#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int a):data(a),next(NULL){}
    /* data */
};

void reverse(Node** head) {

    Node* current = *head;
    Node* prev = NULL;
    Node* next = NULL;

    while(current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;

    }

    *head = prev;
}


void rotate(Node** head, int count)
{
    Node* current = *head;

    while(count > 1)
    {
        current = current->next;
        --count;
    }
    
    Node* newHead = current;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = *head;
    *head = newHead->next;
    newHead->next = NULL;



}

void rotateBlockwise(Node** head, int k)
{
    Node* current  = *head;
    Node* current1;
    bool flag = false;
    Node* prev = *head;
    while(current->next != NULL)
    {
        int d = 1;
        current1 = current;
        while(d < k-1 && current->next != NULL)
        {
            prev = current;
            current = current->next;
            d++;
        }

        if(current->next != NULL)
        {
            Node* tmp = current->next;
            current->next = tmp->next;
            prev->next = tmp;
            tmp->next = current1;
            if(!flag)
            {
                *head = tmp;
                flag = true;
            }

            current = current->next;
        }

        
    }
}

void printNode(Node* head)

{
    Node* root = head;
    while(root != NULL){
        cout<<root->data<<"->";
        root = root->next;
    }
        
    cout<<"NULL"<<endl;
}

int main()
{
    Node* root = new Node(1);
    root->next = new Node(2);
    root->next->next = new Node(3);
    root->next->next->next = new Node(4);
    root->next->next->next->next = new Node(5);
    printNode(root);
    reverse(&root);
    printNode(root);

    rotate(&root, 3);
    printNode(root);

    rotateBlockwise(&root, 2);
    printNode(root);
    return 0;
}