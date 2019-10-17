import copy #needed for temp arrays

# J1
# e = v | (e e ...) | (if e e e)
# v = number | bool | prim

class JNumber:
    def __init__(self, n):
        self.n = n
    def pp(self):
        return str(self.n)
    def interp(self):
        return self
class JEmp:
    def __init__(self):
        pass
    def pp(self):
        return "{}"
    def interp(self):
        return self
class JCons:
    def __init__(self, l, r):
        self.l = l
        self.r = r
    def pp(self):
        return "(" + self.l.pp() + ", " + self.r.pp() + ")"
    def interp(self):
        return JCons(self.l.interp(), self.r.interp())
class JIf:
    def __init__(self, cond, tn, fn):
        self.cond = cond
        self.tn = tn
        self.fn = fn
    def pp(self):
        return "(if " + self.cond.pp() + ", " + self.tn.pp() + ", " + self.fn.pp() + ")"
    def interp(self):
        _cond = self.cond.interp()
        if (_cond.b):
            return self.tn.interp()
        else:
            return self.fn.interp()
class JBool:
    def __init__(self, b):
        self.b = b
    def pp(self):
        return str(self.b)
    def interp(self):
        return self
class JPrim:
    def __init__(self, p):
        self.p = p
    def pp(self):
        return str(self.p)
    def interp(self):
        return self
class JApp:
    def __init__(self, func, args):
        self.func = func
        self.args = args
    def pp(self):
        retstr = "(fn " + self.func.pp() + " ["
        for arg in self.args:
            retstr = retstr + arg.pp() + " "
        retstr = retstr + "])"
        return retstr
    def interp(self):
        return delta(self)

class SeStr:
    def __init__(self, s):
        self.s = s
class SeNum:
    def __init__(self, n):
        self.n = n
class SeEmp:
    def __init__(self):
        pass
class SeCons:
    def __init__(self, l, r):
        self.l = l
        self.r = r

#C := hole | (if C e e) | (e ... C ... e)
class CHole:
    def __init__(self):
        self.h = None
    def plug(self, p):
        self.h = p
        return p
    def pp(self):
        #for testing purposes
        if self.h:
            return 'hole filled with' + self.h.pp()
        else:
            return 'HOLE'
class Cif0:
    def __init__(self, e1, e2):
        self.cond = CHole()
        self.e1 = e1
        self.e2 = e2
    def plug(self, cond):
        self.cond = cond
        return JIf(cond, self.e1, self.e2)
    def pp(self):
        return "{if " + self.cond.pp() + ", " + self.e1.pp() + ", " + self.e2.pp() + "}"
# class Cif1:
    # def __init__(self, e0, e2):
        # self.e0 = e0
        # self.e2 = e2
# class Cif2:
    # def __init__(self, e0, e1):
        # self.e0 = e0
        # self.e1 = e1
class CApp:
    def __init__(self, func, args):
        self.func = func
        self.args = args
        for i, item in enumerate(args):
            if type(item) in [CHole, CApp, Cif0]:
                self.hdex = i
    def plug(self, p):
        if isinstance(self.args[self.hdex], CHole):
            self.args[self.hdex] = self.args[self.hdex].plug(p)
        else:
            self.args[self.hdex].plug(p)
        return JApp(self.func, self.args)
    def pp(self):
        #for testing
        retstr = "{fn " + self.func.pp() + " ["
        for arg in self.args:
            retstr = retstr + arg.pp() + " "
        retstr = retstr + "]}"
        return retstr
   
class CCState:
    def __init__(self, j, c):
        self.j = j
        self.c = c

