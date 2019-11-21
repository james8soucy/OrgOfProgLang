#include <stdio.h>
#include <stdlib.h>
#include "j1.h"

int main(int argc, char* argv[])
{	
	JNumber* test1 = jNumber(0);
	JBool* test2 = jBool(1);
	JApp* test3 = jApp(*jPrim("+ "), jCons(jNumber(0), jCons(jNumber(2), NULL)));
	JIf* test4 = jIf(jApp(*jPrim(">="), jCons(jNumber(3), jCons(jNumber(4), NULL))), jNumber(5), jNumber(3));
	JIf* test5 = jIf(jBool(1), jNumber(4), jNumber(2));
	pp_jObj(ck0(test1));
	printf("\n");
	pp_jObj(ck0(test2));
	printf("\n");
	pp_jObj(ck0(test3));
	printf("\n");
	pp_jObj(ck0(test4));
	printf("\n");
	pp_jObj(ck0(test5));
	printf("\n");
	return 0;
}