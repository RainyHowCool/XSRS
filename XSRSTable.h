#pragma once

#include "XSRSDataType.h"

union XSRSRaw
{
	u8*		sStr;
	i32		iInt;
	i64		lLong;
	boolean bBoolean;
};

enum XSRSDataType
{
	STRING = 128, INT, LONG, BOOLEAN
};

struct XSRSColumn
{
	u8* sName;
	u8	eType;
};

struct XSRSTable
{
	struct XSRSColumn*	xColumn;
	union XSRSRaw**		xLine;
	u8*					sTableName;
};

struct XSRSBase
{
	struct XSRSTable*	xTable;
	i32					xTableCount;
	u8*					xName;
};