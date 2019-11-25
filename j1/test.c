#include <stdio.h>
#include <stdlib.h>
#include "j1.h"
 int main(int argc, char* argv[])
{
    JNumber* var0 = jNumber(54);
    pp_jObj(ck0(var0));
    printf("\n");
    JApp* var1 = jApp(*jPrim("* "), jCons(jNumber(4), jCons(jNumber(6), NULL)));
    pp_jObj(ck0(var1));
    printf("\n");
    JApp* var2 = jApp(*jPrim("+ "), jCons(jNumber(4), jCons(jApp(*jPrim("+ "), jCons(jNumber(3), jCons(jNumber(2), NULL))), NULL)));
    pp_jObj(ck0(var2));
    printf("\n");
    JApp* var3 = jApp(*jPrim("+ "), jCons(jNumber(4), jCons(jApp(*jPrim("+ "), jCons(jNumber(3), jCons(jApp(*jPrim("+ "), jCons(jNumber(2), jCons(jNumber(1), NULL))), NULL))), NULL)));
    pp_jObj(ck0(var3));
    printf("\n");
    JApp* var4 = jApp(*jPrim("+ "), jCons(jApp(*jPrim("* "), jCons(jNumber(2), jCons(jNumber(2), NULL))), jCons(jApp(*jPrim("- "), jCons(jNumber(2), jCons(jNumber(1), NULL))), NULL)));
    pp_jObj(ck0(var4));
    printf("\n");
    JNumber* var5 = jNumber(0);
    pp_jObj(ck0(var5));
    printf("\n");
    JApp* var6 = jApp(*jPrim("+ "), jCons(jNumber(8), NULL));
    pp_jObj(ck0(var6));
    printf("\n");
    JApp* var7 = jApp(*jPrim("+ "), jCons(jNumber(4), jCons(jNumber(8), NULL)));
    pp_jObj(ck0(var7));
    printf("\n");
    JApp* var8 = jApp(*jPrim("+ "), jCons(jNumber(1), jCons(jNumber(1), jCons(jNumber(1), NULL))));
    pp_jObj(ck0(var8));
    printf("\n");
    JApp* var9 = jApp(*jPrim("/ "), jCons(jNumber(9), jCons(jNumber(3), NULL)));
    pp_jObj(ck0(var9));
    printf("\n");
    JApp* var10 = jApp(*jPrim("- "), jCons(jNumber(13), jCons(jNumber(11), NULL)));
    pp_jObj(ck0(var10));
    printf("\n");
    JApp* var11 = jApp(*jPrim("<="), jCons(jNumber(5), jCons(jNumber(3), NULL)));
    pp_jObj(ck0(var11));
    printf("\n");
    JApp* var12 = jApp(*jPrim("< "), jCons(jNumber(12), jCons(jNumber(12), NULL)));
    pp_jObj(ck0(var12));
    printf("\n");
    JApp* var13 = jApp(*jPrim("=="), jCons(jNumber(4), jCons(jNumber(8), NULL)));
    pp_jObj(ck0(var13));
    printf("\n");
    JApp* var14 = jApp(*jPrim("> "), jCons(jNumber(2), jCons(jNumber(1), NULL)));
    pp_jObj(ck0(var14));
    printf("\n");
    JApp* var15 = jApp(*jPrim(">="), jCons(jNumber(7), jCons(jNumber(16), NULL)));
    pp_jObj(ck0(var15));
    printf("\n");
    JIf* var16 = jIf(jBool(1), jNumber(4), jNumber(5));
    pp_jObj(ck0(var16));
    printf("\n");
    JIf* var17 = jIf(jBool(0), jNumber(4), jNumber(5));
    pp_jObj(ck0(var17));
    printf("\n");
    JIf* var18 = jIf(jApp(*jPrim("> "), jCons(jNumber(4), jCons(jNumber(5), NULL))), jNumber(9), jNumber(3));
    pp_jObj(ck0(var18));
    printf("\n");
    JIf* var19 = jIf(jApp(*jPrim("=="), jCons(jNumber(4), jCons(jNumber(4), NULL))), jApp(*jPrim("* "), jCons(jNumber(2), jCons(jNumber(2), NULL))), jNumber(3));
    pp_jObj(ck0(var19));
    printf("\n");
}