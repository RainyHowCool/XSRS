#include "XSRSOperation.h"

XSRSBase*	xBases;
XSRSBase*	xBase;
i32					xBaseCount = 0;

void xsrsBasesInitialize()
{
	// 16-KB 
	xBases = malloc(sizeof(XSRSBase) * 1024 * 16);
	xBase = xBases;
};

void xsrsBaseCreate(char *baseName)
{
	XSRSBase xBaseNow = { .xTable = malloc(sizeof(XSRSTable) * 16 * 1024), .xName = baseName, .xTableCount = 0};
	xBases[xBaseCount++] = xBaseNow;
	xBase++;
}


u8* xsrsBaseList(u8 spilt)
{
	u8 buffer[4096] = ""; // Make a 4KiB Size Buffer
	int len = 0;	// for adding spilt symbol
	for (int i = 0; i < xBaseCount; i++) {
		strcat(buffer, xBases[i].xName);
		len = strlen(buffer);
		buffer[len] = spilt;
	} return buffer;
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
		.xLine = malloc(sizeof(XSRSRaw) * 1024 * 256), .xColumnMax = 256, 
		.xLineMax = 1024, .xColumnCount = 0, .xLineCount = 0 };
	base->xTable[base->xTableCount++] = xTable;
}

u8* xsrsTableList(XSRSBase* base, u8 spilt)
{
	u8 buffer[4096] = ""; // Make a 4KiB Size Buffer
	int len = 0;	// for adding spilt symbol
	for (int i = 0; i < base->xTableCount; i++) {
		strcat(buffer, base->xTable[i].sTableName);
		len = strlen(buffer);
		buffer[len] = spilt;
	} return buffer;
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
	u8 buffer[4096] = ""; // Make a 4KiB Size Buffer
	int len = 0;	// for adding spilt symbol
	for (int i = 0; i < table->xColumnCount; i++) {
		strcat(buffer, table->xColumn[i].sName);
		len = strlen(buffer);
		buffer[len] = spilt;
	} return buffer;
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
		table->xLine[table->xLineCount++] = raw;
	}
}

