class JNumber:
    def __init__(self, _n):
        self.n = _n
    def pp(self):
        return str(self.n)
    def interp(self):
        return self.n

class JPlus:
    def __init__(self, l, r):
        self.l = l
        self.r = r
    def pp(self):
        return "( " + self.l.pp() + " + " + self.r.pp() + " )"
    def interp(self):
        return self.l.interp() + self.r.interp()

class JMult:
    def __init__(self, l, r):
        self.l = l
        self.r = r
    def pp(self):
        return "( " + self.l.pp() + " * " + self.r.pp() + " )"
    def interp(self):
        return self.l.interp() * self.r.interp()


test_values = [
    JPlus(JNumber(6), JMult(JNumber(4), JNumber(3))), #18
    JMult(JPlus(JNumber(9), JNumber(8)), JPlus(JNumber(2), JPlus(JNumber(3), JNumber(4)))), #153
    JPlus(JNumber(4), JPlus(JNumber(4), JNumber(9))), #17
    JMult(JPlus(JNumber(9), JNumber(4)), JNumber(11)), #143
    JNumber(9), #9
    JPlus(JNumber(4), JNumber(9)), #13 
    JMult(JMult(JNumber(5), JNumber(9)), JMult(JNumber(3), JNumber(11))), #1485 
    JPlus(JMult(JNumber(3), JNumber(9)), JNumber(2)), #29
    JMult(JMult(JNumber(4), JNumber(2)), JNumber(8)), #64 
    JPlus(JNumber(3), JMult(JNumber(5), JNumber(8))), #43
    JPlus(JMult(JNumber(4), JNumber(3)), JNumber(13)), #25
    JMult(JPlus(JNumber(3), JNumber(9)), JNumber(12)) #144
]

for value in test_values:
    print(value.interp())