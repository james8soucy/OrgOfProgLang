# J1
# e = v | (e e ...) | (if e e e)
# v = number | bool | prim

class JNumber:
    def __init__(self, n):
        self.n = n
    def pp():
        return str(n)
class JEmp:
    def __init__(self):
        pass
    def pp():
        return "{}"
class JCons:
    def __init__(self, l, r):
        self.l = l
        self.r = r
    def pp():
        return "(" + self.l.pp() + ", " + self.r.pp() + ")"
class JIf:
    def __init__(self, cond, tn, fn):
        self.cond = cond
        self.tn = tn
        self.fn = fn
    def pp():
        return "(if " + cond.pp() + ", " + tn.pp() + ", " + fn.pp() + ")"
class JBool:
    def __init__(self, b):
        self.b = b
    def pp():
        return str(b)
class JPrim:
    def __init__(self, p):
        self.p = p
    def pp():
        return str(p)
    
class JApp:
    def __init__(self, func, args):
        self.func = func
        self.args = args
    def pp():
        return "(fn " + self.func.pp() + ", " + self.args.pp() + ")"
        
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
    print(desugar(value).interp(), expected[index])  