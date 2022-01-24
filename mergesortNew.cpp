#include <iostream>
//if you're not going to change the arguments in a function, no need to use ampersand
using namespace std;

struct Node
{
    int value;
    Node* next;
    Node* prev;
};
//QUEUES
void deleteNode(Node* front, int value)
{
    Node* current = front;
    for(; current; current = current->next)
    {
        if (current->value == value)
        {
            current->next->prev = NULL;
            delete current;
        }
    }
}
void dequeue(Node* &front) // remove from front
{
	Node* temp; // used to hold the item we want to delete
	//this is where we need to focus!
	if(front)  // if there is an item there that we can dequeue
	{
		temp = front;         // temp = front value so we can dequeue temp
		front = front->next;  // make our new front the element after front
		delete temp;          // dequeue
		//if(!front)            // empty list, can't dequeue
		//{
			//rear = NULL;
		//}
	}
}
void enqueue(Node* &front, Node* &rear, int value) // put it at the end 
//pass by alias to affect front and rear directly
{
    Node* nn = new Node;    // new node allocated on heap
    nn->value = value;      // new node value gets our passed value
	nn->next = NULL;        // end value
	//differentiate between an empty queue and not empty queue
	if(!front) // checking if empty
	{
		std::cout << "In !front(), nn->value: " << nn->value << std::endl;
		rear = front = nn; // first assignment so both the rear and front get nn as their value
		//assign rear and front with the Node nn
	}
	else //not an empty list, insert another node
	{
		std::cout << "In else(), nn->value: " << nn->value << std::endl;
		rear->next = nn; // the old rear's next member points to our new node
        nn->prev = rear; // the new rear's prev member is the old rear
		rear = nn;       // nn becomes the new rear in our list (enqueue happens at the rear)
        rear->next = NULL;
	}
}
int traverse(Node* front)
{
	std::cout << "In traverse() " << std::endl;
    int i = 0;
	Node* currentNode;
	for(currentNode = front; currentNode; currentNode = currentNode->next)
	{
		std::cout << currentNode->value << std::endl;
        i++;
	}
    return i;
}
void split (Node* head,Node*&a,Node*&b) // my linked list {1,3,7,9,4}; // 4->9->7->3->1->NULL
{
    cout << "in split()\n";
    a = head;
    Node* current = new Node;
    // traverse
    int length = traverse(head);  // get length of array
    // get length
    cout << "length: " << length << endl;
    //Node* middle = new Node;
    //middle = head+(length/2);
    // partition1 = 0...length / 2;
    // partition2 = length/2...NULL
    int i =0;
    current = head;
    while (current)// && i <((length/2) +1))
    {
        std::cout << "In while()\n";
        if (i == (length/2))
        {
            b = current;
            std::cout << "b->value: " << b->value <<std::endl;
            std::cout << current->prev->value << std::endl;
            current->prev->next = NULL; // NEW
            break;
        }
        i++;
        current = current->next;
    }
    std::cout << "a: " << a->value << endl;
    std::cout << "b: " << b->value << endl;
    std::cout << "a list: \n";
    for(current = a; current; current = current->next)
    {
        std::cout << current->value <<std::endl;
    }
    std::cout << "b list: \n";
    for(current = b; current; current = current->next)
    {
        std::cout << current->value <<std::endl;
    }
}
Node* merge(Node* a, Node* b)
{
    //delete for a and b
    std::cout << "In merge(" << a->value << ", " << b->value << ")\n";
    // have a node* c that points to the sorted list of partition1
    // return c to have node* a = c 
    // have a node* c that points to the sorted list of partition2
    // return node* c to have node* b = c
    //Node* c = new Node; //points to the sorted list of partition1
    Node* c = NULL; // pointer to front of our merged list
    //Node* z = NULL; //for deleting a node from a after transfer to list c
    //Node* y = NULL; // for deleting a node from b after transfer to list c
    //z = a;
    //y = b;
    //Node* current = new Node;
    Node* rear = new Node;
    /*
    You will have a loop that processes the 2 lists against one another and creates another list which will contain the nodes in sorted order. 
    The loop will end as soon as one of the lists is completely processed
    */
    while (a != NULL && b != NULL) //(a != NULL && b != NULL)
    {
        std::cout << "In while999()\n";
        std::cout << "a: " << a->value << ", b: " << b->value << std::endl;
        if (a->value < b->value)
        {
            std::cout << a->value << " < " << b->value << std::endl;
            enqueue(c, rear, a->value);
            dequeue(a);
            //a = a->next;
        }
        else
        {
            std::cout << b->value << " <= " << a->value << std::endl;
            enqueue(c, rear, b->value);
            dequeue(b);
            //b = b->next;
        }
    }
    /*
    After the above loop completes, 
    you will have another loop that processes the rest of what is remaining in the linked list that has not been fully processed. 
    You will need to have one loop for each of the lists.
    */
    while (a != NULL)
    {
        std::cout << "In finish for a[]\n";
        //z = a; //new
        //cout << "z.value =" << z->value << endl;
        enqueue(c, rear, a->value);   // ERROR: first enqueue is not going to the !front case in equeue
        dequeue(a);
        //a = a->next;
    }
    while(b != NULL)
    {
        std::cout << "In finish for b[]\n";
        //z = b;//new
        enqueue(c, rear, b->value);
        dequeue(b);
        //b = b->next;
    }
    return c;
    //merge temp lls back into 
    // the size of all the nodes of a and all the nodes of b   
}
Node* mergeSort(Node* head)
{
    std::cout << "In mergeSort()\n";
    Node* a = new Node;    //points to left partition
    Node* b = new Node;    //points to right partition
    Node* c = new Node;    //the merged linked list of left partition and right partition
    a = NULL;
    b = NULL;
    if (head == NULL)      //no linked list
    {
        std::cout << "In base case 1 for mergeSort()\n";
        return NULL;
    }
    if(head->next == NULL)//just one element
    {
        std::cout << "in base case 2 for mergeSort()\n";
        return head; // this is where we have split our entire array into single elements. Then we merge in sorted ascending order.
    }
    else                 //at least 2 elements
    {
        std::cout << "in else()\n";
        std::cout << "head: " << head->value << std::endl;
        split(head, a, b); // continually split until each partition are single elements
        //first call split(4, new Node, new Node)
        //a = mergeSort(a);  // a == left partition 
        //b = mergeSort(b);  // b == right partition
    }
    // get a and b down to single values that point to NULL
    a = mergeSort(a);  // a == left partition 
    std::cout << "after mergeSort(a): " << a->value << std::endl;
    b = mergeSort(b);  // b == right partition
    std::cout << "after mergeSort(b): " << b->value << std::endl;
    c = merge(a,b); // take the individual values of a and b and merge them 
    Node * current = c;
    std::cout << "c: ";
    for (; current; current = current->next)
    {
        std::cout << current->value << ", ";
    }
    std::cout << std::endl;
    
    return c; // return the mergeSorted linked list after merging the two partitions
}

