#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* pNext;
};

void insert(Node** pHead, int iData)
{
    struct Node* pNewNode = new Node();
    pNewNode->data = iData;
    pNewNode->pNext = (*pHead);

    *pHead = pNewNode;
}

void middleNode(Node* pHead)
{
    struct Node* pFast = pHead;
    struct Node* pSlow = pHead;
    struct Node* pPrev = NULL;
    if(pHead != NULL)
    {
        while(pFast != NULL && pFast->pNext != NULL)
        {
            pFast = pFast->pNext->pNext;
            pPrev = pSlow;
            pSlow = pSlow->pNext;
        }
    }
    pPrev->pNext = pSlow->pNext;
    delete pSlow;
   // cout<<"\n Middle element is: "<< pSlow->data<<endl;
}
void printList(struct Node *ptr)  
{  
    while (ptr != NULL)  
    {  
        printf("%d->", ptr->data);  
        ptr = ptr->pNext;  
    }  
    printf("NULL\n");  
}

int main()  
{  
    // Start with the empty list  
    struct Node* head = NULL;  
      
    // Iterate and add element  
    for (int i=5; i>0; i--)  
    {  
        insert(&head, i);  
        printList(head);  
        middleNode(head);  
        printList(head);  
    }  
  
    return 0;  
}  