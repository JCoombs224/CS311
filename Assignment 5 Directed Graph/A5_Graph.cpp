// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Node object that cotains an element and a pointer to the next
 *        Node.
 * 
 * @tparam T - Type of variable stored in the Node.
 */
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
 * 
 * @tparam T - Type of variable stored in the LinkedList
 */
template<class T>
class LinkedList
{
    public:
        Node<T> *head;
        Node<T> *tail;
        int size;
        LinkedList()
        {
            head = NULL;
            tail = NULL;
            size = 0;
        }
        LinkedList(Node<T> *node)
        {
            head = node;
            tail = node;
            size = 1;
        }

        // **** FUNCTIONS ****
        // Append a new node to end of the list
        void push_back(T val)
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
        void push_front(T val)
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
 * @brief The Queue class is a singly LinkedList with queue functionality.
 *        (First in first out functionality)
 */
class Queue
{
    LinkedList<int> *list = new LinkedList<int>();
    
    public:
        void push_back(int num)
        {
            list->push_back(num);
        }
        int popFront()
        {
            if(this->empty())
                return -1;

            int res = list->head->val;
            
            list->head = list->head->next;
            list->size--;
            return res;
        }
        bool empty()
        {
            return (list->head == NULL);
        }
    
};

class Graph
{
    int V; // num of vertices
    LinkedList<int> *adj; // Array of adjacency lists.
    
    /**
     * @brief Recursive helper function for DFS traversal.
     * 
     * @param v - starting vertex
     * @param visited - array of vertices that have already been visited.
     */
    void DFSUtil(int v, bool visited[])
    {
        visited[v] = true;
        cout << v << ' ';

        Node<int> *temp = adj[v].head;
        while(temp != NULL)
        {
            int vertex = temp->val;
            if(!visited[vertex])
                DFSUtil(vertex, visited);
            temp = temp->next;
        }
    }
    /**
     * @brief Recursive helper function to determine if the graph has a cycle or not.
     * 
     * @param v - starting node for DFS
     * @param visited - array of visited vertices
     * @return true - cycle is detected in the graph
     * @return false - no cycle is detected in the graph.
     */
    bool cycleUtil(int v, bool visited[])
    {
        visited[v] = true;

        Node<int> *temp = adj[v].head;
        while(temp != NULL)
        {
            int vertex = temp->val;
            if(visited[vertex])
                return true;
            else
                return cycleUtil(vertex, visited);
            temp = temp->next;
        }
        return false;
    }

