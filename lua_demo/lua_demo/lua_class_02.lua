function Base(name)
    local a = {}

    a.hello = function()
        print("Base hello function called , name:", a.name)
    end

    a.name = name

    return a
end

local b1 = Base("A")
b1.hello()

local b2 = Base("B")
b2:hello()

-- child
function Child(name,age)
    local b = Base(name)

    b.world = function()
        print("Child world function called , name:", b.name, "age:", b.age)
    end

    -- override
    b.hello = function()
        print("Child hello function called , name:", b.name, "age:", b.age)
    end

    b.age = age

    return b
end

-- 比较好的设置随机数种子的方式
math.randomseed(tostring(os.time()):reverse():sub(1,7))

print("test child")

local b1 = Child("C",math.random(100))
b1.hello()
b1.world()

local b2 = Child("D",math.random(100))
b2.hello()
b2.world()
