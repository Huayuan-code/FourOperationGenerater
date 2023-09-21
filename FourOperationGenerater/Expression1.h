#pragma once
#include "Number.h"
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
    void writefile(FILE* f);
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
    else if (op == 3) op = 'x';
    else if (op == 4) op = '|';
}

void Expression1::show()
{
    num1.show();
    cout << " " << op << " ";
    num2.show();
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
    ans = num / r;
    return ans;
}


Number Expression1::cal()
{
    if (op == '+') return num1 + num2;
    else if (op == '-') return num1 - num2;
    else if (op == 'x') return num1 * num2;
    else if (op == '|') return num1 / num2;
}

void Expression1::writefile(FILE* f)
{
    num1.writeFile(f);
    fprintf(f, " %c ", op);
    num2.writeFile(f);
}



