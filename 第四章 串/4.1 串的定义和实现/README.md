#### 串的定长顺序存储表示

串的顺序存储结构是用一组地址连续的存储单元来存储字符序列的。按照预定义的大小，为每个定义的串变量分配一个固定长度的存储区。一般用定长数组来定义。

```cpp
#define MaxLen 255

typedef struct {
    char ch[MaxLen+1];
    //存储串的一维数组,ch[0]~ch[255],共256个;
    //通常情况下 ch[0]存放串的长度,或者闲置不用,真正串的内容从ch[1]开始
    int length;
}SString;
```

#### 串的堆分配存储

```cpp
typedef struct{
    char *ch;
    int length;
}HString;

void InitHString(HString &Str)
{
    Str.length=0;
    Str.ch=(char *)malloc((MaxLen+1)*sizeof(char));
}

void DestroyString(HString &Str)//销毁操作
{
    free(Str.ch);
}
```

#### 串的块链存储

将多个字符存储在一个结点，那么这一个节点叫做一个存储块，即块链

```cpp
#define MaxBlockSize 4

//不带头结点
typedef struct Chunk{
    char ch[MaxBlockSize];
    Chunk *next;
}Chunk;
```

