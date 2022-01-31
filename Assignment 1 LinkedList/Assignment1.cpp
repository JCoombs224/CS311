// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
using namespace std;

/**
 * @brief Singly Linked Node that contains integer value and a pointer to the
 *        next node.
 */
struct Node
{
	int val;
	Node *next = NULL;

    Node(){}
    Node(int value)
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
    void appendNode(int n)
    {
        Node *node = new Node(n);
        if(head == nullptr)
        {
            head = node;
            tail = node;
        }
        else if(head->next == nullptr)
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

/**
 * @brief Calculates the union between two linked lists and returns
 *        the set as a LinkedList.
 * 
 * @param listA 
 * @param listB 
 * @return LinkedList* 
 */
LinkedList *unionLL(LinkedList *listA, LinkedList *listB)
{
    Node *pA = listA->head;
    Node *pB = listB->head;
    int temp;

    LinkedList *set = new LinkedList();

    while(pA != NULL && pB != NULL)
    {
        if(pA->val == pB->val)
        {
            pA = pA->next;
        }
        else if(pA->val < pB->val)
        {
            temp = pA->val;
            set->appendNode(temp);
            pA = pA->next;
        }
        else if(pA->val > pB->val)
        {
            temp = pB->val;
            set->appendNode(temp);
            pB = pB->next;
        }
        
    }

    // If one of the lists still has nodes to be added, 
    // iterate through the rest of that list.
    while(pA != NULL)
    {
        if(temp != pA->val)
        {
            set->appendNode(pA->val);
        }
        temp = pA->val;
        pA = pA->next;
    }
    while(pB != NULL)
    {
        if(temp != pB->val)
        {
            set->appendNode(pB->val);
        }
        temp = pB->val;
        pB = pB->next;
    }    

    return set;
}

/**
 * @brief Merges two LinkedLists together in non-descending order into
 *        a new LinkedList.
 * 
 * @param listA 
 * @param listB 
 * @return LinkedList* 
 */
LinkedList *mergeLL(LinkedList *listA, LinkedList *listB)
{
    Node *pA = listA->head;
    Node *pB = listB->head;

    LinkedList *list = new LinkedList();

    while(pA != NULL && pB != NULL)
    {
        if(pA->val < pB->val)
        {
            list->appendNode(pA->val);
            pA = pA->next;
        }
        else if(pA->val > pB->val)
        {
            list->appendNode(pB->val);
            pB = pB->next;
        }
        else
        {
            list->appendNode(pA->val);
            list->appendNode(pB->val);
            pA = pA->next;
            pB = pB->next;
        }
    }

    // If one of the lists still has nodes to be added, 
    // iterate through the rest of that list.
    while(pA != NULL)
    {
        list->appendNode(pA->val);
        pA = pA->next;
    }
    while(pB != NULL)
    {
        list->appendNode(pB->val);
        pB = pB->next;
    }    

    return list;
}

// Fills list A as defined in Assignment 1
void fillListA(LinkedList *listA)
{
    listA->appendNode(3);
    listA->appendNode(5);
    listA->appendNode(8);
    listA->appendNode(11);
}
// Fills list B as defined in Assignment 1
void fillListB(LinkedList *listB)
{
    listB->appendNode(2);
    listB->appendNode(6);
    listB->appendNode(8);
    listB->appendNode(9);
    listB->appendNode(22);
    listB->appendNode(24);
}

// Main function
int main()
{
    LinkedList *listA = new LinkedList();
    LinkedList *listB = new LinkedList();
    fillListA(listA);
    fillListB(listB);
    
    LinkedList *unionAB = unionLL(listA, listB);
    LinkedList *mergeAB = mergeLL(listA, listB);

    cout << "List A: ";
    listA->printList();
    
    cout << "\nList B: ";
    listB->printList();

    cout << "\nUnion ListAB: ";
    unionAB->printList();

    cout << "\nList A and List B merged: ";
    mergeAB->printList();

    cout << "\n\nOriginal lists are unaffected.\n";
    cout << "List A: ";
    listA->printList();
    
    cout << "\nList B: ";
    listB->printList();

    cout << "\n\n";

    return 0;
}
