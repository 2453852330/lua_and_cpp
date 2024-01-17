local mytab = {1, 2, 3, 4, 5}
local mytab2 = {7, 9}

local metaTab = {}
-- 只有两个参数有效, a是加号左边的 b是加号右边的
metaTab.__add = function(a, b)
    print("__add function called", #a, #b)
    local tab = {}
    local add
    for i = 1, #a do
        if i > #b then
            add = 0
        else
            add = b[i]
        end
        tab[i] = a[i] + add
    end
    return tab
end

setmetatable(mytab, metaTab)

local tab3 = mytab + mytab2 -- 5 2

for index, value in ipairs(tab3) do
    print(index, ":", value)
end

local tab4 = mytab2 + mytab -- 2 5

for index, value in ipairs(tab4) do
    print(index, ":", value)
end