int main()
{
    Node* front = NULL;
    Node* rear = NULL;
    Node* a = NULL;
    int array[] = {105,65,204,9,7,3,1,13,15,2,31,4};
    //int array[] = {10, 9, 8, 7, 33, 2, 5, 27, 17, 13, 1, 999,21};
    int arraySize = sizeof(array)/sizeof(array[0]);
    std::cout << "Size of array: " << arraySize << std::endl;
    for (size_t i = 0; i < arraySize; i++)
    {
        //push(top, bottom, array[i]);
        enqueue(front, rear, array[i]);
    }
    int count = traverse(front);
    //int count = traverse(top);
    //top = mergeSort(top);
    //top = mergeSort(top);
    front = mergeSort(front);
    cout << "After mergeSort()\n";
    int count2 = traverse(front);
    return 0;
}

/*
WRONG:

merge() 
int i = 0;
    c = a;
    for(; c; c = c->next)
    {
        std::cout << "first\n";
        c->value = a->value;
        i++;
    }
    int j = 0;
    c = b;
    for(; c; c = c->next )
    {
        std::cout << "second\n";
        if (j > i)
        {
            std::cout << "in if()\n";
            c->value = b->value;
        }
        j++;
    }
    int count = 0;
    for(current = c; c ; c = c->next)
    {
        count++;
    }
    std::cout << "count of c is " << count << endl;
    //now compare and copy correctly
    //while(a->next != NULL && b->next != NULL)
    std::cout << c << endl;
    while(a && b)
    {
        std::cout <<"in while()\n";
        if(a->value <= b->value)
        {
            std::cout << "in if()\n";
            //c->value = a->value;
            c = a;
            a = a->next;
            std::cout << "a->value : "  << a->value << endl;
            std::cout << "c->value: " << c->value << endl;
        }
        else
        {
            std::cout << "in else()\n";
            c->value = b->value;
            b = b->next;
        }
        c = c->next;
    }
    for (current = a; current; current = current->next)
    {
        std::cout << current->value <<std::endl;
    }
    for (current = b; current; current = current->next)
    {
        std::cout << current->value <<std::endl;
    }
    for (current = c; current; current = current->next)
    {
        std::cout << current->value <<std::endl;
    }
    // now either a or b will not be empty so we need to copy the rest of either into our c linked list

    //copy the rest of a into c
    //while (a->next != NULL)
    while (a != NULL)
    {
        std::cout << "in a's while()\n";
        c = c->next;
        a = a->next;
        c->value = a->value;
        std::cout << c->value << " " << a->value << endl;
        c = c->next;
        std::cout << c << endl;
        a = a->next;
        std::cout << a <<endl;
        // delete a; // ?
    }
    //copy the rest of b into c
    //while (b->next != NULL)
    while (b != NULL)
    {
        c = c->next;
        std::cout << "In b's while()\n";
        c->value = b->value;
        c = c->next;
        b = b->next;
        //delete b; // ?
    }
    std::cout << c << std::endl;
    std::cout << "returning\n";

*/