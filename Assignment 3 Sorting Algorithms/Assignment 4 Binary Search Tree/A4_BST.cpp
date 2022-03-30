#include <iostream>
#include <iomanip>
using namespace std;

struct Node
{
    int val;
    Node left;
    Node right;
    Node(int data)
    {
        val = data;
        left = NULL;
        right = NULL;
    }
};

class BST
{
    private:
        Node *root;
    public:
        BST()
        {
            root = NULL;
        }

        void insert(int val)
        {
            root = insert(root, val);
        }
        Node* insert(Node *node, int val)
        {
            if(node == NULL)
                node = new Node(val);
            else if(node->val > val)
                insert(node->left, val);
            else if(node->val < val)
                insert(node->right, val);

            return node;
        }
        Node* search(int key)
        {
            return search(root, key);
        }
        Node* search(Node *node, int key)
        {
            if(root == NULL || node->val == key)
                return node;
            else if(node->val > key)
                return search(node->left, key);
            return search(node->right, key);
        }
        void remove(int key)
        {
            root = remove(root, key);
        }
        Node* remove(Node *node, int key)
        {
            if(node == NULL)
                return node;
            if(node->key > key)
            {
                node->left = remove(node->left, key);
            }
            else if(node->key < key)
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
};

int main()
{

}
