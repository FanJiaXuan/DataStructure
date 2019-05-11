#include <iostream>
#include <stdlib.h>

#define OK 1
#define ERROR 0
using namespace std;

typedef char ElemType ;
typedef int Status ;

typedef struct LNode{
    ElemType data;
    LNode *next;
}LNode, *LinkList;

Status InitList(LinkList &l){//�����������ͷָ������� ��ͷָ�����ռ�
    l = (LNode *)malloc(sizeof(LNode));
    if(!l)
        return ERROR;
    l -> next = NULL;
    return OK;
}

//(3)���������head:a b c d e
void ListOutput(LinkList L){//����ͷָ��
	LNode *p = L -> next;
	while(p){
		cout<<p -> data;
		p = p -> next;
		//cout<<"!"<<endl;
	}
	cout<<endl;
}
//(4)������head����:5
int ListLength(LinkList L){
    int Length = 0;
    LNode *p = L -> next;
    while(p){
        ++ Length;
        p = p -> next;
    }
    return Length;
}
//(5)������headΪ�ǿ�
bool isEmpty(LinkList L){
    LNode *p = L -> next;
    if(p)
        return false;
    else
        return true;
}
//(6)������head�ĵ�3��Ԫ��:c
Status GetElem(LinkList L, int i, ElemType &e){
    LNode *p = L -> next;
    int j = 1;
    while(p && j < i){
        p = p -> next;
        j++;
    }
    if(!p || j > i) return ERROR;
    e = p -> data;
    return OK;
}
//(7)Ԫ��a��λ��:1
int GetNo(LinkList L, ElemType e){
    LNode *p = L -> next;
    int j = 1;
    while(p -> data != e && p){
        p = p -> next;
        j++;
    }
    if(p)
        return j;
    else return 0;
}

/*Status ListInsert(LinkList &L, int i, ElemType e){
    LNode *p = L;
    int j = 0;
    while(p && j < i - 1){
        p = p -> next;
        ++j;
    }
    if(!p || j > i - 1)
        return ERROR;
    LNode *s = (LNode *) malloc (sizeof(LNode));
    s -> data = e;
    s -> next = p -> next;
    p -> next = s;
    return OK;
}*/

Status ListInsert111(LinkList &l, int position, ElemType e){
    if(position < 1)
        return ERROR;
    LNode *p = l -> next;
    int i = 1;
    while(p && i < position - 1){
        i++;
        p = p -> next;
    }
    //p = null or i == position
    if(p == NULL)//��Խ��
        return ERROR;
    LNode *temp = (LNode *)malloc(sizeof(LNode));
    temp -> data = e;
    if(p -> next == NULL){
        p -> next = temp;
        temp -> next = NULL;
    }else{
        temp -> next = p -> next;
        p -> next = temp;
    }
}

//(8)�ڵ�4��Ԫ��λ���ϲ���fԪ��
Status ListInsert(LinkList &L, int i, ElemType e){
    LNode *p = L;
    int j = 0;
    while(p && j < i - 1){
        p = p -> next;
        ++j;
    }
    if(!p || j > i - 1)
        return ERROR;
    LNode *s = (LNode *) malloc (sizeof(LNode));
    s -> data = e;
    s -> next = p -> next;
    p -> next = s;
    return OK;
}
//(10)ɾ��head�ĵ�3��Ԫ��
Status ListDelete(LinkList &L, int i){
    LNode *p = L;
    int j = 0;
    while(p && j < i - 1){
        p = p -> next;
        j++;
    }
    if(!(p -> next) || j > i - 1)
        return ERROR;
    LNode *q = p -> next;
    p -> next = q -> next;
    free(q);
    return OK;
}
Status FreeList(LinkList &L){
    LNode *p = L -> next;
    LNode *q = p -> next;
    while(q){
        q = p -> next;
        free(p);
        p = q;
    }
    free(p);
    free(L);
    return OK;
}
int main(void){
    //(1)��ʼ��������head
    LinkList head;
    InitList(head);
    //(2)���β���β�巨����a,b,c,d,e Ԫ��
    char a = 'a';
    LNode *p = NULL;//Ѳ��ָ��
	p = (LNode *)malloc(sizeof(LNode));
	p -> data = a;
	p -> next = NULL;
	a++;
	head -> next = p;
    for(int i = 2; i <= 5; i++){
    	 p -> next = (LNode *)malloc(sizeof(LNode));
    	 p = p -> next;
		 p -> data = a;
		 p -> next = NULL;
    	 a++;
    }
    cout<<"�������Ԫ��:"<<endl;
    ListOutput(head);
    cout<<"������鳤��:"<<endl;
    cout<< ListLength(head)<<endl;
    cout<<"����Ϊ����:"<<endl;
    cout<<isEmpty(head)<<endl;
    ElemType e;
    cout<<"���������Ԫ��:"<<endl;
    GetElem(head, 3, e);
    cout<<e<<endl;
    //(7)Ԫ��a��λ��:1
    cout<<"���e��λ��:"<<endl;
    cout<<GetNo(head,'e')<<endl;
    cout<<"�ڵ��ĸ�λ�ò���f:"<<endl;
    ListInsert(head, 4, 'f');
    ListOutput(head);
    cout<<"ɾ��������λ�õ�Ԫ��:"<<endl;
    ListDelete(head, 3);
    ListOutput(head);
    FreeList(head);
}
