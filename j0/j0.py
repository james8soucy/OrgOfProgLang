class JNumber:
    def __init__(self, _n):
        self.n = _n
    def pp(self):
        return str(self.n)

class JPlus:
    def __init__(self, l, r):
        self.left = l
        self.right = r
    def pp(self):
        return "( " + self.l.pp() + " + " self.r.pp() + " )"

class JMult:
    def __init__(self, l, r):
        self.left = l
        self.right = r
    def pp(self):
        return "( " + self.l.pp() + " * " self.r.pp() + " )"