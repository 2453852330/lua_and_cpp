local base = FBase.new()
FBase.set(base, "A", 12)
FBase.log(base)
base = nil


local b2 = FBase.new()
FBase.set(b2, "B", 13)
FBase.log(b2)
b2:testCall()


local b3 = FBase.new();
b3:set("C",14)
b3:log()

print(b3)