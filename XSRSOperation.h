#pragma once
#include "XSRS.h"
#include <string.h>
void xsrsBasesInitialize();
void xsrsBaseCreate(char* baseName);
u8* xsrsBaseList(u8 spilt);
struct XSRSBase* xsrsBaseFind(u8* name);
void xsrsTableCreate(struct XSRSBase* base, char* tableName);
u8* xsrsTableList(struct XSRSBase* base, u8 spilt);
struct XSRSTable* xsrsTableFind(struct XSRSBase* base, u8* name);