#include<iostream>
#include<stack>

using namespace std;

int get_priority(char op)
{
    if(op=='+'||op=='-')
        return 1;
    else if(op=='*'||op=='/')
        return 2;
    else 
        return 0;
}

void op_calc(stack<int> &sta,char op)
{
    int num2=sta.top();
    sta.pop();
    int num1=sta.top();
    sta.pop();

    if(op=='+')
        sta.push(num1+num2);
    else if(op=='-')
        sta.push(num1-num2);
    else if(op=='*')
        sta.push(num1*num2);
    else sta.push(num1/num2);
}

bool judge_num(char c)
{
    if(c>='0'&&c<='9')
        return true;
    else return false;
}

int calc_value(string str,int len)
{
    //此处为了方便,采用c++的stl的栈实现(手写两个麻烦)
    stack<int> nums;
    stack<char> ops;

    for(int i=0;i<len;i++)
    {
        if(judge_num(str[i])==true)
        {
            int j=i;
            int num=0;
            while(judge_num(str[j])==true)
            {
                num=num*10+(str[j]-'0');
                j++;
            }

            i=j-1;
            nums.push(num);
        }
        else if(str[i]=='(')
            ops.push('(');
        else if(str[i]==')')
        {
            while(ops.empty()==0)
            {
                char op=ops.top();
                ops.pop();
                if(op=='(')
                    break;
                op_calc(nums, op);
            }
        }
        else if(str[i]!=' ')
        {
            while(ops.empty()==0)
            {
                char op=ops.top();
                if(get_priority(op)<get_priority(str[i]))
                    break;
                op_calc(nums, op);
                ops.pop();
            }

            ops.push(str[i]);
        }
    }

    while(ops.empty()==0)
    {
        char op=ops.top();
        ops.pop();
        op_calc(nums, op);
    }
    return nums.top();
}

void Test()
{
    string s1;
    getline(cin,s1);

    /*
    12*4+34/5-(56+67*4)+32
    24+2*(5-3)-6/2
    */
    
    cout << calc_value(s1,s1.size()) << endl;
}

int main()
{
    Test();
    return 0;
}