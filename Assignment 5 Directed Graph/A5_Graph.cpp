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
    LinkedList<int> *adj;
    
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
        void addEdge(int v, int w)
        {
            adj[v].push_back(w);
        }
        void BFS(int s)
        {
            bool *visited = new bool[V];
            for(int i = 0; i < V; i++)
                visited[i] = false;
            Queue queue;
            queue.push_back(s);
            
            while(!queue.empty())
            {
                s = queue.popFront();
                Node<int> *temp = adj[s].head;
                while(temp != NULL)
                {
                    int vertex = temp->val;
                    if(!visited[vertex])
                    {
                        cout << s << ' ';
                        visited[vertex] = true;
                        queue.push_back(vertex);
                    }
                    temp = temp->next;
                }
            }
        }
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
                for(int i=0; i < V; i++)
                    visited[i] = false;
                
                if(cycleUtil(i, visited))
                    return true;
            }
            return false;
        }
};

bool addEdge(Graph&, int);

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

    // Create new graph with desired number of vertices
    Graph graph(n);

    bool done = false;
    cout << "\n***** ADD EDGES ****\n";
    cout << "To add an edge enter the starting vertex then the ending vertex.\n\n";

    // Add edges to thr graph
    while(!done)
    {
        // Add edge and check for success - if not retry
        if(!addEdge(graph, n))
            continue;
        char sel;

        // Ask if user would like to continue adding edges
        while(true)
        {
            cout << "\nWould you like to add another edge? (y/n): ";
            cin >> sel;
            if(sel == 'y')
                break;
            if(sel == 'n')
            {
                done = true;
                break;
            }
            else
            {
                cerr << "Error: Please enter either 'y' or 'n'.\n\n";
            }
        }
    }

    int selection;
    while(true)
    {
        cout << "\n********** Graph Menu **********\n";
        cout << "1. Add Edge\n";
        cout << "2. BFS traversal\n";
        cout << "3. DFS traversal\n";
        cout << "4. Check for cycle\n";
        cout << "5. Quit\n";

        cout << "\nEnter Selection: ";
        cin >> selection;

        int v; // vertex selection for traversal

        switch (selection)
        {
        case 1:
            // Add edge and check for success - if not retry
            if(!addEdge(graph, n))
                continue;
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
            return 0;
        
        default:
            cerr << "Please enter a valid selection!\n\n";
            break;
        }
    }


    return 0;
}

bool addEdge(Graph &graph, int n)
{
    int v, w;
    cout << "Starting vertex: ";
    cin >> v;
    if(v >= n) // Check for valid vertex entered
    {
        cerr << "\nError: Starting vertex does not exist, vertex must be < " << n << "\n\n";
        return false;
    }

    cout << "Ending vertex: ";
    cin >> w;
    if(w >= n) // Check for valid vertex entered
    {
        cerr << "\nError: Ending vertex does not exist, vertex must be < " << n << "\n\n";
        return false;
    }

    graph.addEdge(v, w); // add current edge to the graph
    return true;
}