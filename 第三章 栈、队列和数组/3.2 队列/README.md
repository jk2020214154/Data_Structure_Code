####  3.2.1

>  若希望循环队列中的元素都能得到利用，则需设置一个标志域 $tag$，并以 $tag$ 的值为 $0$或 $1$来区分队头指针 $front $和队尾指针 $rear $相同时的队列状态是“空”还是“满”。试编写与此结构相应的入队和出队算法.

进队时置 $tag$为 $1$,出队时置 $tag$为 $0$,队列初始化时置为 $0$
*  $rear$指向队尾元素的下一个位置

```cpp
//参考循环队列1_3.cpp
void InitQueue(SqQueue &Q)//初始化
{
    Q.front=Q.rear=0;
    Q.tag=0;//表示此时无法删除(即初始化为空队列)
}

bool QueueEmpty(SqQueue Q)//判断队空
{
    if(Q.rear==Q.front&&Q.tag==0)
        return true;
    else return false;
}

bool QueueFull(SqQueue Q)//判断队满
{
    if(Q.rear==Q.front&&Q.tag==1)
        return true;
    else return false;
}

bool EnQueue(SqQueue &Q,ElemType x)//入队
{
    if(QueueFull(Q)==true)
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%MaxSize;

    Q.tag=1;//入队操作更新为1
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x)//出队
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;

    Q.tag=0;//出队操作更新为0
    return true;
}

```

*  $rear$指向队尾元素

```cpp
//参考循环队列2_3.cpp
void InitQueue(SqQueue &Q)//初始化
{
    Q.front=0;
    Q.rear=MaxSize-1;
    Q.tag=0;//表示此时无法删除(即初始化为空队列)
}

bool QueueEmpty(SqQueue Q)//判断队空
{
    if((Q.rear+1)%MaxSize==Q.front&&Q.tag==0)
        return true;
    else return false;
}

bool QueueFull(SqQueue Q)//判断队满
{
    if((Q.rear+1)%MaxSize==Q.front&&Q.tag==1)
        return true;
    else return false;
}

bool EnQueue(SqQueue &Q,ElemType x)//入队
{
    if(QueueFull(Q)==true)
        return false;
    Q.rear=(Q.rear+1)%MaxSize;//注意入队先+1,再赋值
    Q.data[Q.rear]=x;
    

    Q.tag=1;//入队操作更新为1
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x)//出队
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;

    Q.tag=0;//出队操作更新为0
    return true;
}
```

#### 3.2.2

>  $Q$是一个队列， $S$是一个空栈，实现将队列中的元素逆置的算法。

让队列中的元素逐个地出队列,入栈;全部入栈后再逐个出栈,入队列.

```cpp
void Reverse_Queue(SqQueue &Q,SqStack &S)
{
    ElemType num;
    while(QueueEmpty(Q)==false)
    {
        DeQueue(Q, num);//出队列
        Push(S, num);//入栈
    }

    while(StackEmpty(S)==false)
    {
        Pop(S, num);//出栈
        EnQueue(Q, num);//入队列
    }
}
```

#### 3.2.3

>  利用两个栈 $S_1$, $S_2$来模拟一个队列，已知栈的 $4$个运算定义如下:
>
> ```cpp
> Push(S,x);//元素x入栈S
> Pop(S,x);//S出栈并将出栈的值赋给x
> StackEmpty(S);//判断栈是否为空
> stackOverflow(S);//判断栈是否满
> ```
>
> 如何利用栈的运算来实现该队列的 $3$个运算（形参由读者根据要求自己设计）?
>
> ```,
> EnQueue;//将元素x入队
> DeQueue;//出队,并将出队元素存储在x中
> QueueEmpty;//判读队列是否为空
> ```

* 入队操作

两个栈 $S_1$， $S_2$都为空，执行入队操作，将元素直接插入 $S_1$中。

栈 $S_1$为满，栈 $S_2$不为空，则队列为满，无法执行入队操作。

栈 $S_1$为满，栈 $S_2$为空，执行入队操作，先将栈 $S_1$中的元素逐一出栈，再逐一入栈 $S_2$,最后当 $S_1$为空时，将元素插入 $S_1$中，实现入队操作。

* 出队操作

栈 $S_2$不为空，则队首元素位于 $S_2$的栈顶（栈 $S_1$为满， $S_2$不为空），执行出队操作，将 $S_2$中的栈顶元素出栈，实现出队操作。

栈 $S_2$为空，栈 $S_1$为空，则队列为空，无法实现出队操作。

栈 $S_1$不空，栈 $S_2$为空，执行出队操作时，先将 $S_1$中元素逐一从 $S_1$出栈，再逐一入栈 $S_2$，最后将 $S_2$中的栈顶元素出栈，实现出队操作。

* 判空操作

两个栈 $S_1$和 $S_2$都为空时，队列为空。

```cpp
bool EnQueue(SqStack &S1,SqStack &S2,ElemType x)//入队
{
    if(StackOverflow(S1)==false)//S1未满,放入S1中
    {
        Push(S1,x);
        return true;
    }
    if(StackOverflow(S1)==true&&StackEmpty(S2)==false)
    {
        //S1满了,且S2有元素
        cout << "队列满" << endl;
        return 0;
    }
    if(StackOverflow(S1)==true&&StackEmpty(S2)==true)
    {
        //S1满了,S2空
        ElemType num;
        while(StackEmpty(S1)==false)
        {
            Pop(S1,num);
            Push(S2,num);
        }
    }

    Push(S1,x);
    return true;
}

bool DeQueue(SqStack &S1,SqStack &S2,ElemType &x)//出队列
{
    if(StackEmpty(S2)==false)//S2不空
    {
        Pop(S2,x);
        return true;
    }
    else if(StackEmpty(S1)==true)//S2为空,S1为空
    {
        cout << "队列空" << endl;
        return 0;
    }
    else//S2为空,S1不为空
    {
        ElemType num;
        while(StackEmpty(S1)==false)
        {
            Pop(S1, num);
            Push(S2,num);
        }
        Pop(S2,x);
        return true;
    }
}

bool QueueEmpty(SqStack S1,SqStack S2)//判断队空
{
    if(StackEmpty(S1)==true&&StackEmpty(S2)==true)
        return true;
    else return false;
}
```

#### 3.2.4

>  
