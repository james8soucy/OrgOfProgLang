#include <stdio.h>
#include <stdlib.h>
#include "j1.h"

int main(int argc, char* argv[])
{
	JNumber* test1 = jNumber(4);
	JBool* test2 = jBool('T');

	JNumber* test3_args = (JNumber*)malloc(sizeof(JNumber) * 2);
	test3_args[0] = *jNumber(3);
	test3_args[1] = *jNumber(4);
	JApp* test3 = jApp(*jPrim('+'), test3_args);

	JNumber* test4_args = (JNumber*)malloc(sizeof(JNumber) * 2);
	test4_args[0] = *jNumber(6);
	test4_args[1] = *jNumber(8);
	JIf* test4 = jIf(jApp(*jPrim('<'), test4_args), jNumber(8), jNumber(6));
	return 0;
}