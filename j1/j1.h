#include <stdio.h>
#include <stdlib.h>

typedef enum {JNUMBER, JBOOL, JPRIM, JAPP, JIF} JTag;

//acts as a sort of interface
typedef struct {JTag t;} JObj;

// e::= v ::= number
typedef struct {JObj o; int n;} JNumber;
JNumber* jNumber(int n);

// e::= v ::= bool
typedef struct {JObj o; char b;} JBool;
JBool* jBool(char b);

// e::= v ::= prim
typedef struct {JObj o; char p;} JPrim;
JPrim* jPrim(char p);

// e::= (e e ...)
typedef struct {JObj o; JPrim func; JObj* args;} JApp;
JApp* jApp(JPrim func, JObj* args);

// e::= (if e e e)
typedef struct {JObj o; JObj* cond; JObj* tn; JObj* fn;} JIf;
JIf* jIf(JObj* cond, JObj* tn, JObj* fn);
