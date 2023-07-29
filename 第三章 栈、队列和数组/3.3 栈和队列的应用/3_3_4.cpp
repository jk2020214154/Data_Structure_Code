#include<iostream>

using namespace std;

#define MaxSize 110

typedef int ElemType;


//front指向队头元素,rear指向队尾元素的下一个位置
//front=0,rear=0
//牺牲一个空间
typedef struct {
    ElemType data[MaxSize];
    int front,rear; 
}SqQueue;


void InitQueue(SqQueue &Q)//初始化
{
    Q.front=Q.rear=0;
}

bool QueueEmpty(SqQueue Q)//判断队空
{
    if(Q.rear==Q.front)
        return true;
    else return false;
}

bool QueueFull(SqQueue Q)//判断队满
{
    if((Q.rear+1)%MaxSize==Q.front)
        return true;
    else return false;
}

bool EnQueue(SqQueue &Q,ElemType x)//入队
{
    if(QueueFull(Q)==true)
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x)//出队
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    return true;
}

bool GetHead(SqQueue Q,ElemType &x)//获取队头
{
    if(QueueEmpty(Q)==true)
        return false;
    
    x=Q.data[Q.front];
    return true;
}


void DestroyQueue(SqQueue &Q)//销毁队列
{
    //由于是静态分配,不用释放
    ElemType num;
    while(QueueEmpty(Q)==false)
        DeQueue(Q, num);
}


void PrintQueue(SqQueue Q)//打印队列
{
    //cout << "-------------------------" << endl;
    //cout << Q.front << " " << Q.rear << endl;

    int pos=Q.front;

    while(pos!=Q.rear)
    {
        cout << Q.data[pos] << " ";
        pos=(pos+1)%MaxSize;
    }
    cout << endl;
}

int a[MaxSize];

void ClearQueue(SqQueue &Q)
{
    while(QueueEmpty(Q)==false)
    {
        int num;
        DeQueue(Q, num);
    }
}

void ShipArrange(int n)
{
    int ship_tot=0,bus_tot=0,van_tot=0;//分别表示船上车的数量,客车数量,货车队列中的数量
    int ship_cnt=0;//船的个数

    SqQueue van_Q;//存储货车的序号
    SqQueue ship_Q;//存储当前船上的情况

    InitQueue(van_Q);
    InitQueue(ship_Q);

    for(int i=1;i<=n;i++)
    {
        if(ship_tot<=9)//船有足够的空间(小于10)
        {
            if(a[i]==1)//客车
            {
                if(bus_tot>=4&&QueueEmpty(van_Q)==false)//货车队列有且当前客车数量不小于3
                {
                    int num;
                    DeQueue(van_Q, num);//出货车队
                    van_tot--;//货车队列中的数量减少
                    ship_tot++;//货车上船
                    EnQueue(ship_Q, num);

                    bus_tot=0;
                }

                if(ship_tot<=9)//由于有可能刚好把货车放入使得船满
                {
                    EnQueue(ship_Q, i);
                    bus_tot++;
                    ship_tot++;
                }
                else if(ship_tot==10)
                {
                    cout << "第" << ++ship_cnt << "辆船:";
                    PrintQueue(ship_Q);
                    ship_tot=0,bus_tot=0;
                    ClearQueue(ship_Q);
                    
                    EnQueue(ship_Q, i);
                    bus_tot++;
                    ship_tot++;                   

                }
            }
            else//货车
            {
                EnQueue(van_Q, i);
                van_tot++;
            }
        }

        if(ship_tot==10)
        {
            cout << "第" << ++ship_cnt << "辆船:";
            PrintQueue(ship_Q);
            ship_tot=0,bus_tot=0;
            ClearQueue(ship_Q);
        }
        
        //cout << i << ": " << ship_tot << " " << bus_tot << " " << van_tot << endl;
    }


    while(QueueEmpty(van_Q)==false)
    {
        if(ship_tot<=9)
        {
            int num;
            DeQueue(van_Q, num);//出货车队
            van_tot--;//货车队列中的数量减少
            ship_tot++;//货车上船
            EnQueue(ship_Q, num);
        }
        else if(ship_tot==10)
        {
            cout << "第" << ++ship_cnt << "辆船:";
            PrintQueue(ship_Q);
            ship_tot=0;
            ClearQueue(ship_Q);
            
            int num;
            DeQueue(van_Q, num);//出货车队
            van_tot--;//货车队列中的数量减少
            ship_tot++;//货车上船
            EnQueue(ship_Q, num);
        }

        if(ship_tot==10)//此处注意细节
        {
            cout << "第" << ++ship_cnt << "辆船:";
            PrintQueue(ship_Q);
            ship_tot=0;
            ClearQueue(ship_Q);            
        }
    }


    if(ship_tot<=9)
    {
        cout << "第" << ++ship_cnt << "辆船:";
        PrintQueue(ship_Q);
        ship_tot=0;
        ClearQueue(ship_Q);
    }
}


void Test()
{
    int n;
    cin >> n;

    for(int i=1;i<=n;i++)//0表示货车,1表示客车
        cin >> a[i];
    ShipArrange(n);
}

int main()
{
    Test();
    return 0;
}