#include <math.h>
#include <ctype.h>
#include <float.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define pi = 3.14
#define e = 2.7

#define NUMBER 'n'
#define SIGN 's'

typedef struct Token {
	char type;
	float value;
	char sign;
}Token;

typedef struct TokenStream {
	Token buffer;
	bool empty;
}TokenStream;


float calculate(TokenStream* ts);
Token getNextToken(TokenStream* ts);
bool putbackToken(Token t, TokenStream* ts);

float expression(TokenStream *ts);
float term(TokenStream *ts);
float number(TokenStream *ts);


