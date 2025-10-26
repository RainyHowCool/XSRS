#pragma once
#include "XSRS.h"
#include <string.h>
void xsrsBasesInitialize();
void xsrsBaseCreate(char* baseName);
u8* xsrsBaseList(u8 spilt);
XSRSBase* xsrsBaseFind(u8* name);
void xsrsTableCreate(XSRSBase* base, char* tableName);
u8* xsrsTableList(XSRSBase* base, u8 spilt);
XSRSTable* xsrsTableFind(XSRSBase* base, u8* name);
void xsrsColumnCreate(XSRSTable* table, char* columnName, u8 type);
u8* xsrsColumnList(XSRSTable* table, u8 spilt);
XSRSColumn* xsrsColumnFind(XSRSTable* table, u8* name);