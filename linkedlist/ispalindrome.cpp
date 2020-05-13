#include <iostream>

using namespace std;

struct Node
{
    char data;
    struct Node* next;
};

bool isPalindromeCheck(Node** left, Node* right)
{
    if(right == NULL)
        return true;
    
    bool isp = isPalindromeCheck(left, right->next);

    if(isp == false)
        return false;

    bool ispl = (right->data == (*left)->data);

    *left = (*left)->next;

    return ispl;
}

bool isPalindrome(Node* head)
{
    return isPalindromeCheck(&head, head);
}

/* Push a node to linked list. Note that this function 
changes the head */
void push(struct Node** head_ref, char new_data) 
{ 
    /* allocate node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
    /* put in the data */
    new_node->data = new_data; 
  
    /* link the old list off the new node */
    new_node->next = (*head_ref); 
  
    /* move the head to pochar to the new node */
    (*head_ref) = new_node; 

} 
  
// A utility function to print a given linked list 
void printList(struct Node* ptr) 
{ 
    while (ptr != NULL) { 
        cout  << ptr->data << "->"; 
        ptr = ptr->next; 
    } 
    cout << "NULL\n" ; 
} 

int main() 
{ 
    /* Start with the empty list */
    struct Node* head = NULL; 
    char str[] = "abacaba"; 
    int i; 
  
    for (i = 0; str[i] != '\0'; i++) { 
        push(&head, str[i]); 

    } 
    printList(head); 
    isPalindrome(head) ? cout << "Is Palindrome\n\n"  : cout << "Not Palindrome\n\n"; 
    return 0; 
} 