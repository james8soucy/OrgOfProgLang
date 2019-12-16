#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "j2.h"

JCons* sigma_table;

void pp_jObj(JObj* jO)
{
	if (jO == NULL)
	{
		printf("NULL");
		return;
	}
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
	case JVAR:
		pp_jVar((JVar*)jO);
		break;
	case JFUNC:
		pp_jFunc((JFunc*)jO);
		break;
	case JDEF:
		pp_jDefine((JDefine*)jO);
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
JObj* sub_jObj(JObj* jO_s, JVar* jV, JObj* jO)
{
	if (jO_s == NULL)
	{
		return NULL;
	}
	switch (jO_s->t)
	{
	case JNUMBER:
		sub_jNumber((JNumber*)jO_s, jV, jO);
		break;
	case JBOOL:
		sub_jBool((JBool*)jO_s, jV, jO);
		break;
	case JAPP:
		sub_jApp((JApp*)jO_s, jV, jO);
		break;
	case JIF:
		sub_jIf((JIf*)jO_s, jV, jO);
		break;
	case JCONS:
		sub_jCons((JCons*)jO_s, jV, jO);
		break;
	case JVAR:
		sub_jVar((JVar*)jO_s, jV, jO);
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
JNumber* sub_jNumber(JNumber* jN, JVar* jV, JObj* jO)
{
	return jN;
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
	if (jB->b)
	{
		printf("JBool(true)");
	}
	else 
	{
		printf("JBool(false)");
	}
	
}
JBool* sub_jBool(JBool* jB, JVar* jV, JObj* jO)
{
	return jB;
}
JPrim* jPrim(char p[2])
{
	JPrim* item = (JPrim*)malloc(sizeof(JPrim));
	item->o.t = JPRIM;
	item->p[0] = p[0];
	item->p[1] = p[1];
	return item;
}
void pp_jPrim(JPrim* jP)
{
	printf("JPrim(%c", jP->p[0]);
	if (jP->p[1] != ' ')
	{
		printf("%c", jP->p[1]);
	}
	printf(")");
}
JApp* jApp(JObj* func, JObj* args)
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
	pp_jObj((jA->func));
	printf(", ");
	pp_jObj(jA->args);
	printf(")");
}
JApp* sub_jApp(JApp* jA, JVar* jV, JObj* jO)
{
	return jApp(jA->func, sub_jCons(jA->args, jV, jO));
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
JIf* sub_jIf(JIf* jI, JVar* jV, JObj* jO)
{
	return jIf(sub_jObj(jI->cond, jV, jO), sub_jObj(jI->tn, jV, jO), sub_jObj(jI->fn, jV, jO));
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
JCons* sub_jCons(JCons* jC, JVar* jV, JObj* jO)
{
	return jCons(sub_jObj(jC->l, jV, jO), sub_jObj(jC->r, jV, jO));
}
JVar* jVar(char* name)
{
	JVar* item = (JVar*)malloc(sizeof(JVar));
	item->o.t = JVAR;
	item->name = name;
	return item;
}
void pp_jVar(JVar* jV)
{
	printf("JVar(%s", jV->name);
	printf(")");
}
JObj* sub_jVar(JVar* jV_s, JVar* jV, JObj* jO)
{
	if (strcmp(jV_s->name, jV->name) == 0)
	{
		return jO;
	}
	return jV_s;
}
JFunc* jFunc(char* name)
{
	JFunc* item = (JFunc*)malloc(sizeof(JFunc));
	item->o.t = JFUNC;
	item->name = name;
	return item;
}
void pp_jFunc(JFunc* jF)
{
	printf("JFunc(%s", jF->name);
	printf(")");
}

JDefine* jDefine(JFunc* func, JCons* args, JObj* body)
{
	JDefine* item = (JDefine*)malloc(sizeof(JDefine));
	item->o.t = JDEF;
	item->func = func;
	item->args = args;
	item->body = body;
	return item;
}
void pp_jDefine(JDefine* jD)
{
	printf("JDefine(");
	pp_jObj(jD->func);
	printf(", ");
	pp_jObj(jD->args);
	printf(", ");
	pp_jObj(jD->body);
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
KIf* kIf(JObj* tn, JObj* fn, JCons* env, JObj* k)
{
	KIf* item = (KIf*)malloc(sizeof(KIf));
	item->o.t = KIF;
	item->f = fn;
	item->t = tn;
	item->env = env;
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
	pp_jObj(kI->env);
	printf(", ");
	pp_jObj(kI->k);
	printf(")");
}
KApp* kApp(JObj* p, JObj* vargs, JObj* args, JCons* env, JObj* k)
{
	KApp* item = (KApp*)malloc(sizeof(KApp));
	item->o.t = KAPP;
	item->p = p;
	item->vargs = vargs;
	item->args = args;
	item->env = env;
	item->k = k;
	return item;
}
void pp_kApp(KApp* kA)
{
	printf("KApp(");
	pp_jObj((kA->p));
	printf(", ");
	pp_jObj(kA->vargs);
	printf(", ");
	pp_jObj(kA->args);
	printf(", ");
	pp_jObj(kA->env);
	printf(", ");
	pp_jObj((kA->k));
	printf(")");
}

char is_true(JObj* o)
{
	if (o->t == JBOOL)
	{
		return ((JBool*)o)->b;
	}
	else
	{
		printf("value tested as bool is not of bool type\n");
		return 0;
	}
}

JObj* cek0(JObj* o)
{
	JObj* k = (JObj*)kRet();
	JCons* env = NULL;
	while (1 == 1)
	{
		//printf("o: ");
		//pp_jObj(o);
		//printf(", \n");
		//printf("env: ");
		//pp_jObj(env);
		//printf(", \n");
		//printf("k: ");
		//pp_jObj(k);
		//printf("\n\n");
		switch (o->t)
		{
		case JVAR:
		{
			JCons* temp_env = env;
			while (temp_env != NULL && strcmp(((JVar*)((JCons*)((JCons*)temp_env->l)->l))->name, ((JVar*)o)->name) != 0)
			{
				temp_env = temp_env->r;
			}
			//pp_jObj(o);
			//pp_jObj(((JVar*)((JCons*)((JCons*)temp_env->l)->l)));
			//pp_jObj(((JObj*)((JCons*)((JCons*)((JCons*)temp_env->l)->r)->l)));
			o = sub_jVar(o, ((JVar*)((JCons*)((JCons*)temp_env->l)->l)), ((JObj*)((JCons*)((JCons*)((JCons*)temp_env->l)->r)->l)));
			env = NULL;
			break;
		}
		case JNUMBER:
		{
			switch (k->t)
			{
			case KRET:
			{
				return o;
				break;
			}
			case KAPP:
			{
				if (((KApp*)k)->vargs == NULL)
				{
					((KApp*)k)->vargs = jCons(o, NULL);
				}
				else
				{
					JCons* temp = ((KApp*)k)->vargs;
					while (temp->r != NULL)
					{
						temp = temp->r;
					}
					temp->r = jCons(o, NULL);
				}
				((KApp*)k)->args = ((JCons*)((KApp*)k)->args)->r;
				if (((KApp*)k)->args == NULL && ((KApp*)k)->p->t == JPRIM)
				{
					o = (JObj*)delta(((KApp*)k)->p, ((KApp*)k)->vargs);
					k = ((KApp*)k)->k;
				}
				else if (((KApp*)k)->args == NULL && ((KApp*)k)->p->t == JFUNC)
				{
					o = (JObj*)sigma(((KApp*)k)->p, ((KApp*)k)->vargs, env);
					env = set_env(((KApp*)k)->p, ((KApp*)k)->vargs, NULL);
					k = ((KApp*)k)->k;
				}
				else
				{
					o = ((JCons*)((KApp*)k)->args)->l;
					env = ((KApp*)k)->env;
				}
				break;
			}
			default:
				printf("k tag not found\n");
				exit(1);
			}
			break;
		}
		case JBOOL:
		{
			switch (k->t)
			{
			case KRET:
			{
				return o;
				break;
			}
			case KIF:
			{
				KIf* temp = (KIf*)k;
				if (is_true(o))
				{
					o = temp->t;
				}
				else
				{
					o = temp->f;
				}
				env = temp->env;
				k = temp->k;
				break;
			}
			default:
				printf("k tag not found\n");
				exit(1);
			}
			break;
			break;
		}
		case JIF:
		{
			JIf* temp = (JIf*)o;
			o = temp->cond;
			k = kIf(temp->tn, temp->fn, env, k);
			break;
		}
		case JAPP:
		{
			JApp* temp = (JApp*)o;
			KApp* kA = kApp(temp->func, NULL, temp->args, env, k);
			k = kA;
			o = ((JCons*)temp->args)->l;
			break;
		}
		case JDEF:
		{
			if (sigma_table == NULL)
			{
				sigma_table = jCons(o, NULL);
			}
			else
			{
				JCons* temp = sigma_table;
				while (temp->r != NULL)
				{
					temp = temp->r;
				}
				temp->r = jCons(o, NULL);
			}
			return jBool(1);
			break;
		}
		default:
			printf("o tag not found\n");
			exit(1);
		}
	}
}

JObj* delta(JPrim* func, JCons* args)
{
	switch (func->p[0])
	{
	case '+':
	{
		int sum = 0;
		while (args != NULL)
		{
			sum = sum + ((JNumber*)args->l)->n;
			args = args->r;
		}
		JNumber* jSum = jNumber(sum);
		return jSum;
		break;
	}
	case '*':
	{
		int pro = 1;
		while (args != NULL)
		{
			pro = pro * ((JNumber*)args->l)->n;
			args = args->r;
		}
		JNumber* jPro = jNumber(pro);
		return jPro;
		break;
	}
	case '-':
	{
		if (args->r == NULL)
		{
			return -1 * ((JNumber*)args->l)->n;
		}
		int dif = ((JNumber*)args->l)->n;
		args = args->r;
		while (args != NULL)
		{
			dif = dif - ((JNumber*)args->l)->n;
			args = args->r;
		}
		JNumber* jDif = jNumber(dif);
		return jDif;
		break;
	}
	case '/':
	{
		int quo = ((JNumber*)args->l)->n;
		args = args->r;
		while (args != NULL)
		{
			quo = quo / ((JNumber*)args->l)->n;
			args = args->r;
		}
		JNumber* jQuo = jNumber(quo);
		return jQuo;
		break;
	}
	case '>':
	{
		switch (func->p[1])
		{
		case ' ':
			return jBool(((JNumber*)args->l)->n > ((JNumber*)args->r->l)->n);
			break;
		case '=':
			return jBool(((JNumber*)args->l)->n >= ((JNumber*)args->r->l)->n);
			break;
		default:
			printf("primitive not recognized");
			exit(1);
			break;
		}
		
	}
	case '<':
	{
		switch (func->p[1])
		{
		case ' ':
			return jBool(((JNumber*)args->l)->n < ((JNumber*)args->r->l)->n);
			break;
		case '=':
			return jBool(((JNumber*)args->l)->n <= ((JNumber*)args->r->l)->n);
			break;
		default:
			printf("primitive not recognized");
			exit(1);
			break;
		}
	}
	case '=':
	{
		if (func->p[1] == '=')
		{
			return jBool(((JNumber*)args->l)->n == ((JNumber*)args->r->l)->n);
		}
		printf("primitive not recognized");
		exit(1);
		break;
	}
	default:
		printf("primitive not recognized");
		exit(1);
		break;
	}
}
JObj* sigma(JFunc* func, JCons* args, JCons* env)
{
	JCons* temp = sigma_table;

	while (temp != NULL && !(strcmp(((JFunc*)((JDefine*)temp->l)->func)->name, func->name) == 0))
	{
		temp = temp->r;
	}
	
	JObj* body = NULL;
	switch (((JDefine*)temp->l)->body->t)
	{
		case JNUMBER:
			body = jNumber(((JNumber*)((JDefine*)temp->l)->body)->n);
			break;
		case JBOOL:
			body = jBool(((JBool*)((JDefine*)temp->l)->body)->b);
			break;
		case JAPP:
			body = jApp(((JApp*)((JDefine*)temp->l)->body)->func, ((JApp*)((JDefine*)temp->l)->body)->args);
			break;
		case JIF:
			body = jIf(((JIf*)((JDefine*)temp->l)->body)->cond, ((JIf*)((JDefine*)temp->l)->body)->tn, ((JIf*)((JDefine*)temp->l)->body)->fn);
			break;
		default:
			printf("function body case error\n");
			exit(1);
	}
	JCons* temp_vars = ((JDefine*)temp->l)->args;
	JCons* temp_args = args;
	JCons* temp_env = env;
	while (temp_env != NULL && temp_env->r != NULL)
	{
		temp_env = temp_env->r;
	}
	while (temp_vars != NULL)
	{
		if (temp_env != NULL)
		{
			temp_env->r = jCons(jCons(temp_vars->l, jCons(temp_args->l, NULL)), NULL);
		}
		else
		{
			temp_env = jCons(jCons(temp_vars->l, jCons(temp_args->l, NULL)), NULL);
		}
		temp_vars = temp_vars->r;
	}
	return body;
}
JCons* set_env(JFunc* func, JCons* args, JCons* env)
{
	JCons* temp = sigma_table;

	while (temp != NULL && !(strcmp(((JFunc*)((JDefine*)temp->l)->func)->name, func->name) == 0))
	{
		temp = temp->r;
	}

	JCons* temp_vars = ((JDefine*)temp->l)->args;
	JCons* temp_args = args;
	JCons* temp_env = env;
	
	if (env == NULL)
	{
		env = jCons(NULL, NULL);
	}
	temp_env = env;	
	while (temp_env->r != NULL)
	{
		temp_env = temp_env->r;
	}
	while (temp_vars != NULL)
	{
		if (temp_env->l != NULL)
		{
			temp_env->r = jCons(jCons(temp_vars->l, jCons(temp_args->l, NULL)), NULL);
			temp_env = temp_env->r;
		}
		else
		{
			temp_env->l = jCons(temp_vars->l, jCons(temp_args->l, NULL));
		}
		temp_vars = temp_vars->r;
		temp_args = temp_args->r;
	}

	//pp_jObj(env);

	return env;
}