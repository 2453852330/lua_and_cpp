mytable = {
    name = "hello",
    age = 12
}

function testA()
    print("test a function called in lua")
end

function print_table()
    print("my table good :", mytable.good, " this is set in cpp")
    print("mytable name :", mytable.name)
end
