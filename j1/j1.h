#include<stdio.h>

enum JTag{JNUMBER, JBOOL, JPRIM, JAPP, JIF}

typedef enum JTag JTag

struct JNumber
{
	JTag tag;
	int n;
};