local p = point.new()

point.set(p, math.random(), math.random(), math.random())

local x, y, z = point.get(p)
print(x, y, z)
