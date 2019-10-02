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
        
test_values = [
    SeCons(SeStr('+'), SeCons(SeNum(6), SeCons(SeCons(SeStr('*'), SeCons(SeNum(4), SeCons(SeNum(3), SeEmp()))), SeEmp()))),
    SeCons(SeStr('*'), SeCons(SeCons(SeStr('+'), SeCons(SeNum(9), SeCons(SeNum(8), SeEmp()))), SeCons(SeCons(SeStr('+'), SeCons(SeNum(2), SeCons(SeCons(SeStr('+'), SeCons(SeNum(3), SeCons(SeNum(4), SeEmp()))), SeEmp()))), SeEmp()))),
    SeCons(SeStr('+'), SeCons(SeNum(4), SeCons(SeCons(SeStr('+'), SeCons(SeNum(4), SeCons(SeNum(9), SeEmp()))), SeEmp()))),
    SeCons(SeStr('*'), SeCons(SeCons(SeStr('+'), SeCons(SeNum(9), SeCons(SeNum(4), SeEmp()))), SeCons(SeNum(11), SeEmp()))),
    SeNum(9),
    SeCons(SeStr('+'), SeCons(SeNum(4), SeCons(SeNum(9), SeEmp()))),
    SeCons(SeStr('*'), SeCons(SeCons(SeStr('*'), SeCons(SeNum(5), SeCons(SeNum(9), SeEmp()))), SeCons(SeCons(SeStr('*'), SeCons(SeNum(3), SeCons(SeNum(11), SeEmp()))), SeEmp()))),
    SeCons(SeStr('+'), SeCons(SeCons(SeStr('*'), SeCons(SeNum(3), SeCons(SeNum(9), SeEmp()))), SeCons(SeNum(2), SeEmp()))),
    SeCons(SeStr('*'), SeCons(SeCons(SeStr('*'), SeCons(SeNum(4), SeCons(SeNum(2), SeEmp()))), SeCons(SeNum(8), SeEmp()))),
    SeCons(SeStr('+'), SeCons(SeNum(3), SeCons(SeCons(SeStr('*'), SeCons(SeNum(5), SeCons(SeNum(8), SeEmp()))), SeEmp()))),
    SeCons(SeStr('+'), SeCons(SeCons(SeStr('*'), SeCons(SeNum(4), SeCons(SeNum(3), SeEmp()))), SeCons(SeNum(13), SeEmp()))),
    SeCons(SeStr('*'), SeCons(SeCons(SeStr('+'), SeCons(SeNum(3), SeCons(SeNum(9), SeEmp()))), SeCons(SeNum(12), SeEmp())))
]  

for value in test_values:
    print((value).interp())
    

