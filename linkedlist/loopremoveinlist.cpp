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
    struct Node* slow = head;
    struct Node* fast = head->pNext;

    while(fast && fast->pNext) {

        if(slow == fast)
            break;
        
        slow = slow->pNext;
        fast = fast->pNext->pNext;
    }

    if(slow == fast)
    {
        while(fast->pNext == slow)
            fast = fast->pNext;

        fast->pNext = NULL;
    }

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
    head->pNext->pNext->pNext->pNext = newNode(10); 
  
    /* Create a loop for testing */
    head->pNext->pNext->pNext->pNext->pNext = head->pNext->pNext; 
  
    detectLoop(head);
    printf("Linked List after removing loop \n"); 
    printList(head); 
  
    return 0; 
} 