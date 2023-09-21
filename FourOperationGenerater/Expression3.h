#pragma once
#include "Expression2.h"
//三类表达式定义
class Expression3 
{
public:
	Number num;
	Expression2 exp2;
	char op;
	int type; // 0: num + exp, 1:exp + num

	Expression3();
	Expression3(long long range);
	void show();
	Number cal();
	void writefile(FILE* f);
	
};

Expression3::Expression3()
{}

Expression3::Expression3(long long range)
{
	num = Number(range);
	exp2 = Expression2(range);

	op = '+';
	type = rand() % 2;
}

Number Expression3::cal()
{
	Number ans = exp2.cal();
	ans = ans + num;
	return ans;
}


void Expression3::show()
{
	num.show();
	printf(" + ");
	exp2.show();
}

void Expression3::writefile(FILE* f)
{
	num.writeFile(f);
	fprintf(f, " +  ");
	exp2.writefile(f);
}

