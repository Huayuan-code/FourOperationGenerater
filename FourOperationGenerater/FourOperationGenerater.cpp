#include <iostream>
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime> //
#include<stdio.h>
using namespace std;


// ---------分数定义
class Fraction
{
public:
    long long inte; //整数部分
    long long nume; // 分子
    long long deno; // 分母

    Fraction();
    Fraction(long long range);
    void show();
};

Fraction::Fraction()
{
    long long range = 100;
    inte = rand() % range;
    deno = rand() % range + 1;
    nume = rand() % deno + 1;
    if (nume == deno) nume--;
    if (nume == 0) nume++, deno++;
}

Fraction::Fraction(long long range)
{
    inte = rand() % range;
    deno = rand() % range + 1;
    nume = rand() % deno + 1;
    if (nume == deno) nume--;
    if (nume == 0) nume++, deno++;
}

void Fraction::show()
{
    if (inte != 0) printf("%lld'", inte);
    printf("%lld/%lld", nume, deno);
}

//-----------数字定义
class Number
{
public:
    int type; // 1:interger, 2:fraction
    long long inte;
    Fraction frac;

    Number();
    Number(long long range);
    void show();
};

Number::Number()
{}

Number::Number(long long range)
{
    type = rand() % 2 + 1;
    inte = rand() % range;
    frac = Fraction(range);
}

void Number::show()
{
    if (type == 1) printf("%lld", inte);
    else if (type == 2) frac.show();

}

//---------一类表达式定义
class Expression1
{
public:
    Number num1;
    Number num2;
    char op;

    Expression1();
    Expression1(long long range);
    void show();
};

Expression1::Expression1()
{}

Expression1::Expression1(long long range)
{
    num1 = Number(range);
    num2 = Number(range);
    op = rand() % 4 + 1;
    if (op == 1) op = '+';
    else if (op == 2) op = '-';
    else if (op == 3) op = '*';
    else if (op == 4) op = '|';
}

void Expression1::show()
{
    num1.show();
    cout << " " << op << " ";
    num2.show();
}

//----二类表达式定义

class Expression2
{
public:
    long long inte;
    Expression1 exp;
    char op;

    Expression2();
    Expression2(long long range);
    void show();
    
};

Expression2::Expression2()
{
}

Expression2::Expression2(long long range)
{
    inte = rand() % range + 1;
    exp = Expression1(range);
    op = rand() % 4 + 1;
    if (op == 1) op = '+';
    else if (op == 2) op = '-';
    else if (op == 3) op = '*';
    else if (op == 4) op = '|';
}

void Expression2::show()
{
    printf("%lld %c (", inte, op);
    exp.show();
    printf(")");
}


int main()
{
    unsigned seed = time(0);
    srand(seed);
    
    for (int i = 0; i < 100; i++)
    {
        Expression2 num(100);
        num.show();
        cout << endl;
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
