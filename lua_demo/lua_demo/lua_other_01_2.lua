-- n 即为 upvalue
function f1(n)
    local function f2()
        print(n)    -- 调用外层变量n
    end

    n = n + 10

    return f2
end

g1 = f1(1024)  -- 同一闭包内共享 upvalue n 

g1()  -- print 1034