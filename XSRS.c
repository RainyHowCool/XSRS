// XSRS.cpp: 定义应用程序的入口点。
//

#include "XSRS.h"
#include "XSRSOperation.h"

static void xsrsLogoShow()
{
    static char sRawLogo[] = "                                  _____                    _____                    _____          \n"
        "        ______                   /\\    \\                  /\\    \\                  /\\    \\         \n"
        "       |::|   |                 /::\\    \\                /::\\    \\                /::\\    \\        \n"
        "       |::|   |                /::::\\    \\              /::::\\    \\              /::::\\    \\       \n"
        "       |::|   |               /::::::\\    \\            /::::::\\    \\            /::::::\\    \\      \n"
        "       |::|   |              /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\     \n"
        "       |::|   |             /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\    \n"
        "       |::|   |             \\:::\\   \\:::\\    \\      /::::\\   \\:::\\    \\       \\:::\\   \\:::\\    \\   \n"
        "       |::|   |           ___\\:::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\    ___\\:::\\   \\:::\\    \\  \n"
        " ______|::|___|___ ____  /\\   \\:::\\   \\:::\\    \\  /:::/\\:::\\   \\:::\\____\\  /\\   \\:::\\   \\:::\\    \\ \n"
        "|:::::::::::::::::|    |/::\\   \\:::\\   \\:::\\____\\/:::/  \\:::\\   \\:::|    |/::\\   \\:::\\   \\:::\\____\\\n"
        "|:::::::::::::::::|____|\\:::\\   \\:::\\   \\::/    /\\::/   |::::\\  /:::|____|\\:::\\   \\:::\\   \\::/    /\n"
        " ~~~~~~|::|~~~|~~~       \\:::\\   \\:::\\   \\/____/  \\/____|:::::\\/:::/    /  \\:::\\   \\:::\\   \\/____/ \n"
        "       |::|   |           \\:::\\   \\:::\\    \\            |:::::::::/    /    \\:::\\   \\:::\\    \\     \n"
        "       |::|   |            \\:::\\   \\:::\\____\\           |::|\\::::/    /      \\:::\\   \\:::\\____\\    \n"
        "       |::|   |             \\:::\\  /:::/    /           |::| \\::/____/        \\:::\\  /:::/    /    \n"
        "       |::|   |              \\:::\\/:::/    /            |::|  ~|               \\:::\\/:::/    /     \n"
        "       |::|   |               \\::::::/    /             |::|   |                \\::::::/    /      \n"
        "       |::|   |                \\::::/    /              \\::|   |                 \\::::/    /       \n"
        "       |::|___|                 \\::/    /                \\:|   |                  \\::/    /        \n"
        "        ~~                       \\/____/                  \\|___|                   \\/____/         ";

    static char sPromptInfo[] = "XSRS Store-RAM System Alpha 1\n"
        "Build Time: %s %s\n"
        "Running in %s (%s %d)\n"
        "2025 xiaokuai_awa\n";
                                                                                       
    puts(sRawLogo);
    printf(sPromptInfo, __DATE__, __TIME__, PLATFORM, COMPILER, COMPILER_VERSION);
}

int main()
{
	xsrsLogoShow();
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
	xsrsColumnCreate(table, "Column1", INT);
	xsrsColumnCreate(table, "Column2", STRING);
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
	xsrsLineRead(table, 0);
	return 0;
}