def find_hole(cexpr, cholder):
    if type(cexpr) not in [CApp, Cif0]:
        return False
    if isinstance(cexpr, CApp):
        if any([isinstance(arg, CHole) for arg in cexpr.args]):
            return [cexpr, cholder]
        for i, arg in enumerate(cexpr.args):
            t_held = copy.deepcopy(cexpr)
            t_holder = copy.deepcopy(cholder)
            t_held.args[i] = CHole()
            if isinstance(t_holder, CHole):
                t_holder = t_holder.plug(t_held)
            else:
                t_holder.plug(t_held)
            if find_hole(arg, t_holder):
                return find_hole(arg, t_holder)
    if isinstance(cexpr, Cif0):
        if any([isinstance(arg, CHole) for arg in [cexpr.cond, cexpr.e1, cexpr.e2]]):
            return [cexpr, cholder]
        t_held = copy.deepcopy(cexpr)
        t_holder = copy.deepcopy(cholder)
        t_held.cond = CHole()
        if isinstance(t_holder, CHole):
            t_holder = t_holder.plug(t_held)
        else:
            t_holder.plug(t_held)
        return find_hole(cexpr.cond, t_holder)
    return False
    
def CCinterp(jexpr):
    state = CCState(jexpr, CHole())
    # print(state.j.pp() + '  ///  ' + state.c.pp())
    while not (type(state.j) in [JNumber, JBool] and isinstance(state.c, CHole)):
        t = find_hole(state.c, CHole())
        if isinstance(state.j, JIf):
            state = CCState(state.j.cond, Cif0(state.j.tn, state.j.fn))
            # print(state.j.pp() + '  ///  ' + state.c.pp())
            continue
        if isinstance(state.j, JBool) and state.j.b == True:
            state = CCState(state.c.e1, CHole())
            # print(state.j.pp() + '  ///  ' + state.c.pp())
            continue
        if isinstance(state.j, JBool) and state.j.b == False:
            state = CCState(state.c.e2, CHole())
            # print(state.j.pp() + '  ///  ' + state.c.pp())
            continue
        if isinstance(state.j, JApp):
            tempargs = copy.deepcopy(state.j.args)
            tempargs[0] = CHole()
            if isinstance(state.c, CHole):
                state.c = state.c.plug(CApp(state.j.func, tempargs))
            else:
                state.c.plug(CApp(state.j.func, tempargs))
            state = CCState(state.j.args[0], state.c)
            # print(state.j.pp() + '  ///  ' + state.c.pp())
            continue
        if isinstance(state.j, JNumber) and isinstance(t[0], CApp) and not isinstance(t[0].args[len(t[0].args) - 1], CHole):
            t[0].args[t[0].hdex] = t[0].args[t[0].hdex].plug(state.j)
            state.j = t[0].args[t[0].hdex + 1]
            t[0].args[t[0].hdex + 1] = CHole()
            t[0].hdex += 1
            if isinstance(t[1], CHole):
                state.c = t[1].plug(t[0])
            else:
                state.c = t[1]
                state.c.plug(t[0])
            # print(state.j.pp() + '  ///  ' + state.c.pp())
            continue
        if isinstance(state.j, JNumber) and isinstance(t[0], CApp) and isinstance(t[0].args[len(t[0].args) - 1], CHole):
            state = CCState(delta(t[0].plug(state.j)), t[1])
            # print(state.j.pp() + '  ///  ' + state.c.pp())
            continue
    return state.c.plug(state.j)

