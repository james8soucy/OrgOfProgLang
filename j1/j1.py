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
        return "(fn " + self.func.pp() + ", " + self.args.pp() + ")"
    def interp(self):
        _func = self.func.interp().p
        _args = [self.args.interp().l.n, self.args.interp().r.l.n]
        if (_func == '+'):
            return JNumber(_args[0] + _args[1])
        if (_func == '*'):
            return JNumber(_args[0] * _args[1])
        if (_func == '-'):
            if(isinstance(_args[1]), JEmp):
                return JNumber(-1 * _args[1])
            return JNumber(_args[0] - _args[1])
        if (_func == '/'):
            return JNumber(_args[0] / _args[1])
        if (_func == '<'):
            return JBool(_args[0] < _args[1])
        if (_func == '>'):
            return JBool(_args[0] > _args[1])
        if (_func == '=='):
            return JBool(_args[0] == _args[1])
        if (_func == '<='):
            return JBool(_args[0] <= _args[1])
        if (_func == '>='):
            return JBool(_args[0] >= _args[1])
        if (_func == '!='):
            return JBool(_args[0] != _args[1])
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
        
def desugar(sexpr):
    # e = v
    if isinstance(sexpr, SeNum):
        return JNumber(sexpr.n)
    # e = (e e ...)
    if isinstance(sexpr, SeCons) and isinstance(sexpr.l, SeStr) and isinstance(sexpr.r, SeCons) and isinstance(sexpr.r.r, SeCons) and isinstance(sexpr.r.r.r, SeEmp):
        return JApp(JPrim(sexpr.l.s), JCons(desugar(sexpr.r.l), JCons(desugar(sexpr.r.r.l), JEmp())))
    # e = (if e e e)
    if isinstance(sexpr, SeCons) and isinstance(sexpr.l, SeStr) and sexpr.l.s == 'if'  and isinstance(sexpr.r, SeCons)  and isinstance(sexpr.r.r, SeCons)  and isinstance(sexpr.r.r.r, SeCons) and isinstance(sexpr.r.r.r.r, SeEmp):
        return JIf(desugar(sexpr.r.l), desugar(sexpr.r.r.l), desugar(sexpr.r.r.r.l))
    return 'case error'

def SApp(op, l, r):
    return SeCons(op, SeCons(l, SeCons(r, SeEmp())))
    
def SIf(cond, tn, fn):
    return SeCons(SeStr('if'), SeCons(cond, SeCons(tn, SeCons(fn, SeEmp()))))
    
expected = [54, 12, 24, 3, 2, JBool(False), JBool(False), JBool(False), JBool(True), JBool(False), 3, 4]

test_values = [    
    SeNum(54),
    SApp(SeStr('+'), SeNum(4), SeNum(8)),
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
    print(desugar(value).pp(), desugar(value).interp().pp())  