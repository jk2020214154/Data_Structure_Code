#include<iostream>

using namespace std;

#define MaxSize 50

typedef int ElemType;

//顺序栈(top1初始为-1,top2初始为MaxSize--->指向栈顶元素的当前位置)
typedef struct{
    ElemType data[MaxSize];
    int top1;
    int top2;
}SqStack;

void InitStack(SqStack &S)//栈的初始化
{
    S.top1=-1;
    S.top2=MaxSize;
}

bool Stack1Empty(SqStack S)//判断栈空
{
    if(S.top1==-1)
        return true;
    else return false;
}

bool Stack2Empty(SqStack S)//判断栈空
{
    if(S.top2==MaxSize)
        return true;
    else return false;
}

bool Push1(SqStack &S,ElemType x)//进栈
{
    if(S.top1+1==S.top2)
        return false;
    S.data[++S.top1]=x;
    return true;
}

bool Push2(SqStack &S,ElemType x)//进栈
{
    if(S.top1+1==S.top2)
        return false;
    S.data[--S.top2]=x;
    return true;
}

bool Pop1(SqStack &S,ElemType &x)//出栈
{
    if(S.top1==-1)
        return false;
    
    x=S.data[S.top1--];
    return true;
}

bool Pop2(SqStack &S,ElemType &x)//出栈
{
    if(S.top2==MaxSize)
        return false;
    
    x=S.data[S.top2++];
    return true;
}

bool GetTop1(SqStack S,ElemType &x)//获取栈顶
{
    if(S.top1==-1)
        return false;
    x=S.data[S.top1];
    return true;
}

bool GetTop2(SqStack S,ElemType &x)//获取栈顶
{
    if(S.top2==MaxSize)
        return false;
    x=S.data[S.top2];
    return true;
}

void Destroy1Stack(SqStack &S)//销毁栈
{
    //由于是静态分配,不用释放
}

void Destroy2Stack(SqStack &S)//销毁栈
{
    //由于是静态分配,不用释放
}

void Test()
{
	SqStack S;		//声明一个共享栈(分配内存空间)

	/*1、初始化共享栈*/
	InitStack(S);

	/*2、1号栈-判空*/
	if (Stack1Empty(S))
		printf("当前1号栈空！\n");
	else
		printf("当前1号栈非空！\n");

	/*3、1号栈-入栈操作*/
	ElemType e1;
	printf("请输入1号栈入栈元素的值：");
	scanf("%d", &e1);
	if (Push1(S, e1))
		printf("1号栈新元素入栈成功！\n");
	else
		printf("共享栈已满,1号栈新元素入栈失败！\n");

	/*4、1号栈-读取栈顶元素*/
	ElemType e2 = -1;
	if (GetTop1(S, e2))
		printf("1号栈读取栈顶元素成功，当前栈顶元素值为：%d\n", e2);
	else
		printf("1号栈已空，读取栈顶元素失败！\n");

	/*5、1号栈-出栈操作*/
	ElemType e3 = -1;
	if (Pop1(S, e3))
		printf("1号栈栈顶元素出栈成功，出栈元素值为：%d\n", e3);
	else
		printf("1号栈已空，栈顶元素出栈失败！\n");

	/*6、1号栈-读取栈顶元素*/
	ElemType e4 = -1;
	if (GetTop1(S, e4))
		printf("1号栈读取栈顶元素成功，当前栈顶元素值为：%d\n", e4);
	else
		printf("1号栈已空，读取栈顶元素失败！\n");

	/*7、2号栈-判空*/
	if (Stack2Empty(S))
		printf("当前2号栈空！\n");
	else
		printf("当前2号栈非空！\n");

	/*8、2号栈-入栈操作*/
	ElemType e21;
	printf("请输入2号栈入栈元素的值：");
	scanf("%d", &e21);
	if (Push2(S, e21))
		printf("2号栈新元素入栈成功！\n");
	else
		printf("共享栈已满,2号栈新元素入栈失败！\n");

	/*9、2号栈-读取栈顶元素*/
	ElemType e22 = -1;
	if (GetTop2(S, e22))
		printf("2号栈读取栈顶元素成功，当前栈顶元素值为：%d\n", e22);
	else
		printf("2号栈已空，读取栈顶元素失败！\n");

	/*10、2号栈-出栈操作*/
	ElemType e23 = -1;
	if (Pop2(S, e23))
		printf("2号栈栈顶元素出栈成功，出栈元素值为：%d\n", e23);
	else
		printf("2号栈已空，栈顶元素出栈失败！\n");

	/*11、2号栈-读取栈顶元素*/
	ElemType e24 = -1;
	if (GetTop2(S, e24))
		printf("2号栈读取栈顶元素成功，当前栈顶元素值为：%d\n", e24);
	else
		printf("2号栈已空，读取栈顶元素失败！\n");    

}


int main()
{
    Test();
    return 0;
}