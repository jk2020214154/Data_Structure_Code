#include<iostream>

using namespace std;

#define MaxBlockSize 4

//不带头结点
typedef struct Chunk{
    char ch[MaxBlockSize];
    Chunk *next;
}Chunk;

typedef struct{
    Chunk *head,*rear;
    int length;
}LString;

void InitLString(LString &Str)
{
    Str.head=Str.rear=NULL;
    Str.length=0;
}

void StrAssign(LString &Str,char str[])//赋值操作
{
    InitLString(Str);
    Chunk *r=Str.head;//尾指针
    int len=0,pos=0;
    while(str[len]!='\0')
        len++;
    Str.length=len;

    int blocknum=len/MaxBlockSize;
    if(len%MaxBlockSize!=0)//余数部分需再开个空间
        blocknum++;

    for(int i=1;i<=blocknum;i++)
    {
        Chunk *p=(Chunk *)malloc(sizeof(Chunk));
        if(Str.head==NULL)//第一个结点
            Str.head=r=p;
        else
        {
            r->next=p;
            r=p;
        }

        int j;
        for(j=0;j<MaxBlockSize&&pos<len;j++)
            r->ch[j]=str[pos++];
    
        if(pos==len)
        {
            Str.rear=p;
            Str.rear->next=NULL;

            while(j<MaxBlockSize)
                r->ch[j++]='#';
        }        
    }
}

bool StrEmpty(LString Str)//判空操作
{
    return Str.length==0;
}

void DestroyString(LString &Str)//销毁和清空亦可
{
    if(Str.length==0)
        return ;
    Chunk *p=Str.head,*q;

    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    Str.head=Str.rear=NULL;
    Str.length=0;
}

void StrCopy(LString &Str1,LString Str2)//复制操作
{
    Chunk *q=Str2.head;
    if(q==NULL)
        return ;
    
    int pos=0;
    char *str=(char *)malloc((Str2.length+1)*sizeof(char));
    while(q!=NULL)
    {
        for(int j=0;j<MaxBlockSize;j++)
            if(q->ch[j]!='#')
                str[pos++]=q->ch[j];
        q=q->next;
    }
    
    str[pos]='\0';

    //cout << str << endl;
    StrAssign(Str1,str);

    free(str);

}

void PrintLString(LString Str)
{
    if(Str.length==0)
        cout << "该串为空" << endl;
    Chunk *p=Str.head;
    while(p!=NULL)
    {
        for(int i=0;i<MaxBlockSize;i++)
            if(p->ch[i]!='#')
                cout << p->ch[i];
        p=p->next;
        //cout << " ";
    }
    cout << endl;
}

int StrCompare(LString Str1,LString Str2)//比较操作
{//若Str1>Str2,返回值>0;若Str1=Str2,返回0,若Str1<Str2,返回值<0
    Chunk *p1=Str1.head,*p2=Str2.head;

    while(p1!=NULL&&p2!=NULL)
    {
        for(int i=0;i<MaxBlockSize;i++)
        {
            if(p1->ch[i]!=p2->ch[i])
            {
                if(p1->ch[i]=='#')
                    return -1;
                else if(p2->ch[i]=='#')
                    return 1;
                return p1->ch[i]-p2->ch[i];
            }
        }
        p1=p1->next;
        p2=p2->next;
    }
    return p1-p2;//当有一个指向NULL时,该指针为0,返回相减结果即可
}

int StrLength(LString Str)//求串长
{
    return Str.length;
}


bool SubString(LString &Sub,LString Str,int pos,int len)//求子串
{
    if(pos+len-1>Str.length)
        return false;

    char *str=(char *)malloc((len+1)*sizeof(char));

    Chunk *p=Str.head;

    int i=0,j=0;
    while(j<pos)
    {
        if(j==pos-1)
            break;
        i++,j++;
        if(i==MaxBlockSize)
            p=p->next,i=0;
    }

    j=0;//枚举长度

    while(j<len)
    {
        str[j]=p->ch[i];
        i++;
        if(i==MaxBlockSize)
            p=p->next,i=0;
        j++;
    }

    str[j]='\0';

    InitLString(Sub);
    StrAssign(Sub, str);
    return true;
}


int StrIndex(LString Str1,LString Str2)//定位操作
{
    int pos=1;
    int len1=StrLength(Str1),len2=StrLength(Str2);
    
    LString Subs;

    while(pos<=len1-len2+1)
    {
        SubString(Subs, Str1, pos, len2);
        //PrintLString(Subs);
        if(StrCompare(Subs, Str2)==0)
            return pos;
        else pos++;
    }
    return 0;//Str1中不存在与T相等的子串
}


void Test()
{
    LString s1;
    LString s2;
    LString Subs;
    char str1[]="abcdedfghgvkb";
    char str2[]="testa bab";

    char str3[]="dedf";

    InitLString(s1);
    InitLString(s2);

    StrAssign(s1, str1);
    StrAssign(s2, str2);
    
    SubString(Subs, s1, 5, 3);

    PrintLString(Subs);
    

    StrAssign(s2, str3);
    PrintLString(s2);

    cout << endl;
    cout << StrIndex(s1, s2) << endl;


    StrAssign(s2, str2);
    PrintLString(s1);
    PrintLString(s2);

    StrCopy(s1,s2);

    cout << endl;

    PrintLString(s1);
    PrintLString(s2);


    DestroyString(s1);
    DestroyString(s2);
    DestroyString(Subs);
}

int main()
{
    Test();
    return 0;
}