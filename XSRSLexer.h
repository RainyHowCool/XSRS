#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XSRSDataType.h"

enum XSRSTokenType
{
	TOKEN_EOF, TOKEN_IDENTIFIER, TOKEN_NUMBER, TOKEN_STRING,
	TOKEN_ASSIGN, TOKEN_EOL,
};

void xsrsBind(u8* data);
int xsrsLexerNext();
int xsrsLexerGetDigit();
u8* xsrsLexerGetString();