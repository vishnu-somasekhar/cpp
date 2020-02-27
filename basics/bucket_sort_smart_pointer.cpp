#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <memory>
#include <vector>


using namespace std;

#define _MAX_ARRAY_SIZE 15
#define _MAX_BUCKET_SIZE 8
#define _BUCKET_RANGE 10

struct Node
{
    int data;
    shared_ptr<Node> next;

    Node():data(-1){};
    Node(int i):data(i){};
};
void printBucket(shared_ptr<Node> list);
void BucketSoft(int array[]);
void InsertionSort( shared_ptr<Node> &list);
void Print(int array[]);

int getBucketIndex(int value);

void BucketSort(int array[])
{
    int i, j;

    vector<shared_ptr<Node>> buckets(_MAX_BUCKET_SIZE);



    for(i = 0; i < _MAX_ARRAY_SIZE; i++) {
        shared_ptr<Node> current = make_shared<Node>();
        int pos = getBucketIndex(array[i]);
        current->data = array[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    for(i = 0; i < _MAX_BUCKET_SIZE; i++) {
        cout<< "Bucket[" << i << "] : ";
        printBucket(buckets[i]);
        cout<<endl;
    }

    for(i = 0; i < _MAX_BUCKET_SIZE; i++) {
        InsertionSort(buckets[i]);
    }

    	/* check what's in each bucket */
	cout << "-------------" << endl;
	cout << "Bucktets after sorted" << endl;
    for(i = 0; i < _MAX_BUCKET_SIZE; i++) {
        cout<< "Bucket[" << i << "] : ";
        printBucket(buckets[i]);
        cout<<endl;
    }

    for(j = 0, i = 0; i < _MAX_BUCKET_SIZE; ++i) {
        shared_ptr<Node> current = buckets[i];
        while(current != nullptr) {
            array[j++] = current->data;
            current = current->next;
        }
    }
}

void InsertionSort(shared_ptr<Node> &list) {

    shared_ptr<Node> k = make_shared<Node>();
    shared_ptr<Node> nodeList = make_shared<Node>();

    if(list == nullptr) {
        return;
        if(list->next == nullptr)
            return;
    }

    nodeList = list;
    k = list->next;
    nodeList->next = nullptr;

    while(k != nullptr) {

        shared_ptr<Node> ptr = make_shared<Node>();

        if(nodeList->data > k->data) {
            shared_ptr<Node> tmp = make_shared<Node>();
            tmp = k;
            k = k->next;
            tmp->next = nodeList;
            list = tmp;
            continue;
        }

        for(ptr = list; ptr->next != nullptr; ptr = ptr->next) {
            if(ptr->next->data > k->data) break;
        }

        if(ptr->next != nullptr) {
            shared_ptr<Node> tmp = make_shared<Node>();
            tmp = k;
            k = k->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
            continue;
        }
        else {
            ptr->next = k;  
			k = k->next;  
			ptr->next->next = 0; 
			continue;
        }
        
    }

   // list = nodeList;

}

int getBucketIndex(int value)
{
	return value/_BUCKET_RANGE;
}

void print(int ar[])
{	
	int i;
	for(i = 0; i < _MAX_ARRAY_SIZE; ++i) { 
		cout << setw(3) << ar[i]; 
	}
	cout << endl;
}

void printBucket(shared_ptr<Node> list)
{
	while(list) {
		cout << setw(3) << list->data;
		list = list->next;
	}
}

int main(void)
{	
	int array[_MAX_ARRAY_SIZE] = {29,25,3,3,49,9,37,1,21,43};

	cout << "Initial array" << endl;
	print(array);
	cout << "-------------" << endl;

	BucketSort(array); 
	cout << "-------------" << endl;
	cout << "Sorted array"  << endl;
	print(array); 
    cin.get();
	return 0;
}