-- 用来测试 lua 调用 cpp 函数
-- 这个函数被声明在cpp中,然后注册到lua中;
avg, sum = average(10, 20, 30, 40, 50)  
print("The average is ", avg)  
print("The sum is ", sum)