#include "calculator.h"


int main(char args[]) {
	//args to stream!!!???
	FILE* inputstream = NULL;
	inputstream = tmpfile();
	if(inputstream == NULL) {
		printf("null stream!");
		exit(-1);
	}
	fputs(args, inputstream);
	fclose(inputstream);
	
	
	Token token = {'0', 0, '0'};
	TokenStream ts = {{'0', 0, '0'}, true};
	printf("\n>>");
	float val = calculate(&ts);
	printf("\n\n%f", val);
	fclose(inputstream);
}


float calculate(TokenStream* ts) {
	return expression(ts);
}

Token getNextToken(TokenStream* ts) {
	Token t = {'0', 0, '0'};
	if(ts->empty == false) {
		t = ts->buffer;
		ts->empty = true;
	}
	else {
		char c = getchar();

		if(c == EOF) exit(-5);		//error handling
		else if(isdigit(c)) {
			ungetc(c, stdin);
			scanf("%f", &t.value);
			t.type = NUMBER;
			t.sign = '0';
		}
		else {
			t.type = SIGN;
			t.sign = c;
			t.value = 0;
		}
	}
	return t;
}

float expression(TokenStream* ts) {
	float val = term(ts);
	Token t = getNextToken(ts);
	if(t.type = SIGN) {
		switch(t.sign) {
			case '+':
				return val+expression(ts);
				break;
			case '-':
				return val-expression(ts);
				break;
			default:
				putbackToken(t, ts);
				return val;
				break;
		}
	}
	else {
	exit(-2);
	}
}

float term(TokenStream* ts) {
	float val = number(ts);
	Token t = getNextToken(ts);
	if(t.type == SIGN) {
		switch(t.sign) {
			case '*':
				return val*term(ts);
				break;
			case '/':
				return val/term(ts);
				break;
			default:
				putbackToken(t, ts);
				return val;
				break;
		}
	}	
	else {
		exit(-1);
	}

}

float number(TokenStream* ts) {
	Token t = getNextToken(ts);

	if(t.type == SIGN) {
		switch(t.sign) {
			case '(':
				{
					float f = expression(ts);
					t = getNextToken(ts);		//error handling
					if(t.sign != ')') exit(-3);
					return f;
				}
				break;
			default:
				exit(-4);
				break;
		}
	}
	else {
		return t.value;
	}
}

bool putbackToken(Token t, TokenStream* ts) {
	if(ts->empty == false) return false;
	else {
		ts->buffer = t;
		ts->empty = false;
	}
}
