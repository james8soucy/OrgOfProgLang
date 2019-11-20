#include <stdio.h>
#include <stdlib.h>

typedef enum {JNUMBER, JBOOL, JPRIM, JAPP, JIF, JCONS, KRET, KIF, KAPP} JTag;

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
typedef struct {JObj o; char p;} JPrim;
JPrim* jPrim(char p);
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