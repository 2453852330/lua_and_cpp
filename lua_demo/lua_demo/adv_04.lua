local base = {}

local meta_base = {}

setmetatable(base,meta_base)

-- 将原表的__index设置为自身,可以实现 : 调用
meta_base.__index = meta_base

meta_base.hello = function ()
    print("meta_base hello function called")
end


base:hello()


