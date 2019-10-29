#include <stdio.h>
#include <stdlib.h>
#include "j1.h"

void pp_jObj(JObj* jO)
{
	switch (jO->t)
	{
	case JNUMBER:
		pp_jNumber((JNumber*)jO);
		break;
	case JBOOL:
		pp_jBool((JBool*)jO);
		break;
	case JPRIM:
		pp_jPrim((JNumber*)jO);
		break;
	case JAPP:
		pp_jApp((JApp*)jO);
		break;
	case JIF:
		pp_jIf((JIf*)jO);
		break;
	default:
		printf("tag not found");
		exit(1);
	}
}
JNumber* jNumber(int n)
{
	JNumber* item = (JNumber*)malloc(sizeof(JNumber));
	item->o.t = JNUMBER;
	item->n = n;
	return item;
}
void pp_jNumber(JNumber* jN)
{
	printf("JNumber(%d)", jN->n);
}
JBool* jBool(char b)
{
	JBool* item = (JBool*)malloc(sizeof(JBool));
	item->o.t = JBOOL;
	item->b = b;
	return item;
}
void pp_jBool(JBool* jB)
{
	printf("JBool(%c)", jB->b);
}
JPrim* jPrim(char p)
{
	JPrim* item = (JPrim*)malloc(sizeof(JPrim));
	item->o.t = JPRIM;
	item->p = p;
	return item;
}
void pp_jPrim(JPrim* jP)
{
	printf("JPrim(%c)", jP->p);
}
JApp* jApp(JPrim func, JObj* args, int argc)
{
	JApp* item = (JApp*)malloc(sizeof(JApp));
	item->o.t = JAPP;
	item->func = func;
	item->args = args;
	item->argc = argc;
	return item;
}
void pp_jApp(JApp* jA)
{
	printf("JApp(");
	pp_jPrim(&(jA->func));
	printf(", [");
	for (int i = 0; i < jA->argc; i++)
	{
		pp_jObj((JObj*)&jA->args[i]);
		if (i != jA->argc - 1)
		{
			printf(", ");
		}
	}
	printf("])");
}
JIf* jIf(JObj* cond, JObj* tn, JObj* fn)
{
	JIf* item = (JIf*)malloc(sizeof(JIf));
	item->o.t = JIF;
	item->cond = cond;
	item->tn = tn;
	item->fn = fn;
	return item;
}
void pp_jIf(JIf* jI)
{
	printf("JIf(");
	pp_jObj(jI->cond);
	printf(", ");
	pp_jObj(jI->tn);
	printf(", ");
	pp_jObj(jI->fn);
	printf(")");
}
