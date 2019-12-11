#include <stdio.h>
#include <stdlib.h>

typedef enum {JNUMBER, JBOOL, JPRIM, JAPP, JIF, JCONS, JVAR, JFUNC, JDEF, KRET, KIF, KAPP} JTag;

//acts as a sort of interface
typedef struct {JTag t;} JObj;
void pp_jObj(JObj* jO);

// e::= v ::= number
typedef struct {JObj o; int n;} JNumber;
JNumber* jNumber(int n);
void pp_jNumber(JNumber* jN);

// e::= v ::= bool
typedef struct {JObj o; char b;} JBool;
JBool* jBool(char b);
void pp_jBool(JBool* jB);

// e::= v ::= prim
typedef struct {JObj o; char p[2];} JPrim;
JPrim* jPrim(char p[2]);
void pp_jPrim(JPrim* jP);

// e::= (e e ...)
typedef struct { JObj o; JPrim func; JObj* args; } JApp;
JApp* jApp(JPrim func, JObj* args);
void pp_jApp(JApp* jA);

// e::= (if e e e)
typedef struct { JObj o; JObj* cond; JObj* tn; JObj* fn;} JIf;
JIf* jIf(JObj* cond, JObj* tn, JObj* fn);
void pp_jIf(JIf* jI);

// JCons structure for building lists of arguments
typedef struct JCons { JObj o; JObj* l; struct JCons* r; } JCons;
JCons* jCons(JObj* l, JCons* r);
void pp_jCons(JCons* jC);

typedef struct JVar { JObj o; char* name; } JVar;
JVar* jVar(char* name);
void pp_jVar(JVar* jV);

typedef struct JFunc { JObj o; char* name; JObj* args; } JFunc;
JFunc* jFunc(char* name, JObj* args);
void pp_jFunc(JFunc* jF);

typedef struct JDefine { JObj o; JFunc* func; JCons* args; JObj* body; } JDefine;
JDefine* jDefine(JFunc* func, JCons* args, JObj* body);
void pp_jDefine(JDefine* jD);


typedef struct { JObj o;} KRet;
KRet* kRet();
void pp_kRet(KRet* kR);

typedef struct { JObj o; JObj* t; JObj* f; JObj* k; } KIf;
KIf* kIf(JObj* tn, JObj* fn, JObj* k);
void pp_kIf(KIf* kI);

typedef struct { JObj o; JPrim p; JObj* vargs; JObj* args; JObj* k; } KApp;
KApp* kApp(JPrim p, JObj* vargs, JObj* args, JObj* k);
void pp_kApp(KApp* kA);

JObj* ck0(JObj* o);

char is_true(JObj* o);

JObj* delta(JPrim func, JCons* args);