    public:
        // constructor
        Graph(int v)
        {
            V = v;
            adj = new LinkedList<int>[V];
        }
        /**
         * @brief Adds a directed edge to the graph.
         * 
         * @param v - starting node
         * @param w - ending node
         */
        void addEdge(int v, int w)
        {
            adj[v].push_back(w);
        }
        /**
         * @brief Performs a Breadth-First Search from a given starting node.
         * 
         * @param s - starting node for BFS
         */
        void BFS(int s)
        {
            bool *visited = new bool[V];
            for(int i = 0; i < V; i++)
                visited[i] = false;
            Queue queue;
            visited[s] = true;
            queue.push_back(s);
            
            while(!queue.empty())
            {
                s = queue.popFront();
                cout << s << ' ';
                Node<int> *temp = adj[s].head;
                while(temp != NULL)
                {
                    int vertex = temp->val;
                    if(!visited[vertex])
                    {
                        visited[vertex] = true;
                        queue.push_back(vertex);
                    }
                    temp = temp->next;
                }
            }
        }
        /**
         * @brief Performs a Depth-First Search from a given starting node.
         * 
         * @param v - starting node for DFS
         */
        void DFS(int v)
        {
            bool *visited = new bool[V];
            for(int i=0; i < V; i++)
                visited[i] = false;
            
            DFSUtil(v, visited);
        }
        /**
         * @brief Uses DFS to check for a cycle in the graph
         * 
         * @return true - cycle found
         * @return false - no cycle found
         */
        bool hasCycle()
        {
            bool *visited = new bool[V];

            for(int i = 0; i < V; i++)
            {
                for(int j=0; j < V; j++)
                    visited[j] = false;
                visited[i] = true;
                
                if(adj[i].head != NULL)
                    if(cycleUtil(i, visited))
                        return true;
            }
            return false;
        }
        /**
         * @brief Prints the adjacency lists for each vertex.
         */
        void printAdjacencyList()
        {
            Node<int> *temp;
            for(int i = 0; i < V; i++)
            {
                temp = adj[i].head;
                cout << i << ' ';
                while(temp != NULL)
                {
                    cout << temp->val << ' ';
                    temp = temp->next;
                }
                cout << endl;
            }
        }
};

int addEdge(Graph&, int); // main program helper function

// main program
int main()
{
    int n;
    cout << "Enter number of vertices in the graph: ";
    cin >> n;

    if(n < 1) // check for valid number of vertices entered
    {
        cerr << "\nNumber of vertices must be greater than 0!\n";
        return -1;
    }
    cout << "Vertices range from 0-" << n-1 << endl;

    // Create new graph with desired number of vertices
    Graph graph(n);

    cout << "\n***** ADD EDGES ****\n";
    cout << "Enter starting vertex and ending vertex seperated by a single space (enter -1 in either to stop adding edges)\n\n";
    // Loop adding edges to the graph until user quits when returnType == 1
    while(true)
    {
        // Get the result from the addEdge function
        int returnType = addEdge(graph, n);
        
        if(returnType == -1) // Error adding edge loop again
            continue;
        if(returnType == 1) // User quit adding new edges
        {
            break;
        }
    }

    int selection;
    while(true)
    {
        cout << "\n********** Graph Menu **********\n";
        cout << "1. Add Edges\n";
        cout << "2. BFS traversal\n";
        cout << "3. DFS traversal\n";
        cout << "4. Check for cycle\n";
        cout << "5. Print adjaceny list\n";
        cout << "6. Quit\n";

        cout << "\nEnter Selection: ";
        cin >> selection;

        int v; // vertex selection for traversal

        switch (selection)
        {
        case 1:
            cout << "\n***** ADD EDGES ****\n";
            cout << "Enter starting vertex and ending vertex seperated by a single space (enter -1 in either to stop adding edges)\n\n";
            // Loop adding edges to the graph until user quits when returnType == 1
            while(true)
            {
                // Get the result from the addEdge function
                int returnType = addEdge(graph, n);
                
                if(returnType == -1) // Error adding edge loop again
                    continue;
                if(returnType == 1) // User quit adding new edges
                {
                    break;
                }
            }
            break;
        case 2:
            cout << "Please enter starting vertex for BFS traversal: ";
            cin >> v;
            if(v >= n) // Check for valid vertex entered
            {
                cerr << "\nError: Starting vertex does not exist, vertex must be < " << n << "\n\n";
                continue;
            }
            graph.BFS(v);
            break;
        case 3:
            cout << "Please enter starting vertex for DFS traversal: ";
            cin >> v;
            if(v >= n) // Check for valid vertex entered
            {
                cerr << "\nError: Starting vertex does not exist, vertex must be < " << n << "\n\n";
                continue;
            }
            graph.DFS(v);
            break;
        case 4:
            if(graph.hasCycle())
                cout << "Cycle has been detected in the graph.\n";
            else
                cout << "No cycle detected in the graph.\n";
            break;
        case 5:
            graph.printAdjacencyList();
            break;
        case 6:
            return 0;
        
        default:
            cerr << "Please enter a valid selection!\n\n";
            break;
        }
    }


    return 0;
}

// main program helper function to add edge to a graph object.
int addEdge(Graph &graph, int n)
{
    int v, w;
    cout << "New Edge: ";
    
    cin >> v >> w;
    if(v == -1 || w == -1)
        return 1;
    if(v < -1 || v >= n) // Check for valid vertex entered
    {
        cerr << "\nError: Starting vertex does not exist, vertex must be < " << n << "\n\n";
        return -1;
    }
    if(w < -1 || w >= n) // Check for valid vertex entered
    {
        cerr << "\nError: Ending vertex does not exist, vertex must be < " << n << "\n\n";
        return -1;
    }

    graph.addEdge(v, w); // add current edge to the graph
    return 0;
}