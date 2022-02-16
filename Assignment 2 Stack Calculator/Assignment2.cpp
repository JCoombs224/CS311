// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
#include <string>
using namespace std;

// ************************** CLASSES **************************

template<class T>
struct Node
{
	T val;
	Node *next = NULL;

    Node(){}
    Node(T value)
    {
        val = value;
    }
    ~Node(){}
};

/**
 * @brief Singly LinkedList class that has a pointer to the head and tail
 *        node. Contains an append function to add node after the tail.
 */
template<class T>
struct LinkedList
{
    Node<T> *head;
    Node<T> *tail;
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    LinkedList(Node<T> *node)
    {
        head = node;
        tail = node;
    }

    // **** FUNCTIONS ****
    // Append a new node to end of the list
    void appendNode(T val)
    {
        Node<T> *node = new Node<T>(val);
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
    // Adds to the beginning of the list
    void prependNode(T val)
    {
        Node<T> *node = new Node<T>(val);
        node->val = val;
        if(head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->next = head;
            head = node;
        }
    }
    // Print the list to the console
    void printList()
    {
        Node<T> *p = head;
        while(p != NULL)
        {
            T val = p->val;
            cout << val << " ";
            p = p->next;
        }
    }
    // List destructor
    ~LinkedList()
    {
        Node<T> *current = head;
        while( current != NULL ) 
        {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }
        head = NULL;
    }
};

/**
 * @brief Stack data structure with first in first out functionality.
 *        Utilizes a LinkedList to store the values.
 * 
 * @tparam T - Type of variable stored in the Stack
 */
template<class T>
class Stack
{
    private:
        int size = 0;
        LinkedList<T> *list = new LinkedList<T>();

    public:
        // Default Constructor
        Stack(){}

        // Pushes an element to the top of the Stack
        void push(T val)
        {
            list->prependNode(val);
            size++;
        }

        // Removes element from top of Stack and returns its value
        T pop()
        {
            if(size < 1)
                return 0;
            
            Node<T> *temp = list->head;
            list->head = list->head->next;
            size--;
            return temp->val;
        }

        // Returns the value of the element on top of the Stack
        T peekTop()
        {
            if(size < 1)
                return 0;
            
            return list->head->val;
        }

        // Returns size of the Stack
        int getSize()
        {
            return size;
        }

        // Stack Destructor
        ~Stack()
        {
            delete list;
        }
};

// ************************** PROGRAM FUNCTIONS **************************

/**
 * @brief Creates a weighted operator priority table.
 *        1 = '<'
 *        2 = '='
 *        3 = '>'
 *        -1 = 'Error'
 */
int operatorMap[7][7] =
{
  // +  -  *  /  (  )  #
    {3, 3, 1, 1, 1, 3, 3}, // +
    {3, 3, 3, 3, 1, 3, 3}, // -
    {3, 3, 1, 1, 1, 3, 3}, // *
    {3, 3, 3, 3, 1, 3, 3}, // /
    {1, 1, 1, 1, 1, 2, -1}, // (
    {3, 3, 3, 3, -1, 3, 3}, // )
    {1, 1, 1, 1, 1, -1, 2} // #
};

/**
 * @brief Checks if the given character is an operator symbol.
 * 
 * @param c - Given character
 * @return true if it is an operator
 * @return false  if it is not an operator
 */
bool isOperator(char c)
{
    string operatorKey = "+-*/()#"; // operator symbols
    for(int i = 0; i < operatorKey.size(); i++)
    {
        if(c == operatorKey[i])
            return true;
    }

    return false;
}

/**
 * @brief Returns the ID of the operator.
 *        The ID is the coordiante used in the precedence map.
 * 
 * @param c - operator symbol
 * @return short int - ID
 */
short int optrID(char c)
{
    switch(c)
    {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '(':
            return 4;
        case ')':
            return 5;
        case '#':
            return 6;
    };

    return -1;
}

/**
 * @brief Does the given operation in 'op' betwen number a and b.
 * 
 * @param a - number on the left of operation
 * @param op - operator symbol
 * @param b - number on the right of the operation
 * @return double 
 */
double operate(double a, char op, double b)
{
    switch(op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }

    return -1;
}

/**
 * @brief Returns the result as a double of a given expression from
 *        a string of chars beginning and ending with a '#' symbol.
 * 
 * @param exp 
 * @return double 
 */
double evalExpression(const char *exp)
{
    Stack<double> operands;
    Stack<char> operators;

    char currentOp;
    int a, b;

    operators.push('#');
    exp++;

    while(!(*exp == '#' && operators.peekTop() == '#'))
    {
        // Check if input is an operand
        if(*exp >= '0' && *exp <= '9')
        {
            // Since operands can be more than one digit we create a temp string and
            // continue to add digits until the pointer is no longer a numeric value.

            string temp = "";
            while((*exp >= '0' && *exp <= '9') || *exp == '.')
            {
                temp += *exp;
                exp++;
            }

            // Convert temp string to double and add to operands
            operands.push(stod(temp));
        }
        else if(isOperator(*exp))
        {
            int prevOpID = optrID(operators.peekTop());
            int currID = optrID(*exp);

            if(operatorMap[prevOpID][currID] == -1)
            {
                // Handle exception here
            }
            else if(operatorMap[prevOpID][currID] == 1)
            {
                operators.push(*exp);
                exp++;
            }
            else if(operatorMap[prevOpID][currID] == 2)
            {
                operators.pop();
                exp++;
            }
            else if(operatorMap[prevOpID][currID] == 3)
            {
                currentOp = operators.pop();
                a = operands.pop();
                b = operands.pop();
                operands.push(operate(a, currentOp, b));
            }
        }
        else
        {
            exp++;
        }
    }
    return operands.peekTop();
}

// Main Function
int main()
{
    const char *expression = "#5 + 5 * (10 * 10)#";

    cout << evalExpression(expression) << endl;
    
    return 0;
}