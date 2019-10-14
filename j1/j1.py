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
        return "(fn " + self.func.pp() + ", " + str([arg.pp() for arg in self.args]) + ")"
    def interp(self):
        _func = self.func.interp().p
        if (_func == '+'):
            sum = 0
            for arg in self.args:
                sum = sum + arg.interp().n
            return JNumber(sum)
        if (_func == '*'):
            prd = 1
            for arg in self.args:
                prd = prd * arg.interp().n
            return JNumber(prd)
        if (_func == '-'):
            if(len(self.args) == 1):
                return JNumber(-1 * self.args[1].interp().n)
            return JNumber(self.args[0].interp().n - self.args[1].interp().n)
        if (_func == '/'):
            return JNumber(self.args[0].interp().n / self.args[1].interp().n)
        if (_func == '<'):
            return JBool(self.args[0].interp().n < self.args[1].interp().n)
        if (_func == '>'):
            return JBool(self.args[0].interp().n > self.args[1].interp().n)
        if (_func == '=='):
            return JBool(self.args[0].interp().n == self.args[1].interp().n)
        if (_func == '<='):
            return JBool(self.args[0].interp().n <= self.args[1].interp().n)
        if (_func == '>='):
            return JBool(self.args[0].interp().n >= self.args[1].interp().n)
        if (_func == '!='):
            return JBool(self.args[0].interp().n != self.args[1].interp().n)
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

#C := hole | (if C e e) | (if e C e) | (if e e C) | (e ... C ... e)
class CHole:
    def __init__(self):
        self.h = None
    def plug(self, p):
        return p
class Cif0:
    def __init__(self, e1, e2):
        self.e1 = e1
        self.e2 = e2
    def plug(self, cond):
        return JIf(cond, self.e1, self.e2)
class Cif1:
    def __init__(self, e0, e2):
        self.e0 = e0
        self.e2 = e2
    def plug(self, tn):
        return JIf(self.e0, tn, self.e2)
class Cif2:
    def __init__(self, e0, e1):
        self.e0 = e0
        self.e1 = e1
    def plug(self, fn):
        return JIf(self.e0, self.e1, fn)
class CApp:
    def __init__(self, args):
        self.func = func
        for i, item in enumerate(args):
            if isinstance(args, CHole):
                self.hdex = i
    def plug(self, p):
        self.args[self.hdex] = p
        
def desugar(sexpr):
    # e = v
    if isinstance(sexpr, SeNum):
        return JNumber(sexpr.n)
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
    #no redex found
    if type(jexpr) in [JNumber, JBool, JPrim]:
        return False
    if isinstance(jexpr, JIf):
        #Cif0
        if not isinstance(jexpr.cond, JBool):
            return [Cif0(jexpr.tn, jexpr.fn), jexpr.cond]
        #Cif1
        if type(jexpr.tn) not in [JNumber, JBool, JPrim]:
            return [Cif1(jexpr.cond, jexpr.fn), jexpr.tn]
        #Cif2
        if type(jexpr.fn) not in [JNumber, JBool, JPrim]:
            return [Cif2(jexpr.cond, jexpr.tn), jexpr.fn]
        #all terms of JIf are simplified - no redex found
        return False
    if isinstance(jexpr, JApp):
        for i, arg in enumerate(jexpr.args):
            #Capp
            if not isinstance(arg, JNumber):
                tempargs = jexpr.args
                tempargs[i] = CHole()
                return [CApp(tempargs), arg]
        #all terms of JApp are simplified - no redex found
        return False

expected = [54, 0, 8, 12, 3, 24, 3, 2, False, False, False, True, False, 3, 4]

test_values = [    
    SeNum(54),
    SeCons(SeStr('+'), SeEmp()),
    SeCons(SeStr('+'), SeCons(SeNum(8), SeEmp())),
    SApp(SeStr('+'), SeNum(4), SeNum(8)),
    SeCons(SeStr('+'), SeCons(SeNum(1), SeCons(SeNum(1), SeCons(SeNum(1), SeEmp())))),
    SApp(SeStr('*'), SeNum(4), SeNum(6)),
    SApp(SeStr('/'), SeNum(9), SeNum(3)),
    SApp(SeStr('-'), SeNum(13), SeNum(11)),
    SApp(SeStr('<='), SeNum(5), SeNum(3)),
    SApp(SeStr('<'), SeNum(12), SeNum(12)),
    SApp(SeStr('=='), SeNum(4), SeNum(8)),
    SApp(SeStr('>'), SeNum(2), SeNum(1)),
    SApp(SeStr('>='), SeNum(7), SeNum(16)),
    SIf(SApp(SeStr('>'), SeNum(4), SeNum(5)), SeNum(9), SeNum(3)),
    SIf(SApp(SeStr('=='), SeNum(4), SeNum(4)), SApp(SeStr('*'), SeNum(2), SeNum(2)), SeNum(3))   
]

for index, value in enumerate(test_values):
    print('printed: ' + desugar(value).pp(), '\nresult: ' + desugar(value).interp().pp(), '\nexpected: ' + str(expected[index]) + '\n')  