def desugar(sexpr):
    # e = v
    if isinstance(sexpr, SeNum):
        return JNumber(sexpr.n)
    if isinstance(sexpr, SeStr) and isinstance(sexpr.s, bool):
        return JBool(sexpr.s)
    # e = (+ e e ...) | e = (* e e ...) 
    if (isinstance(sexpr, SeCons) and isinstance(sexpr.l, SeStr) and sexpr.l.s in ['+', '*'] and isinstance(sexpr.r, SeCons)):
        tempS = sexpr.r
        args = [desugar(tempS.l)]
        while not isinstance(tempS.r, SeEmp):
            tempS = tempS.r
            args.append(desugar(tempS.l))
        return JApp(JPrim(sexpr.l.s), args)
    # e = (e e ...)
    if isinstance(sexpr, SeCons) and isinstance(sexpr.l, SeStr) and isinstance(sexpr.r, SeCons) and isinstance(sexpr.r.r, SeCons) and isinstance(sexpr.r.r.r, SeEmp):
        return JApp(JPrim(sexpr.l.s), [desugar(sexpr.r.l), desugar(sexpr.r.r.l)])
    # e = (if e e e)
    if isinstance(sexpr, SeCons) and isinstance(sexpr.l, SeStr) and sexpr.l.s == 'if'  and isinstance(sexpr.r, SeCons)  and isinstance(sexpr.r.r, SeCons)  and isinstance(sexpr.r.r.r, SeCons) and isinstance(sexpr.r.r.r.r, SeEmp):
        return JIf(desugar(sexpr.r.l), desugar(sexpr.r.r.l), desugar(sexpr.r.r.r.l))
    # e = (+)
    if (isinstance(sexpr, SeCons) and isinstance(sexpr.l, SeStr) and sexpr.l.s == '+' and isinstance(sexpr.r, SeEmp)):
        return JNumber(0)
    # e = (*)
    if (isinstance(sexpr, SeCons) and isinstance(sexpr.l, SeStr) and sexpr.l.s == '*' and isinstance(sexpr.r, SeEmp)):
        return JNumber(1)
    return 'case error'

def SApp(op, l, r):
    return SeCons(op, SeCons(l, SeCons(r, SeEmp())))
    
def SIf(cond, tn, fn):
    return SeCons(SeStr('if'), SeCons(cond, SeCons(tn, SeCons(fn, SeEmp()))))
    
def find_redex(jexpr):
    #CHole
    if type(jexpr) in [JNumber, JBool, JPrim]:
        return False
    if isinstance(jexpr, JIf):
        #Cif0
        if not isinstance(jexpr.cond, JBool):
            return [Cif0(jexpr.tn, jexpr.fn), jexpr.cond]
        #all terms of JIf are simplified - no redex found
        return [CHole(), jexpr]
    if isinstance(jexpr, JApp):
        for i, arg in enumerate(jexpr.args):
            #Capp
            if not isinstance(arg, JNumber):
                tempargs = jexpr.args
                tempargs[i] = CHole()
                return [CApp(jexpr.func, tempargs), arg]
        #all terms of JApp are simplified - no redex found
        return [CHole(), jexpr]
        
def ssinterp(jexpr):
    t_context_redex = find_redex(jexpr)
    #if e = v return e    
    while(t_context_redex):
        context_redex = t_context_redex #if a redex is found, then C, e' = find_redex(e)
        context_redex[1] = step(context_redex[1]) #recursively call interp to check for more redexes inside e' or call step(e')
        jexpr = context_redex[0].plug(context_redex[1]) #plug hole with step(e')
        t_context_redex = find_redex(jexpr) #look for next redex in jexpr
    return jexpr #if no redex found in jexpr, call step of jexpr
    
def step(jexpr):
    #step(v) = v
    if type(jexpr) in [JNumber, JBool]:
        return jexpr
    if isinstance(jexpr, JApp):
        #step(v ... ((if) | (fn)) e ...) = (v .... step(arg) e ...)
        for i, arg in enumerate(jexpr.args):
            if type(arg) not in [JNumber, JBool]:
                jexpr.args[i] = step(arg)
                return jexpr
        #step(p v ...) = delta(e)
        return delta(jexpr)
    if isinstance(jexpr, JIf) and isinstance(jexpr.cond, JBool):
        #step(if true et ef) = et
        if (jexpr.cond.b):
            return jexpr.tn
        #step(if false et ef) = ef
        else:
            return jexpr.fn
    #step(if ((if) | (fn)) et ef) = (if step(cond) et ef)
    if isinstance(jexpr, JIf):
        return JIf(step(jexpr.cond), jexpr.tn, jexpr.fn)

