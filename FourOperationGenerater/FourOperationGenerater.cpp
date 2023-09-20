#pragma once
#include <iostream>
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime> //
#include<stdio.h>
#include<string.h>
#include "Expression2.h"
using namespace std;

void showhelp()
{
    printf("command error\n");
    printf("here is the command format:\n");
    printf("Myapp.exe -n <the number of expression> -r <the max value of each number>\n");
    printf("the number of expression should be bewteen [100, 1000000]\n");
    printf("the max value of each number should be bewteen [100, 1000000]\n");
}

long long string2ll(string &s)
{
    long long ans = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] < '0' || s[i] > '9') return -1;
        ans *= 10;
        ans += s[i] - '0';
        if (ans > 10000000) return -1;
    }
    return ans;
}

int generate(long long m, long long r)
{
    printf("n = %lld, r = %lld\n", m, r);
    printf("generating.....\n");
    FILE *fexe, *fans, *fcom;
    int err;
    err = fopen_s(&fexe, "Exercises.txt", "w+");
    if (err)
    {
        printf("can't open Exercises.txt\n");
        return 0;
    }
    err = fopen_s(&fans, "Answers.txt", "w+");
    if (err)
    {;
        printf("can't open Answers.txt\n");
        return 0;
    }
    err = fopen_s(&fcom, "complete.txt", "w+");
    if (err)
    {
        ;
        printf("can't open complete.txt\n");
        return 0;
    }

    long long cnt = 0;
    Expression1 exp1(r);
    Expression2 exp2(r);
    Number ans;
    while (cnt < m)
    {
        if (rand() % 2)
        {
            exp1 = Expression1(r);
            ans = exp1.cal();
            if (ans.iszero() || !ans.normalize())
            {                   
                continue;
            }
            
            exp1.writefile(fexe);
            fprintf(fexe, " = ");
            fprintf(fexe, "\n");

            ans.writeFile(fans);
            fprintf(fans, "\n");

            exp1.writefile(fcom);
            fprintf(fcom, " = ");
            ans.writeFile(fcom);
            fprintf(fcom, "\n");
        }
        else
        {
            exp2 = Expression2(r);
            ans = exp2.cal();
            if (ans.iszero() || !ans.normalize()) continue;

            exp2.writefile(fexe);
            fprintf(fexe, " = ");
            fprintf(fexe, "\n");

            ans.writeFile(fans);
            fprintf(fans, "\n");

            exp2.writefile(fcom);
            fprintf(fcom, " = ");
            ans.writeFile(fcom);
            fprintf(fcom, "\n");
        }
        cnt++;
        //printf("%lld\n", cnt);
    }


    fclose(fexe);
    fclose(fans);
    printf("done!\n");
    return 1;
}



int main(int argc, char* argv[])
{
    int seed = time(0);
    srand(seed);

    long long r = -1;
    long long m = 100;
    if (argc < 3) printf("too few param");
    else if (argc == 3)
    {
        string param1 = argv[1];
        string param2 = argv[2];
        long long r = string2ll(param2);
        if (param1 != "-r" || r < 100 || r > 1000000) showhelp();
        else if (!generate(m, r)) printf("error\n");
    }
    else if (argc == 4) printf("too few param");
    else if (argc == 5)
    {
        string param1 = argv[1];
        string param2 = argv[2];
        string param3 = argv[3];
        string param4 = argv[4];

        if (param1 != "-r" && param3 != "-r") showhelp();
        else if (param1 != "-n" && param3 != "-n") showhelp();
        else
        {
            long long num1 = string2ll(param2);
            long long num2 = string2ll(param4);
            if (num1 < 100 || num2 < 100 || num1 > 1000000 || num2 > 1000000) showhelp();
            else
            {
                if (param1 == "-r") r = num1, m = num2;
                else r = num2, m = num1;
                if (!generate(m, r)) printf("error\n");
            }
        }

    }
    else printf("too much param\n");
    


    return 0;
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
