local stu1 = student.new()

local info = student.test()
print(info)

-- student.log(stu1)

student.setName(stu1, "hello")
student.setAge(stu1, 12)
student.setScore(stu1, 6.6)

local name,age,score = student.log(stu1)
print(name,age,score)