def delta(JA):
    _func = JA.func.interp().p
    if (_func == '+'):
        sum = 0
        for arg in JA.args:
            sum = sum + arg.interp().n
        return JNumber(sum)
    if (_func == '*'):
        prd = 1
        for arg in JA.args:
            prd = prd * arg.interp().n
        return JNumber(prd)
    if (_func == '-'):
        if(len(JA.args) == 1):
            return JNumber(-1 * JA.args[1].interp().n)
        return JNumber(JA.args[0].interp().n - JA.args[1].interp().n)
    if (_func == '/'):
        return JNumber(JA.args[0].interp().n / JA.args[1].interp().n)
    if (_func == '<'):
        return JBool(JA.args[0].interp().n < JA.args[1].interp().n)
    if (_func == '>'):
        return JBool(JA.args[0].interp().n > JA.args[1].interp().n)
    if (_func == '=='):
        return JBool(JA.args[0].interp().n == JA.args[1].interp().n)
    if (_func == '<='):
        return JBool(JA.args[0].interp().n <= JA.args[1].interp().n)
    if (_func == '>='):
        return JBool(JA.args[0].interp().n >= JA.args[1].interp().n)
    if (_func == '!='):
        return JBool(JA.args[0].interp().n != JA.args[1].interp().n)


expected = [54, 24, 9, 10, 5, 0, 8, 12, 3, 3, 2, False, False, False, True, False, 4, 5, 3, 4]

test_values = [    
    SeNum(54),
    SApp(SeStr('*'), SeNum(4), SeNum(6)),
    SeCons(SeStr('+'), SeCons(SeNum(4), SeCons(SeCons(SeStr('+'), SeCons(SeNum(3), SeCons(SeNum(2), SeEmp()))), SeEmp()))),
    SeCons(SeStr('+'), SeCons(SeNum(4), SeCons(SeCons(SeStr('+'), SeCons(SeNum(3), SeCons(SeCons(SeStr('+'), SeCons(SeNum(2), SeCons(SeNum(1), SeEmp()))), SeEmp()))), SeEmp())))
    ,
    SApp(SeStr('+'), SApp(SeStr('*'), SeNum(2), SeNum(2)), SApp(SeStr('-'), SeNum(2), SeNum(1))),
    SeCons(SeStr('+'), SeEmp()),
    SeCons(SeStr('+'), SeCons(SeNum(8), SeEmp())),
    SApp(SeStr('+'), SeNum(4), SeNum(8)),
    SeCons(SeStr('+'), SeCons(SeNum(1), SeCons(SeNum(1), SeCons(SeNum(1), SeEmp())))),
    SApp(SeStr('/'), SeNum(9), SeNum(3)),
    SApp(SeStr('-'), SeNum(13), SeNum(11)),
    SApp(SeStr('<='), SeNum(5), SeNum(3)),
    SApp(SeStr('<'), SeNum(12), SeNum(12)),
    SApp(SeStr('=='), SeNum(4), SeNum(8)),
    SApp(SeStr('>'), SeNum(2), SeNum(1)),
    SApp(SeStr('>='), SeNum(7), SeNum(16)),
    SIf(SeStr(True), SeNum(4), SeNum(5)),
    SIf(SeStr(False), SeNum(4), SeNum(5)),
    SIf(SApp(SeStr('>'), SeNum(4), SeNum(5)), SeNum(9), SeNum(3)),
    SIf(SApp(SeStr('=='), SeNum(4), SeNum(4)), SApp(SeStr('*'), SeNum(2), SeNum(2)), SeNum(3))   
]

for index, value in enumerate(test_values):
    # print(find_hole(CApp(JPrim('+'), [JNumber(4), CApp(JPrim('+'), [JNumber(5), CApp(JPrim('+'), [JNumber(6), CHole()])])]), CHole()))
    # print('printed: ' + desugar(value).pp(), '\nbig-step result: ' + desugar(value).interp().pp(), '\nsmall-step result: ' + ssinterp(desugar(value)).pp(), '\nexpected: ' + str(expected[index]) + '\n')
    print('printed: ' + desugar(value).pp(), '\nbig-step result: ' + desugar(value).interp().pp(), '\ncc0 result: ' + CCinterp(desugar(value)).pp(), '\nexpected: ' + str(expected[index]) + '\n')
    