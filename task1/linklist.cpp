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

Status InitList(LinkList &l){//传入的是链表头指针的引用 给头指针分配空间
    l = (LNode *)malloc(sizeof(LNode));
    if(!l)
        return ERROR;
    l -> next = NULL;
    return OK;
}

//(3)输出单链表head:a b c d e
void ListOutput(LinkList L){//传入头指针
	LNode *p = L -> next;
	while(p){
		cout<<p -> data;
		p = p -> next;
		//cout<<"!"<<endl;
	}
	cout<<endl;
}
//(4)单链表head长度:5
int ListLength(LinkList L){
    int Length = 0;
    LNode *p = L -> next;
    while(p){
        ++ Length;
        p = p -> next;
    }
    return Length;
}
//(5)单链表head为非空
bool isEmpty(LinkList L){
    LNode *p = L -> next;
    if(p)
        return false;
    else
        return true;
}
//(6)单链表head的第3个元素:c
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
//(7)元素a的位置:1
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
    if(p == NULL)//超越了
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

//(8)在第4个元素位置上插入f元素
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
//(10)删除head的第3个元素
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
    //(1)初始化单链表head
    LinkList head;
    InitList(head);
    //(2)依次采用尾插法插入a,b,c,d,e 元素
    char a = 'a';
    LNode *p = NULL;//巡游指针
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
    cout<<"输出数组元素:"<<endl;
    ListOutput(head);
    cout<<"输出数组长度:"<<endl;
    cout<< ListLength(head)<<endl;
    cout<<"数组为空吗:"<<endl;
    cout<<isEmpty(head)<<endl;
    ElemType e;
    cout<<"输出第三个元素:"<<endl;
    GetElem(head, 3, e);
    cout<<e<<endl;
    //(7)元素a的位置:1
    cout<<"输出e的位置:"<<endl;
    cout<<GetNo(head,'e')<<endl;
    cout<<"在第四个位置插入f:"<<endl;
    ListInsert(head, 4, 'f');
    ListOutput(head);
    cout<<"删除第三个位置的元素:"<<endl;
    ListDelete(head, 3);
    ListOutput(head);
    FreeList(head);
}
