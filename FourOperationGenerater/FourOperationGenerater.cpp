#include <iostream>
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime> //
#include<stdio.h>
using namespace std;

long long gcd(long long a, long long b)
{
    if (!b) return a;
    else return gcd(b, a % b);
}

long long lcm(long long a, long long b)
{
    return a / gcd(a, b) * b;
}

//-----------数字定义
class Number
{
public:

    long long inte; // 整数部分
    long long nume; // 分子
    long long deno; // 分母

    Number();
    Number(long long range);
    void show();
    bool normalize();
    bool iszero();
};

Number::Number()
{
    long long range = 100;
    inte = rand() % range + 1;
    deno = rand() % range + 1;
    if (deno == 1) deno++;

    if (rand() % 2) nume = rand() % deno;
    else nume = 0;

    normalize();
}

Number::Number(long long range)
{
    inte = rand() % range + 1;
    deno = rand() % range + 1;
    if (deno == 1) deno++;

    if (rand() % 2) nume = rand() % deno;
    else nume = 0, deno = 1;

    normalize();
}

void Number::show()
{
    if(inte) printf("%lld", inte);
    if (inte && nume) printf("'");
    if (nume) printf("%lld/%lld", nume, deno);
    if (!inte && !nume) printf("0");
}

bool Number::normalize()
{
    if (inte < 0) return false;

    nume += inte * deno;
    if (nume < 0) return false;

    inte = nume / deno;
    nume %= deno;

    long long g = gcd(nume, deno);
    nume /= g;
    deno /= g;
}

bool Number::iszero()
{
    if (inte == 0 && nume == 0) return true;
    else return false;
}

Number operator + (const Number& a, const Number& b)
{
    Number ans;
    ans.inte = a.inte + b.inte;
    
    long long com = lcm(a.deno, b.deno);
    ans.deno = com;
    ans.nume = com / a.deno * a.nume + com / b.deno * b.nume;

    ans.normalize();

    return ans;
}

Number operator - (const Number& a, const Number& b) //postive ans
{
    Number ans;
    ans.inte = a.inte - b.inte;

    long long com = lcm(a.deno, b.deno);
    ans.deno = com;
    ans.nume = com / a.deno * a.nume - com / b.deno * b.nume;

    ans.normalize();
    
    return ans;
}

Number operator * (const Number& a, const Number& b)
{
    Number ans;

    ans.inte = 0;
    ans.deno = a.deno * b.deno;
    ans.nume = (a.inte * a.deno + a.nume) * (b.inte * b.deno + b.nume);
    ans.normalize();

    return ans;
}

Number operator / (Number& a, Number& b)
{
    Number ans;
    ans.inte = -1;
    ans.nume = -1;

    if (b.iszero() || !b.normalize()) return ans;

    ans.inte = 0;
    ans.deno = a.deno * (b.inte * b.deno + b.nume);
    ans.nume = (a.inte * a.deno + a.nume) * b.deno;

    ans.normalize();

    return ans;
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
    Number cal();
};

Expression1::Expression1()
{}

Expression1::Expression1(long long range)
{
    num1 = Number(range);
    num2 = Number(num1.inte);
    op = rand() % 4 + 1;
    if (op == 1) op = '+';
    else if (op == 2) op = '-';
    else if (op == 3) op = 'x';
    else if (op == 4) op = '|';
}

void Expression1::show()
{
    num1.show();
    cout << " " << op << " ";
    num2.show();
}

Number Expression1::cal()
{
    if (op == '+') return num1 + num2;
    else if (op == '-') return num1 - num2;
    else if (op == 'x') return num1 * num2;
    else if (op == '|') return num1 / num2;
}

//----二类表达式定义

class Expression2
{
public:
    Number num;
    Expression1 exp;
    char op;

    Expression2();
    Expression2(long long range);
    void show();
    Number cal();
    
};

Expression2::Expression2()
{
}

Expression2::Expression2(long long range)
{
    num = Number(range);
    exp = Expression1(num.inte);
    op = rand() % 4 + 1;
    if (op == 1) op = '+';
    else if (op == 2) op = '-';
    else if (op == 3) op = 'x';
    else if (op == 4) op = '|';
}

Number operator + (Number& num, Expression1& e)
{
    Number ans;
    ans = num + e.cal();
    return ans;
}

Number operator - (Number& num, Expression1& e)
{
    Number ans;
    ans = num - e.cal();
    return ans;
}

Number operator * (Number& num, Expression1& e)
{
    Number ans;
    ans = num * e.cal();
    return ans;
}

Number operator / (Number& num, Expression1& e)
{
    Number ans, r = e.cal();
    ans.inte = -1;
    ans.nume = -1;
    if (r.iszero() || !r.normalize())  return ans;
    ans = num /r;
    return ans;
}

Number Expression2::cal()
{
    if (op == '+') return num + exp;
    else if (op == '-') return num - exp;
    else if (op == 'x') return num * exp;
    else if (op == '|') return num / exp;
}

void Expression2::show()
{
    num.show();
    printf(" %c ", op);
    cout << '(';
    exp.show();
    cout << ')';
}

int main()
{
    unsigned seed = time(0);
    //seed = 1;
    srand(seed);

    Expression2 num(10000);
    for (int i = 0; i < 10000; i++)
    {
        num = Expression2(100);
     
        num.show();
        cout << " = ";
        Number ans = num.cal();
        ans.show();
        if (!ans.normalize()) printf(" negativ! or div0");
        
        cout <<   "\n\n";
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
