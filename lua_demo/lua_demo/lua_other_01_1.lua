-- n 即为 upvalue
function f1(n)
    local function f2()
        print(n)    -- 调用外层变量n
    end
    return f2
end

g1 = f1(1024) -- g1 会保持f2()的生命,导致upvalue n 不会被释放
print("test 1024")
g1() -- 可以在这里继续使用 n 


g2 = f1(500)
print("test 500")
g2()