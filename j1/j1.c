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
	case JCONS:
		pp_jCons((JCons*)jO);
		break;
	case KRET:
		pp_kRet((KRet*)jO);
		break;
	case KIF:
		pp_kIf((KIf*)jO);
		break;
	case KAPP:
		pp_kApp((KApp*)jO);
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
JApp* jApp(JPrim func, JObj* args)
{
	JNumber* test = ((JNumber*)args);
	JApp* item = (JApp*)malloc(sizeof(JApp));
	item->o.t = JAPP;
	item->func = func;
	item->args = args;
	return item;
}
void pp_jApp(JApp* jA)
{
	printf("JApp(");
	pp_jPrim(&(jA->func));
	printf(", ");
	pp_jObj(jA->args);
	printf(")");
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
JCons* jCons(JObj* l, JCons* r)
{
	JCons* item = (JCons*)malloc(sizeof(JCons));
	item->o.t = JCONS;
	item->l = l;
	item->r = r;
	return item;
}
void pp_jCons(JCons* jC)
{
	printf("JCons(");
	pp_jObj(jC->l);
	printf(", ");
	if (jC->r != NULL)
	{
		pp_jObj(jC->r);
	}
	else
	{
		printf("NULL");
	}
	printf(")");
}

KRet* kRet()
{
	KRet* item = (KRet*)malloc(sizeof(KRet));
	item->o.t = KRET;
	return item;
}
void pp_kRet(KRet* kR)
{
	printf("KRet()");
}
KIf* kIf(JObj* tn, JObj* fn, JObj* k)
{
	KIf* item = (KIf*)malloc(sizeof(KIf));
	item->o.t = KIF;
	item->f = fn;
	item->t = tn;
	item->k = k;
	return item;

}
void pp_kIf(KIf* kI)
{
	printf("KIf(");
	pp_jObj(kI->t);
	printf(", ");
	pp_jObj(kI->f);
	printf(", ");
	pp_jObj(kI->k);
	printf(")");
}
KApp* kApp(JPrim func, JObj* args, JObj* k)
{
	KApp* item = (KApp*)malloc(sizeof(KApp));
	item->o.t = KAPP;
	item->func = func;
	item->args = args;
	item->k = k;
	return item;
}
void pp_kApp(KApp* kA)
{
	printf("KApp(");
	pp_jPrim(&(kA->func));
	printf(", ");
	pp_jObj(kA->args);
	printf(", ");
	pp_jPrim((kA->k));
	printf(")");
}