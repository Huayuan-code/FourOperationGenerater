#pragma once
#include "Expression1.h"
//----������ʽ����
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
    void writefile(FILE* f);

};

Expression2::Expression2()
{
}

Expression2::Expression2(long long range)
{
    num = Number(range);
    exp = Expression1(range);
    op = rand() % 4 + 1;
    if (op == 1) op = '+';
    else if (op == 2) op = '-';
    else if (op == 3) op = 'x';
    else if (op == 4) op = '|';
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


void Expression2::writefile(FILE* f)
{
    num.writeFile(f);
    fprintf(f, " %c ", op);
    fprintf(f, "(");
    exp.writefile(f);
    fprintf(f, ")");
}