#include "XSRSOperation.h"

struct XSRSBase*	xBases;
struct XSRSBase*	xBase;
i32					xBaseCount = 0;

void xsrsBasesInitialize()
{
	// 16-KB 
	xBases = malloc(sizeof(struct XSRSBase) * 1024 * 16);
	xBase = xBases;
};

void xsrsBaseCreate(char *baseName)
{
	struct XSRSBase xBaseNow = { .xTable = malloc(sizeof(struct XSRSTable) * 16 * 1024), .xName = baseName, .xTableCount = 0};
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

struct XSRSBase* xsrsBaseFind(u8* name)
{
	for (int i = 0; i < xBaseCount; i++) {
		if (!strcmp(xBases[i].xName, name)) {
			return xBases + i;
		}
	} return NULL;
}

void xsrsTableCreate(struct XSRSBase* base, char* tableName)
{
	struct XSRSTable xTable = { .sTableName = tableName, .xColumn = NULL, .xLine = NULL };
	base->xTable[base->xTableCount++] = xTable;
}

u8* xsrsTableList(struct XSRSBase* base, u8 spilt)
{
	u8 buffer[4096] = ""; // Make a 4KiB Size Buffer
	int len = 0;	// for adding spilt symbol
	for (int i = 0; i < base->xTableCount; i++) {
		strcat(buffer, base->xTable[i].sTableName);
		len = strlen(buffer);
		buffer[len] = spilt;
	} return buffer;
}

struct XSRSTable* xsrsTableFind(struct XSRSBase* base, u8* name)
{
	for (int i = 0; i < base->xTableCount; i++) {
		if (!strcmp(base->xTable[i].sTableName, name)) {
			return base->xTable + i;
		}
	} return NULL;
}