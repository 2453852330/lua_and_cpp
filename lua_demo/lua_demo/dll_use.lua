require "myLuaLib"

local ave, sum = ss.average(1, 2, 3, 4, 5)
print("call dll's sum function, the sum:", sum, " the average:", ave)

ss.sayHello()
