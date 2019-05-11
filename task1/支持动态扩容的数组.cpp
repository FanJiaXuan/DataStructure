#include <iostream>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
//ʵ��һ��֧�ֶ�̬���ݵ����飿
#define INCREMENT 10
#define OK 1
#define ERROR 0

using namespace std;

typedef char ElemType;
typedef int Status;
typedef struct{
    ElemType *pointer;//��ַ
    int length;
    int maxSize;
} SqList;

Status ListInit(SqList &L){//����һ������ �Ҹ��������ַ����ַ������Դ�ֵ��������������
    L.pointer = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.pointer)
        return ERROR;
    L.length = 0;
    L.maxSize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert(SqList &L, int position, ElemType elem){//����˳�������ã������λ�ã��Ͳ������
    if(position < 1 || position > L.length + 1)//����ķ�Χ ֻ���ڵ�һ�� �����һ������Ԫ�ص�ƨ�ɺ���֮��
        return ERROR;
    if(L.length + 1 > L.maxSize){//������� �ǿ϶��Ͳ岻��
        ElemType *newBase = (ElemType *)realloc(L.pointer,(LIST_INIT_SIZE + INCREMENT)* sizeof(ElemType));
        if(!newBase)
            return ERROR;
        L.pointer = newBase;
        L.maxSize = L.maxSize + INCREMENT;
    }
    ElemType *q = &L.pointer[position - 1];//Ҫ�����λ��
    ElemType *p = &L.pointer[L.length - 1];//���һ��Ԫ�ص�λ��
    for(p; p >= q; p--){//��β�Ϳ�ʼ �������Ŀ��λ��Ϊֹ�� ÿ���ռ����ֵ����ƶ�һ��
        *(p + 1) = *p;
    }
    *q = elem;
    L.length++;
    return OK;
}

ElemType deleteElem(SqList &L, int order){
    if(order < 1 || order > L.length)
        return ERROR;
    ElemType *p = &L.pointer[order];//Ҫɾ����Ԫ�ص���һ��λ��
    ElemType *q = &L.pointer[L.length - 1];//ƨ��
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

//������������ϲ���һ����������
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
    cout<<"��c��λ�ã�"<<endl;
    cout<<FindElementNo(l,'c')<<endl;
    cout<<"�ڵ�4 ��Ԫ��λ���ϲ���f Ԫ��: "<<endl;
    ListInsert(l,4,'f');
    //(9)���˳���L:a b c f d e
    ListOutput(l);
    cout<<"ɾ��L �ĵ�3 ��Ԫ��: "<<endl;
    deleteElem(l,3);
    //(11)���˳���L:a b f d e
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

