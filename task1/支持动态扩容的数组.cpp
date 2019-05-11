#include <iostream>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
//实现一个支持动态扩容的数组？
#define INCREMENT 10
#define OK 1
#define ERROR 0

using namespace std;

typedef char ElemType;
typedef int Status;
typedef struct{
    ElemType *pointer;//地址
    int length;
    int maxSize;
} SqList;

Status ListInit(SqList &L){//给我一个引用 我给你申请地址（地址里面可以存值），并标上数据
    L.pointer = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.pointer)
        return ERROR;
    L.length = 0;
    L.maxSize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert(SqList &L, int position, ElemType elem){//给我顺序表的引用，插入的位置，和插入的数
    if(position < 1 || position > L.length + 1)//插入的范围 只能在第一个 到最后一个已有元素的屁股后面之间
        return ERROR;
    if(L.length + 1 > L.maxSize){//如果满了 那肯定就插不了
        ElemType *newBase = (ElemType *)realloc(L.pointer,(LIST_INIT_SIZE + INCREMENT)* sizeof(ElemType));
        if(!newBase)
            return ERROR;
        L.pointer = newBase;
        L.maxSize = L.maxSize + INCREMENT;
    }
    ElemType *q = &L.pointer[position - 1];//要插入的位置
    ElemType *p = &L.pointer[L.length - 1];//最后一个元素的位置
    for(p; p >= q; p--){//从尾巴开始 到插入的目标位置为止， 每个空间里的值向后移动一个
        *(p + 1) = *p;
    }
    *q = elem;
    L.length++;
    return OK;
}

ElemType deleteElem(SqList &L, int order){
    if(order < 1 || order > L.length)
        return ERROR;
    ElemType *p = &L.pointer[order];//要删除的元素的下一个位置
    ElemType *q = &L.pointer[L.length - 1];//屁股
    for(p; p <= q; p++){
        *(p - 1) = *p;
    }
    L.length--;
    return OK;
}

Status ListOutput(SqList L){
    if(L.length < 1) return ERROR;

    for(int i = 0; i <= L.length - 1; i++)
        {
        if(i == L.length - 1)
        {
            cout<<L.pointer[i]<<endl;
            break;
        }
         cout<<L.pointer[i];
         cout<<",";
        }
    return OK;

}

ElemType FindElemByOrder(SqList L, int order){
    if(order < 1 || order > L.length)
        return ERROR;
    return L.pointer[order - 1];
}

Status releaseList(SqList &L){
    free(L.pointer);
    L.pointer = NULL;
    L.length = 0;
    L.maxSize = 0;
    return OK;
}

int FindElementNo(SqList L, ElemType e){
    int i = 1;
    for(; i <= L.length; i++){
        if( (L.pointer[i - 1]) == e)
            return i;
    }
    return 0;
}

//两个有序数组合并成一个有序数组
int* ArrayMerge(int *a, int *b, int m, int n){
    int *c = new int[m + n];
    int p = 0, q = 0, i = 0;
    while(p < m && q < n){
        if(a[p] >= b[q])
            c[i++] = b[q++];
        else
            c[i++] = a[p++];
    }

    while(p != m)
        c[i++] = a[p++];
    while(q != n)
        c[i++] = b[q++];
    return c;
}

int main(){

    //TEST DYNAMIC VACTOR

    SqList l;
    cout << ListInit(l) << endl;

    char temp = 'a';
    for(int i = 1; i <= 5; i++){

            ListInsert(l,i,temp);
            temp++;
    }

    cout<<"---------------------------"<<endl;
    ListOutput(l);
    cout<<"找c的位置："<<endl;
    cout<<FindElementNo(l,'c')<<endl;
    cout<<"在第4 个元素位置上插入f 元素: "<<endl;
    ListInsert(l,4,'f');
    //(9)输出顺序表L:a b c f d e
    ListOutput(l);
    cout<<"删除L 的第3 个元素: "<<endl;
    deleteElem(l,3);
    //(11)输出顺序表L:a b f d e
    ListOutput(l);
    releaseList(l);
    cout<<"---------------------------"<<endl;
    //TEST ARRAY MERGE

    int a[] = {1, 3, 5};
    int b[] = {2, 4, 6};
    int *c = ArrayMerge(a, b, 3, 3);
    for(int i = 0; i < 6; i++)
        cout << c[i] << " ";
    return 0;
}

