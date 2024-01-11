#include <iostream>  
#include <string.h>  


extern "C"
{
#include "lua.h"  
#include "lauxlib.h"  
#include "lualib.h"  
}

void print_line()
{
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
}

// 栈顶是 -1 , 栈底是 1

// base use
void test_01()
{
    using namespace std;
    //1.创建一个state  
    lua_State* L = luaL_newstate();

    //2.入栈操作  
    lua_pushstring(L, "I am so cool~");
    lua_pushnumber(L, 20);

    //3.取值操作  
    // if (lua_isstring(L, 1)) {             //判断是否可以转为string  
    //     cout << lua_tostring(L, 1) << endl;  //转为string并返回  
    // }
    // if (lua_isnumber(L, 2)) {
    //     cout << lua_tonumber(L, 2) << endl;
    // }


    if (lua_isnumber(L,-1))
    {
        cout << lua_tonumber(L, -1) << endl;;
    }
    if (lua_isstring(L,-2))
    {
        cout << lua_tostring(L, -2) << endl;
    }


    //4.关闭state  
    lua_close(L);
}

// load lua + run
void test_02()
{
    using namespace std;


    //1.创建Lua状态  
    lua_State* L = luaL_newstate();
    if (L == NULL)
    {
        return;
    }

    //2.加载Lua文件  
    int bRet = luaL_loadfile(L, "hello.lua");
    if (bRet)
    {
        cout << "load file error" << endl;
        return;
    }

    //3.运行Lua文件  
    bRet = lua_pcall(L, 0, 0, 0);
    if (bRet)
    {
        cout << "pcall error" << endl;
        return;
    }

    //4.读取变量  
    lua_getglobal(L, "str");
    string str = lua_tostring(L, -1);
    cout << "str = " << str.c_str() << endl;        //str = I am so cool~  

    //5.读取table  
    lua_getglobal(L, "tbl");
    lua_getfield(L, -1, "name");
    str = lua_tostring(L, -1);
    cout << "tbl:name = " << str.c_str() << endl; //tbl:name = cyc  

    //6.读取函数  
    lua_getglobal(L, "add");        // 获取函数，压入栈中  
    lua_pushnumber(L, 10);          // 压入第一个参数  
    lua_pushnumber(L, 20);          // 压入第二个参数

    // 调用函数，调用完成以后，会将返回值压入栈中，2表示参数个数，1表示返回结果个数。  
    int iRet = lua_pcall(L, 2, 1, 0);
    if (iRet)                       // 调用出错  
    {
        const char* pErrorMsg = lua_tostring(L, -1);
        cout << pErrorMsg << endl;
        lua_close(L);
        return;
    }
    if (lua_isnumber(L, -1))        //取值输出  
    {
        double fValue = lua_tonumber(L, -1);
        cout << "Result is " << fValue << endl;
    }

    //至此，栈中的情况是：  
    //=================== 栈顶 ===================   
    //  索引  类型      值  
    //   4   int：      30   
    //   3   string：   shun   
    //   2   table:     tbl  
    //   1   string:    I am so cool~  
    //=================== 栈底 ===================   

    // 将需要设置的值设置到栈中  
    // lua_pushstring(L, "我是一个大帅锅～");
    // 将这个值设置到table中（此时tbl在栈的位置为2）  
    // lua_setfield(L, 2, "name");

    // 创建一个新的table，并压入栈  
    // lua_newtable(L);
    // 往table中设置值  
    // lua_pushstring(L, "Give me a girl friend !"); //将值压入栈  
    // lua_setfield(L, -2, "str"); //将值设置到table中，并将Give me a girl friend 出栈

    //7.关闭state  
    lua_close(L);
    return;
}

// 此函数会被注册到Lua中;
static int average(lua_State* L)
{
    /* 得到参数个数 */
    int n = lua_gettop(L);
    double sum = 0;
    int i;

    /* 循环求参数之和 */
    for (i = 1; i <= n; i++)
    {
        /* 求和 */
        sum += lua_tonumber(L, i);
    }
    /* 压入平均值 */
    lua_pushnumber(L, sum / n);
    /* 压入和 */
    lua_pushnumber(L, sum);
    /* 返回返回值的个数 */
    return 2;
}
void test_03()
{
    /* 初始化Lua */
    lua_State* L = lua_open();

    /* 载入Lua基本库 */
    luaL_openlibs(L);
    /* 注册函数 */
    lua_register(L, "average", average);
    /* 运行脚本,在此脚本中会执行上面注册的函数 */
    luaL_dofile(L, "avg.lua");
    /* 清除Lua */
    lua_close(L);

}


// 
void test_04()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    int ret = luaL_loadfile(L, "base.lua");

    if (ret != 0)
    {
        printf("load lua file failed \n");
        return;
    }

    lua_pcall(L, 0, 0, 0);

    lua_getglobal(L, "name");
    lua_getglobal(L, "age");

    //
    int age = lua_tointeger(L, -1);
    const char* name = lua_tostring(L, -2);

    printf("name = %s | age = %d \n", name, age);

    lua_close(L);
}

// lua function + stack
void test_05()
{
    lua_State* L = luaL_newstate();

    if (luaL_loadfile(L, "base.lua") != 0)
    {
        printf("lua load file failed \n");
        return;
    }
    // 执行文件
    lua_pcall(L, 0, 0, 0);

    // 函数入栈
    lua_getglobal(L, "add");
    lua_pushnumber(L, 10);
    lua_pushnumber(L, 20);

    // 打印栈
    for (int i = 1; i <= 3; ++i)
    {
    	double tmp =  lua_tonumber(L, -i);
        printf("index:%d | value:%f \n", -i, tmp);
    }

    // 调用函数
    lua_pcall(L, 2, 1, 0);

    // 在栈顶获取返回值
    int result = lua_tointeger(L, -1);
    printf("the function result is : %d \n", result);

    for (int i = 1; i <= 3; ++i)
    {
        double tmp = lua_tonumber(L, -i);
        printf("index:%d | value:%f \n", -i, tmp);
    }



    lua_close(L);
}


// lua table
void test_06()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, "base.lua") != 0)
    {
	    return;
    }

    lua_pcall(L, 0, 0, 0);



    // 将全局变量mytable压入栈
    lua_getglobal(L, "mytable");

    // 压入表中的key
    lua_pushstring(L, "name");

    // 从栈顶取出index(1)个元素,然后在table中查找值,并将结果返回到栈顶
    lua_gettable(L, 1);
    //
    const char* name = lua_tostring(L, -1);
    printf("get name form table value is : %s \n", name);


    lua_pushstring(L, "id");
    lua_gettable(L, 1);
    int id = lua_tointeger(L, -1);
    printf("get id from table value is : %d \n", id);


    lua_close(L);
}
void test_07()
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    if (luaL_loadfile(L,"base.lua") != 0)
    {
	    return;
    }

    lua_pcall(L, 0, 0, 0);

    lua_getglobal(L, "mytable");
    lua_getfield(L, 1, "name");

    const char* name = lua_tostring(L, -1);
    printf("lua get table name : %s \n", name);


    lua_close(L);
}


// lua_getglobal(L, "var")会执行两步操作：1.将var放入栈中，2.由Lua去寻找变量var的值，并将变量var的值返回栈顶（替换var）。
// lua_getfield(L, -1, "name")的作用等价于 lua_pushstring(L, "name") + lua_gettable(L, -2)


// call dll
void test_08()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, "dll_use.lua");

    lua_close(L);
}

int main()
{
    test_08();

    return 1;
}