// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
#include <iomanip>
#include <string>
// used for sleep function
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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

struct TreeBranch
{
    TreeBranch *prev;
    string str;
 
    TreeBranch(TreeBranch *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};


class BST
{
    private:
        Node *root;
        int size = 0;

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
            else if(node->val == val) // if value being inserted the same as current node insert to the left
                node->left = insert(node->left, val);

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
        bool remove(int key)
        {
            root = remove(root, key);
            if(root == NULL)
                return false;

            size--;
            return true;
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
                
                Node *temp = rightmostNode(node->left);
                node->val = temp->val;
                node->left = remove(node->left, temp->val);
            }
            return node;
        }
        Node* rightmostNode(Node *node)
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
        void preOrder(Node *node)
        {
            if(node != NULL)
            {
                cout << node->val << ' ';
                preOrder(node->left);
                preOrder(node->right);
            }
        }
        void printInOrder()
        {
            inOrder(root);
            cout << endl;
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
        void printPostOrder()
        {
            postOrder(root);
            cout << endl;
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
        // Printing
        void printTree()
        {
            printTree(root, nullptr, false);
        }
        // TODO: Make custom printing function
        // Helper function to print branches of the binary tree
        void showBranches(TreeBranch *p)
        {
            if (p == nullptr) {
                return;
            }
        
            showBranches(p->prev);
            cout << p->str;
        }
        void printTree(Node* root, TreeBranch *prev, bool isLeft)
        {
            if (root == nullptr) {
                return;
            }
        
            string prev_str = "    ";
            TreeBranch *branch = new TreeBranch(prev, prev_str);
        
            printTree(root->right, branch, true);
        
            if (!prev) {
                branch->str = "---";
            }
            else if (isLeft)
            {
                branch->str = ".---";
                prev_str = "   |";
            }
            else {
                branch->str = "`---";
                prev->str = prev_str;
            }
        
            showBranches(branch);
            cout << " " << root->val << endl;
        
            if (prev) {
                prev->str = prev_str;
            }
            branch->str = "   |";
        
            printTree(root->left, branch, false);
        }

        // Destructor
        ~BST()
        {
            while(root != NULL)
                remove(root->val);
        }
};

/*********** MAIN PROGRAM ***********/
void traverseTree(BST&);
void searchNode(BST&);
void insertNode(BST&);
void deleteNode(BST&);
void displayTree(BST&);

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
    
    // Program loop
    while(true)
    {
        // Display operation menu
        cout << "\nBinary Search Tree Operation Menu\n\n";
        cout << "1. Tree Traversal\n";
        cout << "2. Search Node\n";
        cout << "3. Insert Node\n";
        cout << "4. Delete Node\n";
        cout << "5. Display Tree\n";
        cout << "6. Exit Program\n";

        cout << "\nEnter selection: ";
        cin >> selection;

        // Run selected function
        switch(selection)
        {
            case 1:
                traverseTree(tree);
                Sleep(2000);
                break;
            case 2:
                searchNode(tree);
                Sleep(2000);
                break;
            case 3:
                insertNode(tree);
                Sleep(2000);
                break;
            case 4:
                deleteNode(tree);
                Sleep(2000);
                break;
            case 5:
                cout << endl;
                tree.printTree();
                Sleep(2000);
                break;
            case 6:
                return 0;
            default:
                cerr << "Please enter a valid menu selection!\n\n";
                Sleep(1000);
                break;
        }
    }

    return 1;
}

void traverseTree(BST &tree)
{
    // 1. Tree Traversal
    cout << "\nPre-order tree traversal: "; 
    tree.printPreOrder();
    cout << "In-order tree traversal: "; 
    tree.printInOrder();
    cout << "Post-order tree traversal: "; 
    tree.printPostOrder();
}
void searchNode(BST &tree)
{
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
        cout << key << "'s sub-tree\n";
        tree.printTree(node, nullptr, false);
        /*cout << key << " left node value: ";
        if(node->left == NULL) cout << "NULL\n"; else cout << node->left->val << endl;
        cout << key << " right node value: ";
        if(node->right == NULL) cout << "NULL\n"; else cout << node->right->val << endl;*/
    }
}
void insertNode(BST &tree)
{
    // 3. Insertion
    int key;
    cout << "\nEnter a new value to be added into the binary tree: ";
    cin >> key;
    tree.insert(key);
    cout << "Tree with " << key << " inserted: ";
    tree.printInOrder();
}
void deleteNode(BST &tree)
{
    // 4. Deletion
    int key;
    cout << "\nEnter a value to be deleted from the tree: ";
    cin >> key;
    if(tree.remove(key))
    {
        cout << "Tree with " << key << " removed: ";
        tree.printInOrder();
    }
    else
    {
        cout << key << " was not found in the tree.\n";
    }
}