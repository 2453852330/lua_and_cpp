-- n 即为 upvalue
function f1(n)
    local function foo()
        local function f2()
            print(n) -- 调用外层变量n
        end

        local function f3()
            print("+10")
            n = n + 10
        end

        return f2,f3
    end

    return foo
end

-- upvalue 转移

local t = f1(1024)

local f2,f3 = t()

f2()  -- 1024
f3()  -- + 10
f2()  -- 1034

print("recall t()") 

local g1,g2 = t()

g1() -- 1034
g2() -- + 10
g1() -- 1044

f2() -- 1044

-- 因为g1和g2与f1和f2都是同一个闭包t 创建的，
-- 所以它们引用的upvalue  (变量n)实际也是同一个变量
-- 而它们的upvalue引用都会指向同一个地方。