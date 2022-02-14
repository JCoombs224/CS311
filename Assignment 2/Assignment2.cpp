// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
using namespace std;

struct Node
{
	char val;
	Node *next = NULL;

    Node(){}
    Node(char value)
    {
        val = value;
    }
    ~Node(){}
};

/**
 * @brief Singly LinkedList class that has a pointer to the head and tail
 *        node. Contains an append function to add node after the tail.
 */
struct LinkedList
{
    Node *head;
    Node *tail;
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    LinkedList(Node *node)
    {
        head = node;
        tail = node;
    }

    // **** FUNCTIONS ****
    // Append a new node to end of the list
    void appendNode(char c)
    {
        Node *node = new Node(c);
        if(head == NULL)
        {
            head = node;
            tail = node;
        }
        else if(head->next == NULL)
        {
            head->next = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }
    // Print the list to the console
    void printList()
    {
        Node *p = head;
        int val;
        while(p != NULL)
        {
            val = p->val;
            cout << val << " ";
            p = p->next;
        }
    }
    // List destructor
    ~LinkedList()
    {
        Node *current = head;
        while( current != NULL ) 
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = NULL;
    }
};

struct Stack
{
    int size = 0;
    LinkedList *list = new LinkedList();

    Stack(){}

    void push(char c)
    {
        list->appendNode(c);
        size++;
    }
    char pop()
    {
        if(size < 1)
            return 0;
        
        Node *temp = list->head;
        list->head = list->head->next;
        size--;
        return temp->val;
    }
    char peekTop()
    {
        if(size < 1)
            return 0;
        
        return list->head->val;
    }
};

int main()
{

    return 0;
}