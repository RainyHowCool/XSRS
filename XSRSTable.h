#pragma once

#include "XSRSDataType.h"

union XSRSRaw
{
	u8*		sStr;
	i32		iInt;
	i64		lLong;
	boolean bBoolean;
};

typedef union XSRSRaw XSRSRaw;

enum XSRSDataType
{
	STRING, INT, LONG, BOOLEAN
};

struct XSRSColumn
{
	u8* sName;
	u8	eType;
};

typedef struct XSRSColumn XSRSColumn;

struct XSRSTable
{
	struct XSRSColumn*	xColumn;
	i32					xColumnCount;
	i32					xColumnMax;
	union XSRSRaw**		xLine;
	i32					xLineCount;
	i32					xLineMax;
	u8*					sTableName;
};

typedef struct XSRSTable XSRSTable;

struct XSRSBase
{
	struct XSRSTable*	xTable;
	i32					xTableCount;
	u8*					xName;
};

typedef struct XSRSBase XSRSBase;