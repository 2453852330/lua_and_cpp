-- n 即为 upvalue
function f1(n)
    local function f2()
        print(n) -- 调用外层变量n
    end

    local function f3()
        n = n + 10
    end

    return f2,f3
end

-- upvalue 是共享的
local g1,g2 =  f1(1024)

g1()  -- 1024
g2()  -- 1024 + 10
g1()  -- 1034