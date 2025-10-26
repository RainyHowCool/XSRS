// XSRSOperation.c
#include "XSRSOperation.h"
#define _CRT_SECURE_NO_WARNINGS

XSRSBase* xBases;
XSRSBase* xBase;
i32			xBaseCount = 0;

void xsrsBasesInitialize()
{
	// 16-KB 
	xBases = malloc(sizeof(XSRSBase) * 1024 * 16);
	xBase = xBases;
};

void xsrsBaseCreate(char* baseName)
{
	XSRSBase xBaseNow = { .xTable = malloc(sizeof(XSRSTable) * 16 * 1024), .xName = baseName, .xTableCount = 0 };
	xBases[xBaseCount++] = xBaseNow;
	xBase++;
}


u8* xsrsBaseList(u8 spilt)
{
	static u8 buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	size_t remaining = sizeof(buffer) - 1;
	for (int i = 0; i < xBaseCount && remaining > 0; i++) {
		size_t len = strlen(xBases[i].xName);
		if (len >= remaining) break;
		strncat(buffer, xBases[i].xName, remaining - 1);
		remaining -= len;
		if (remaining > 0) {
			buffer[sizeof(buffer) - remaining - 1] = spilt;
			remaining--;
		}
	}
	return buffer;
}

XSRSBase* xsrsBaseFind(u8* name)
{
	for (int i = 0; i < xBaseCount; i++) {
		if (!strcmp(xBases[i].xName, name)) {
			return xBases + i;
		}
	} return NULL;
}

void xsrsTableCreate(XSRSBase* base, char* tableName)
{
	XSRSTable xTable = { .sTableName = tableName, .xColumn = malloc(sizeof(XSRSColumn) * 256),
		.xLine = malloc(sizeof(XSRSRaw*) * 1024 * 256), .xColumnMax = 256,
		.xLineMax = 1024 * 256, .xColumnCount = 0, .xLineCount = 0 };
	base->xTable[base->xTableCount++] = xTable;
}

u8* xsrsTableList(XSRSBase* base, u8 spilt)
{
	static u8 buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	size_t remaining = sizeof(buffer) - 1;
	for (int i = 0; i < base->xTableCount && remaining > 0; i++) {
		size_t len = strlen(base->xTable[i].sTableName);
		if (len >= remaining) break;
		strncat(buffer, base->xTable[i].sTableName, remaining - 1);
		remaining -= len;
		if (remaining > 0) {
			buffer[sizeof(buffer) - remaining - 1] = spilt;
			remaining--;
		}
	}
	return buffer;
}

XSRSTable* xsrsTableFind(XSRSBase* base, u8* name)
{
	for (int i = 0; i < base->xTableCount; i++) {
		if (!strcmp(base->xTable[i].sTableName, name)) {
			return base->xTable + i;
		}
	} return NULL;
}

void xsrsColumnCreate(XSRSTable* table, char* columnName, u8 type)
{
	XSRSColumn xColumn = { .sName = columnName, .eType = type };
	table->xColumn[table->xColumnCount++] = xColumn;
}

u8* xsrsColumnList(XSRSTable* table, u8 spilt)
{
	static u8 buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	size_t remaining = sizeof(buffer) - 1;
	for (int i = 0; i < table->xColumnCount && remaining > 0; i++) {
		size_t len = strlen(table->xColumn[i].sName);
		if (len >= remaining) break;
		strncat(buffer, table->xColumn[i].sName, remaining - 1);
		remaining -= len;
		if (remaining > 0) {
			buffer[sizeof(buffer) - remaining - 1] = spilt;
			remaining--;
		}
	}
	return buffer;
}

XSRSColumn* xsrsColumnFind(XSRSTable* table, u8* name)
{
	for (int i = 0; i < table->xColumnCount; i++) {
		if (!strcmp(table->xColumn[i].sName, name)) {
			XSRSColumn* xColumnFound = table->xColumn + i;
			return xColumnFound;
		}
	} return NULL;
}

void xsrsLineAppend(XSRSTable* table, XSRSRaw* raw)
{
	if (table->xLineCount < table->xLineMax) {
		XSRSRaw* newRaw = malloc(sizeof(XSRSRaw) * table->xColumnCount);
		memcpy(newRaw, raw, sizeof(XSRSRaw) * table->xColumnCount);
		table->xLine[table->xLineCount++] = newRaw;
	}
}

void xsrsLineRead(XSRSTable* table, i32 id)
{
	for (int i = 0; i < table->xColumnCount; i++) {
		XSRSColumn* column = &table->xColumn[i];
		switch (column->eType) {
		case DINT:
			printf("%d\t", table->xLine[id][i].iInt);
			break;
		case DSTRING:
			printf("%s\t", table->xLine[id][i].sStr);
			break;
		default:
			break;
		}
	}
}

void xsrsSyncBaseToDisk(XSRSBase *base)
{
	// XSRS Binary Format
	int len = 0;
	FILE* fp = fopen("base.xsrs", "wb");
	if (!fp) {
		fprintf(stderr, "Error opening file for writing.\n");
		return;
	}
	for (int i = 0; i < base->xTableCount; i++) {
		// Write Table Name to disk
		XSRSTable table = base->xTable[i];
		fputc(XSRS_TABLE_LOAD, fp);
		fputs(table.sTableName, fp);
		fputc('\0', fp);
		// Write Columns to disk
		fputs(XSRS_COLUMN_LOAD, fp);
		XSRSColumn* columns = table.xColumn;
		for (int j = 0; j < table.xColumnCount; j++) {
			fputs(columns[j].sName, fp);
			fputc('\0', fp);
			fputc(columns[j].eType, fp);
			fputs('\0', fp);
		}
		// Write Lines to disk
		fputc(XSRS_LINE_LOAD, fp);
		for (int j = 0; j < table.xLineCount; j++) {
			for (int k = 0; k < table.xColumnCount; k++) {
				switch (columns[k].eType) {
				case DINT:
					fwrite(&(table.xLine[j] + k)->iInt, sizeof(i32), 1, fp);
					break;
				case DSTRING:
					fputs((table.xLine[j] + k)->sStr, fp);
					fputc('\0', fp);
					break;
				default:
					break;
				}
			}
		}
	}
	// close
	fclose(fp);
}