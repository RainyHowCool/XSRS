// XSRS.cpp: 定义应用程序的入口点。
//

#include "XSRS.h"

int main()
{
	xsrsLogoShow("Server");
    xsrsBasesInitialize();
    xsrsBaseCreate("Base1");
    xsrsBaseCreate("Base2");
    puts(xsrsBaseList(' '));
    XSRSBase* base = xsrsBaseFind("Base2");
    base->xName = "BaseTwo";
    puts(xsrsBaseList('#'));
    xsrsTableCreate(base, "Table1");
    xsrsTableCreate(base, "Table2");
    puts(xsrsTableList(base, ' '));
    XSRSTable* table = xsrsTableFind(base, "Table2");
    table->sTableName = "TableTwo";
    puts(xsrsTableList(base, '#'));
	xsrsColumnCreate(table, "Column1", DINT);
	xsrsColumnCreate(table, "Column2", DSTRING);
	puts(xsrsColumnList(table, ' '));
    // wtf
	XSRSColumn* column = xsrsColumnFind(table, "Column2");
	column->sName = "ColumnTwo";
	puts(xsrsColumnList(table, '#'));
    XSRSRaw raws[] = {
        {.iInt = 42},
        {.sStr = "Hello, XSRS!"}
	};
	xsrsLineAppend(table, raws);
    XSRSRaw raws1[] = {
        {.iInt = 42},
        {.sStr = "XSRS这一块!"}
    };
    xsrsLineAppend(table, raws1);
	xsrsLineRead(table, 0);
	//xsrsSyncBaseToDisk(base);

	xsrsSocketInitialize();
    xsrsSocketCreateAndBind(11451);
	xsrsSocketListen();
	return 0;
}
