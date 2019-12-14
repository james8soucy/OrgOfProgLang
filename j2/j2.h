#include <stdio.h>
#include <stdlib.h>

typedef enum {JNUMBER, JBOOL, JPRIM, JAPP, JIF, JCONS, JVAR, JFUNC, JDEF, KRET, KIF, KAPP} JTag;

//acts as a sort of interface
typedef struct {JTag t;} JObj;
void pp_jObj(JObj* jO);
JObj* sub_jObj(JObj* jO_s, struct JVar* jV, JObj* jO);

typedef struct JVar { JObj o; char* name; } JVar;
JVar* jVar(char* name);
void pp_jVar(JVar* jV);
JObj* sub_jVar(JVar* jV_s, JVar* jV, JObj* jO);

// e::= v ::= number
typedef struct {JObj o; int n;} JNumber;
JNumber* jNumber(int n);
void pp_jNumber(JNumber* jN);
JNumber* sub_jNumber(JNumber* jN, JVar* jV, JObj* jO);

// e::= v ::= bool
typedef struct {JObj o; char b;} JBool;
JBool* jBool(char b);
void pp_jBool(JBool* jB);
JBool* sub_jBool(JBool* jB, JVar* jV, JObj* jO);

// e::= v ::= prim
typedef struct {JObj o; char p[2];} JPrim;
JPrim* jPrim(char p[2]);
void pp_jPrim(JPrim* jP);

// e::= (e e ...)
typedef struct { JObj o; JObj* func; JObj* args; } JApp;
JApp* jApp(JObj* func, JObj* args);
void pp_jApp(JApp* jA);
JApp* sub_jApp(JApp* jA, JVar* jV, JObj* jO);


// e::= (if e e e)
typedef struct { JObj o; JObj* cond; JObj* tn; JObj* fn;} JIf;
JIf* jIf(JObj* cond, JObj* tn, JObj* fn);
void pp_jIf(JIf* jI);
JIf* sub_jIf(JIf* jI, JVar* jV, JObj* jO);


// JCons structure for building lists of arguments
typedef struct JCons { JObj o; JObj* l; struct JCons* r; } JCons;
JCons* jCons(JObj* l, JCons* r);
void pp_jCons(JCons* jC);
JCons* sub_jCons(JCons* jC, JVar* jV, JObj* jO);


typedef struct JFunc { JObj o; char* name;} JFunc;
JFunc* jFunc(char* name);
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

typedef struct { JObj o; JObj* p; JObj* vargs; JObj* args; JObj* k; } KApp;
KApp* kApp(JObj* p, JObj* vargs, JObj* args, JObj* k);
void pp_kApp(KApp* kA);

JObj* ck0(JObj* o);

char is_true(JObj* o);

JObj* delta(JPrim* func, JCons* args);

JObj* sigma(JFunc* func, JCons* args);