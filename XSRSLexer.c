#include "XSRSLexer.h"

u8* cp;
char sb[4096] = { 0 };
int sbc = 0;
int vl = 0;

void xsrsBind(u8* data)
{
	cp = data;
}

int xsrsLexerNext()
{
	if (*cp == ' ' || *cp == '\t' || *cp == '\r') {
		// Skip whitespace
		while (*cp == ' ' || *cp == '\t' || *cp == '\r') {
			cp++;
		}
	}
	else if (*cp == '\0') {
		return TOKEN_EOF;
	} else if (*cp == '=') {
		cp++;
		return TOKEN_ASSIGN;
	}
	else if (*cp == '\n') {
		cp++;
		return TOKEN_EOL;
	}
	else if ((*cp >= '0') && (*cp <= '9')) {
		// Number
		vl = 0;
		while ((*cp >= '0') && (*cp <= '9')) {
			vl = vl * 10 + *cp - '0';
			cp++;
		}
		return TOKEN_NUMBER;
	}
	else if (((*cp >= 'a') && (*cp <= 'z')) || ((*cp >= 'A') && (*cp <= 'Z')) || (*cp == '_')) {
		// Identifier
		memset(sb, 0, sizeof(sb));
		sbc = 0;
		while (((*cp >= 'a') && (*cp <= 'z')) || ((*cp >= 'A') && (*cp <= 'Z')) || ((*cp >= '0') && (*cp <= '9')) || (*cp == '_')) {
			sb[sbc++] = *cp;
			cp++;
		}
		return TOKEN_IDENTIFIER;
	}
	else if (*cp == '"') {
		// String
		memset(sb, 0, sizeof(sb));
		sbc = 0;
		cp++; // Skip opening quote
		while (*cp != '"' && *cp != '\0') {
			sb[sbc++] = *cp;
			cp++;
		}
		if (*cp == '"') {
			cp++; // Skip closing quote
		}
		return TOKEN_STRING;
	}
}

int xsrsLexerGetDigit()
{
	return vl;
}

u8* xsrsLexerGetString()
{
	return strdup(sb);
}