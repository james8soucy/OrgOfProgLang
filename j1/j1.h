#include<stdio.h>

typedef enum JTag{JNUMBER, JBOOL, JPRIM, JAPP, JIF} JTag;

//acts as a sort of interface
typedef struct {JTag t;} JObj;

// e::= v ::= number
typedef struct JNumber{JObj o; int n;} JNumber;

// e::= v ::= bool
typedef struct JBool{JObj o; char b;} JBool;

// e::= v ::= prim
typedef struct JPrim{JObj o; char p;} JPrim;

// e::= (e e ...)
typedef struct JApp{JObj o; JPrim* func; JObj* args;} JApp;

// e::= (if e e e)
typedef struct JIf{JObj o; JObj* cond; JObj* tn; JObj* fn;} JIf;

