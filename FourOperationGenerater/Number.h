#pragma once
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
    void writeFile(FILE* f);
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
    if (inte) printf("%lld", inte);
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
    return true;
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


void Number::writeFile(FILE* f)
{
    if (inte) fprintf(f, "%lld", inte);
    if (inte && nume) fprintf(f, "'");
    if (nume) fprintf(f, "%lld/%lld", nume, deno);
    if (!inte && !nume) fprintf(f, "0");
}