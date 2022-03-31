// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int data)
    {
        val = data;
        left = NULL;
        right = NULL;
    }
    ~Node(){}
};

class BST
{
    private:
        Node *root;
        int size = 0;
        void preOrder(Node *node)
        {
            if(node != NULL)
            {
                cout << node->val << ' ';
                preOrder(node->left);
                preOrder(node->right);
            }
        }
        void inOrder(Node *node)
        {
            if(node != NULL)
            {
                inOrder(node->left);
                cout << node->val << ' ';
                inOrder(node->right);
            }
        }
        void postOrder(Node *node)
        {
            if(node != NULL)
            {
                postOrder(node->left);
                postOrder(node->right);
                cout << node->val << ' ';
            }
        }
    public:
        // Constructor
        BST()
        {
            root = NULL;
        }
        int getSize()
        {
            return size;
        }

        // Class Functions
        void insert(int val)
        {
            root = insert(root, val);
            size++;
        }
        Node* insert(Node *node, int val)
        {
            if(node == NULL)
                node = new Node(val);
            else if(node->val > val)
                node->left = insert(node->left, val);
            else if(node->val < val)
                node->right = insert(node->right, val);

            return node;
        }
        Node* search(int key)
        {
            return search(root, key);
        }
        Node* search(Node *node, int key)
        {
            if(node == NULL || node->val == key)
                return node;
            else if(node->val > key)
                return search(node->left, key);
            return search(node->right, key);
        }
        void remove(int key)
        {
            root = remove(root, key);
            size--;
        }
        Node* remove(Node *node, int key)
        {
            if(node == NULL)
                return node;
            if(node->val > key)
            {
                node->left = remove(node->left, key);
            }
            else if(node->val < key)
            {
                node->right = remove(node->right, key);
            }
            else
            {
                if(node->left == NULL)
                {
                    Node *temp = node->right;
                    delete node;
                    return temp;
                }
                else if(node->right == NULL)
                {
                    Node *temp = node->left;
                    delete node;
                    return temp;
                }
                
                Node *temp = leftmostNode(node->left);
                node->val = temp->val;
                node->left = remove(node->left, temp->val);
            }
            return node;
        }
        Node* leftmostNode(Node *node)
        {
            Node *current = node;

            while(current->right != NULL)
                current = current->right;
            return current;
        }
        Node* findMax()
        {
            if(root == NULL)
                return NULL;
            Node *current = root;
            while(current->right != NULL)
                current = current->right;
            return current;
        }
        Node *findMin()
        {
            if(root == NULL)
                return NULL;
            Node *current = root;
            while (current->left != NULL)
                current = current->left;
            return current;
        }
        // Tree Traversal
        void printPreOrder()
        {
            preOrder(root);
            cout << endl;
        }
        void printInOrder()
        {
            inOrder(root);
            cout << endl;
        }
        void printPostOrder()
        {
            postOrder(root);
            cout << endl;
        }
        // Printing
        void print()
        {
            print(root, 0);
        }
        void print(Node *root, int space)
        {
            if(root == NULL)
                return;
            
            
        }
};

int main()
{
    int arrSize = 0;
    string input, temp = "";
    int arr[50];

    cout << "Enter up to 50 integers seperated by spaces to be added to BST: ";
    getline(cin, input);

    // Get set of integers from user.
    for(int i = 0; i < input.size(); i++)
    {
        // Break loop if max elements have been added to array.
        if(arrSize > 49)
        {
            cout << "Error: Array limit reached the last element is: " << arr[49] << endl;
            break;
        }
        if(input[i] >= '0' && input[i] <= '9')
        {
            temp += input[i];
        }
        else if(input[i] == ' ')
        {
            if(temp != "")
            {
                arr[arrSize++] = stoi(temp);
                temp = "";
            }
        }
        else
        {
            cerr << "Invalid input! Exiting...\n\n";
            return -1;
        }
    }
    // Add last element to array
    if(arrSize < 50 && temp != "")
    {
        arr[arrSize++] = stoi(temp);
        temp = "";
    }

    BST tree;
    // Now loop through list and insert into BST
    for(int i = 0; i < arrSize; i++)
        tree.insert(arr[i]);

    int selection;

    // 1. Tree Traversal
    cout << "\nPre-order tree traversal: "; 
    tree.printPreOrder();
    cout << "In-order tree traversal: "; 
    tree.printInOrder();
    cout << "Post-order tree traversal: "; 
    tree.printPostOrder();

    // 2. Searching
    int key;
    cout << "\nEnter an integer to search for in the tree: ";
    cin >> key;
    Node *node = tree.search(key);

    if(node == NULL)
        cout << key << " was not found in the BST.\n\n";
    else
    {
        cout << "Node with value " << key << " was found in BST.\n";
        cout << key << " left node value: ";
        if(node->left == NULL) cout << "NULL\n"; else cout << node->left->val << endl;
        cout << key << " right node value: ";
        if(node->right == NULL) cout << "NULL\n"; else cout << node->right->val << endl;
    }

    // 3. Insertion
    cout << "\nEnter a new value to be added into the binary tree: ";
    cin >> key;
    tree.insert(key);
    cout << "Tree with " << key << " inserted: ";
    tree.printInOrder();

    // 4. Deletion
    cout << "\nEnter a value to be deleted from the tree: ";
    cin >> key;
    tree.remove(key);
    cout << "Tree with " << key << " removed: ";
    tree.printInOrder();

    // 5. Print tree
    tree.print();

    return 0;
}
