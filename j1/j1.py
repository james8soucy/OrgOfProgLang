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
    
      