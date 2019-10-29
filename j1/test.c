#include <stdio.h>
#include <stdlib.h>
#include "j1.h"

int main(int argc, char* argv[])
{
	//JNumber* test1 = jNumber(4);
	//pp_jObj((JObj*)test1);
	//printf("\n");

	//JBool* test2 = jBool('T');
	//pp_jObj((JObj*)test2);
	//printf("\n");

	JNumber* test3_args = (JNumber*)malloc(sizeof(JNumber) * 2);
	test3_args[0] = *jNumber(3);
	test3_args[1] = *jNumber(4);

	pp_jObj(&test3_args[0]);
	printf("\n");
	pp_jObj(&test3_args[1]);
	printf("\n");

	JApp* test3 = jApp(*jPrim('+'), &test3_args, 2);

	//pp_jObj(&(test3->args[0]));
	//printf("\n");
	//pp_jObj(&(test3->args[1]));

	pp_jObj((JObj*)test3);

	printf("\n");

	JNumber* test4_args = (JNumber*)malloc(sizeof(JNumber) * 2);
	test4_args[0] = *jNumber(6);
	test4_args[1] = *jNumber(8);
	JIf* test4 = jIf(jApp(*jPrim('<'), test4_args, 2), jNumber(8), jNumber(6));
	pp_jObj((JObj*)test4);
	printf("\n");

	return 0;
}