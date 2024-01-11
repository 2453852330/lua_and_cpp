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

// ջ���� -1 , ջ���� 1

// base use
void test_01()
{
    using namespace std;
    //1.����һ��state  
    lua_State* L = luaL_newstate();

    //2.��ջ����  
    lua_pushstring(L, "I am so cool~");
    lua_pushnumber(L, 20);

    //3.ȡֵ����  
    // if (lua_isstring(L, 1)) {             //�ж��Ƿ����תΪstring  
    //     cout << lua_tostring(L, 1) << endl;  //תΪstring������  
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


    //4.�ر�state  
    lua_close(L);
}

// load lua + run
void test_02()
{
    using namespace std;


    //1.����Lua״̬  
    lua_State* L = luaL_newstate();
    if (L == NULL)
    {
        return;
    }

    //2.����Lua�ļ�  
    int bRet = luaL_loadfile(L, "hello.lua");
    if (bRet)
    {
        cout << "load file error" << endl;
        return;
    }

    //3.����Lua�ļ�  
    bRet = lua_pcall(L, 0, 0, 0);
    if (bRet)
    {
        cout << "pcall error" << endl;
        return;
    }

    //4.��ȡ����  
    lua_getglobal(L, "str");
    string str = lua_tostring(L, -1);
    cout << "str = " << str.c_str() << endl;        //str = I am so cool~  

    //5.��ȡtable  
    lua_getglobal(L, "tbl");
    lua_getfield(L, -1, "name");
    str = lua_tostring(L, -1);
    cout << "tbl:name = " << str.c_str() << endl; //tbl:name = cyc  

    //6.��ȡ����  
    lua_getglobal(L, "add");        // ��ȡ������ѹ��ջ��  
    lua_pushnumber(L, 10);          // ѹ���һ������  
    lua_pushnumber(L, 20);          // ѹ��ڶ�������

    // ���ú�������������Ժ󣬻Ὣ����ֵѹ��ջ�У�2��ʾ����������1��ʾ���ؽ��������  
    int iRet = lua_pcall(L, 2, 1, 0);
    if (iRet)                       // ���ó���  
    {
        const char* pErrorMsg = lua_tostring(L, -1);
        cout << pErrorMsg << endl;
        lua_close(L);
        return;
    }
    if (lua_isnumber(L, -1))        //ȡֵ���  
    {
        double fValue = lua_tonumber(L, -1);
        cout << "Result is " << fValue << endl;
    }

    //���ˣ�ջ�е�����ǣ�  
    //=================== ջ�� ===================   
    //  ����  ����      ֵ  
    //   4   int��      30   
    //   3   string��   shun   
    //   2   table:     tbl  
    //   1   string:    I am so cool~  
    //=================== ջ�� ===================   

    // ����Ҫ���õ�ֵ���õ�ջ��  
    // lua_pushstring(L, "����һ����˧����");
    // �����ֵ���õ�table�У���ʱtbl��ջ��λ��Ϊ2��  
    // lua_setfield(L, 2, "name");

    // ����һ���µ�table����ѹ��ջ  
    // lua_newtable(L);
    // ��table������ֵ  
    // lua_pushstring(L, "Give me a girl friend !"); //��ֵѹ��ջ  
    // lua_setfield(L, -2, "str"); //��ֵ���õ�table�У�����Give me a girl friend ��ջ

    //7.�ر�state  
    lua_close(L);
    return;
}

// �˺����ᱻע�ᵽLua��;
static int average(lua_State* L)
{
    /* �õ��������� */
    int n = lua_gettop(L);
    double sum = 0;
    int i;

    /* ѭ�������֮�� */
    for (i = 1; i <= n; i++)
    {
        /* ��� */
        sum += lua_tonumber(L, i);
    }
    /* ѹ��ƽ��ֵ */
    lua_pushnumber(L, sum / n);
    /* ѹ��� */
    lua_pushnumber(L, sum);
    /* ���ط���ֵ�ĸ��� */
    return 2;
}
void test_03()
{
    /* ��ʼ��Lua */
    lua_State* L = lua_open();

    /* ����Lua������ */
    luaL_openlibs(L);
    /* ע�ắ�� */
    lua_register(L, "average", average);
    /* ���нű�,�ڴ˽ű��л�ִ������ע��ĺ��� */
    luaL_dofile(L, "avg.lua");
    /* ���Lua */
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
    // ִ���ļ�
    lua_pcall(L, 0, 0, 0);

    // ������ջ
    lua_getglobal(L, "add");
    lua_pushnumber(L, 10);
    lua_pushnumber(L, 20);

    // ��ӡջ
    for (int i = 1; i <= 3; ++i)
    {
    	double tmp =  lua_tonumber(L, -i);
        printf("index:%d | value:%f \n", -i, tmp);
    }

    // ���ú���
    lua_pcall(L, 2, 1, 0);

    // ��ջ����ȡ����ֵ
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



    // ��ȫ�ֱ���mytableѹ��ջ
    lua_getglobal(L, "mytable");

    // ѹ����е�key
    lua_pushstring(L, "name");

    // ��ջ��ȡ��index(1)��Ԫ��,Ȼ����table�в���ֵ,����������ص�ջ��
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


// lua_getglobal(L, "var")��ִ������������1.��var����ջ�У�2.��LuaȥѰ�ұ���var��ֵ����������var��ֵ����ջ�����滻var����
// lua_getfield(L, -1, "name")�����õȼ��� lua_pushstring(L, "name") + lua_gettable(L, -2)


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