-- parent
local Base = {}


Base.hello = function ()
    print("base hello function called")
end

Base.new = function ()
    local tab = {}
    for key, value in pairs(Base) do
        tab[key] = value
    end
    return tab
end

-- child

local Child = {}

Child.new = function ()
    local tab = Base.new()
    for key, value in pairs(Child) do
        tab[key] = value
    end
    return tab
end

-- override
Child.hello = function ()
    print("child hello function called")
end

-- new function
Child.world = function ()
    print("child world function called")
end


-- test

local b1 = Base.new()
b1.hello()
b1:hello()

print("test child")

local c1 = Child.new()
c1.hello()
c1:world()