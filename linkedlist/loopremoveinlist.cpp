#include <iostream>

using namespace std;

struct Node
{
    int data;

    struct Node* pNext;
};

Node* newNode(int key) 
{ 
    Node* temp = new Node; 
    temp->data = key; 
    temp->pNext = NULL; 
    return temp; 
} 

void detectLoop(Node* head)
{
     Node *slow_p = head, *fast_p = head; 
  
    while (slow_p && fast_p && fast_p->pNext) { 
        slow_p = slow_p->pNext; 
        fast_p = fast_p->pNext->pNext; 
        if (slow_p == fast_p) { 
            cout << "Found Loop "<<slow_p->data<<endl; ; 
            break;

            //return 1; 
        } 
    } 

    Node* ptr1 = head;
    Node* ptr2;
while(1)
{
ptr2 = slow_p;

while(ptr2->pNext != slow_p && ptr2->pNext != ptr1)
    ptr2 = ptr2->pNext;

    if(ptr2->pNext == ptr1)
        break;
    ptr1= ptr1->pNext;
}
    ptr2->pNext = NULL;
}

// A utility function to print a linked list 
void printList(Node* head) 
{ 
    while (head != NULL) { 
        cout << head->data << " "; 
        head = head->pNext; 
    } 
    cout << endl; 
} 

int main() 
{ 
    Node* head = newNode(50); 
    head->pNext = head; 
    head->pNext = newNode(20); 
    head->pNext->pNext = newNode(15); 
    head->pNext->pNext->pNext = newNode(4); 
   // head->pNext->pNext->pNext->pNext = newNode(10); 
  
    /* Create a loop for testing */
    head->pNext->pNext->pNext->pNext  = head->pNext; //->pNext->pNext = head->pNext->pNext; 
  
    detectLoop(head);
    printf("Linked List after removing loop \n"); 
    printList(head); 
  
    return 0; 
} 