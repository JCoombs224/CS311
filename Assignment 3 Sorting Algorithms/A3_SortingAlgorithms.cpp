// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
#include <string>
using namespace std;

int arrSize; // global array size variable only used for printing

void swap(int arr[], int q, int i)
{
    int temp = arr[q];
    arr[q] = arr[i];
    arr[i] = temp;
}

// ****************** Sorting Algorithms ******************

/**
 * @brief Selection Sort algorithm.
 *        Time Complexity: O(n^2)
 * 
 * @param arr - array to be sorted
 * @param n - size of the array
 */
void SelectionSort(int arr[], int n)
{   
    for(int i = n-1; i >= 0; i--)
    {
        int max = INT_MIN;
        int swapIndex;
        for(int j = 0; j <= i; j++)
        {
            if(arr[j] > max)
            {
                max = arr[j];
                swapIndex = j;
            }
        }
        swap(arr, swapIndex, i);

        // Print iteration
        cout << "Iteration #" << n-i << ": ";
            for(int j = 0; j < n; j++)
                cout << arr[j] << " ";
            cout << endl;
    }
}

/**
 * @brief Bubble Sort algorithm.
 *        Time Complexity: O(n^2)
 * 
 * @param arr - array to be sorted
 * @param n - size of the array
 */
void BubbleSort(int arr[], int n)
{
    bool didSwap = true;
    int count = 0;

    while(didSwap)
    {
        count++;
        didSwap = false;
        for(int i = 0; i < n-1; i++)
        {
            if(arr[i] > arr[i+1])
            {
                swap(arr, i, i+1);
                didSwap = true;
            }
        }
        if(didSwap)
        {
            cout << "Iteration #" << count << ": ";
            for(int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << endl;
        }
    }
}

/**
 * @brief Insertion Sort algorithm.
 *        Time Complexity: O(n^2)
 * 
 * @param arr - array to be sorted
 * @param n - size of the array
 */
void InsertionSort(int arr[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int j = i - 1;
        int k = i;
        while(j >= 0 && arr[j] > arr[k])
        {
            swap(arr, j, k);
            k--;
            j--;
        }

        cout << "Iteration #" << i << ": ";
        for(int x = 0; x < n; x++)
            cout << arr[x] << " ";
        cout << endl;
    }
}

/**
 * @brief Function used to partition array for the Quick Sort algorithm
 * 
 * @param arr - array that is being sorted
 * @param p - low
 * @param r - high
 * @return int 
 */
int Partition(int arr[], int p, int r)
{
    int pivot = arr[p];
    int i;
    int q = i = p + 1;

    while(i < r)
    {
        if(arr[i] <= pivot)
            swap(arr, q++, i);
        i++;
    }
    swap(arr,p,q-1);

    return q;
}

/**
 * @brief Quick Sort algorithm.
 *        Time Complexity: O(nlog(n))
 * 
 * @param arr - array to be sorted
 * @param p - low index
 * @param r - high index
 */
void QuickSort(int arr[], int p, int r)
{
    if(p >= r)
        return;
    else
    {
        int q = Partition(arr, p, r);
        QuickSort(arr, p, q-1);
        cout << "Swap : ";
        for(int i = 0; i < arrSize; i++) // TODO: make print better
            cout << arr[i] << " ";
        cout << endl;
        QuickSort(arr, q, r);
    }
}

/**
 * @brief Merge function used in the Merge Sort algorithm.
 *        Combines two subarrays into parent array.
 * 
 * @param arr - array being sorted
 * @param p - low index
 * @param q - middle index
 * @param r - high index
 */
void Merge(int arr[], int p, int q, int r)
{
    int bArr[50];
    int i = p, k = p;
    int j = q+1;

    while(i <= q && j <= r)
    {
        if(arr[i] <= arr[j])
        {
            bArr[k++] = arr[i++];
        }
        else
        {
            bArr[k++] = arr[j++];
        }
    }

    while (i <= q)
        bArr[k++] = arr[i++];

    while(j <= r)
        bArr[k++] = arr[j++];
    
    for(int i = p; i <= r; i++)
    {
        arr[i] = bArr[i];
    }
    
    cout << "Merge : ";
    for(int z = 0; z < arrSize; z++)
        cout << arr[z] << " ";
    cout << endl;
}

/**
 * @brief Merge Sort algorithm.
 *        Time Complexity: O(nlog(n))
 * 
 * @param arr - array to be sorted
 * @param p - low index
 * @param r - high index
 */
void MergeSort(int arr[], int p, int r)
{
    if(p == r)
        return;
    
    int q = (p + r)/2;

    MergeSort(arr, p, q);
    MergeSort(arr, q+1, r);
    Merge(arr, p, q, r);
}

/**
 * @brief MaxHeap class rearranges an internal or external array into a Max Heap
 *        data structure. Can be implemented in order to perform a heap sort on an
 *        array of integers.
 */
class MaxHeap
{
    int size, capacity;
    int *arr;
    public:
        MaxHeap(){} // Default constructor

        // Constructor with size
        MaxHeap(int n)
        {
            size = 0;
            capacity = n;
            arr = new int[capacity];
        }

        // Returns the index of the parent for i.
        int parent(int i)
        {
            return (i-1)/2;
        }
        // Returns the index of i's left node.
        int left(int i)
        {
            return 2*i + 1;
        }
        // Returns the index of i's right node.
        int right(int i)
        {
            return 2*i + 2;
        }
        // Returns the size of the heap.
        int getSize()
        {
            return size;
        }
        // Returns whether the node at i is a leaf node or not.
        bool isLeaf(int i)
        {
            return (i >= size/2);
        }
        // Returns the max value of the heap.
        int getMax()
        {
            return arr[0];
        }

        // Takes in an external array and turns it into a MaxHeap structure.
        void heapify(int *array, int n)
        {
            arr = array;
            size = n;
            capacity = n;
            int half = size/2 - 1;
            for(int i = half; i >= 0; i--)
                siftDown(i);
        }

        // Sifts the node at i up until it is smaller than its parent
        void siftUp(int i)
        {
            while(i > 0 && arr[parent(i)] < arr[i])
            {
                swap(arr, i, parent(i));
                i = parent(i);
            }
        }
        // Sifts the node at i down until it is a leaf or larger than both the left
        // and right nodes.
        void siftDown(int i)
        {
            while(!isLeaf(i))
            {
                int l = left(i);
                int r = right(i);
                int larger = l;
                if(r < size)
                    larger = (arr[l] > arr[r]) ? l : r;
                if(arr[i] >= arr[larger])
                    break;
                swap(arr, i, larger);
                i = larger;
            }
        }
        // Inserts a value into the heap
        void insert(int k)
        {
            if(size >= capacity)
                throw Overflow();
            int i = size;
            arr[i] = k;
            siftUp(i);
            size++;
        }
        // Removes the value at i and returns the value
        int removeAt(int i)
        {
            if(i < 0 || size <= i) throw UnderFlow();
            if(size == 1) return arr[--size];

            int result = arr[i];
            arr[i] = arr[--size];
            if(arr[i] < result)
                siftDown(i);
            else
                siftUp(i);
            
            return result;
        }
        // Removes the root of the heap which is the max value and returns it.
        int extractMax()
        {
            if(size <= 0) throw UnderFlow();
            if(size == 1) return arr[--size];

            int res = arr[0];
            arr[0] = arr[--size];
            siftDown(0);

            return res;
        }

        // Heap Exceptions
        class Overflow{};
        class UnderFlow{};
};

/**
 * @brief Heap Sort algorithm.
 *        Time Complexity: O(nlog(n))
 * 
 * @param arr - array to be sorted
 * @param n - size of the array
 */
void HeapSort(int arr[], int n)
{
    MaxHeap heap(n);
    heap.heapify(arr, n);
    int i = n-1;
    int count = 1; // for printing purposes

    while(heap.getSize() > 0)
    {
        arr[i--] = heap.extractMax();

        cout << "Extract Max " << count++ << ": ";
        for(int j = 0; j < arrSize; j++)
            cout << arr[j] << " ";
        cout << endl;
    }
}

// Main Function
int main()
{
    arrSize = 0;
    string input, temp = "";
    int arr[50];

    cout << "Enter up to 50 integers seperated by spaces to be sorted: ";
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

    int selection;

    // Display sorting menu
    cout << "\n\n*** Sorting Algorithm Menu ***\n";
    cout << "1 - Selection Sort\n";
    cout << "2 - Bubble Sort\n";
    cout << "3 - Insertion Sort\n";
    cout << "4 - Quick Sort\n";
    cout << "5 - Merge Sort\n";
    cout << "6 - Heap Sort\n";

    // Get menu selection
    cin >> selection;

    cout << "\nOriginal Array: ";
    for(int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << "\n\n";
    
    switch(selection)
    {
        case 1:
            SelectionSort(arr, arrSize);
            cout << "\nSelection Sorted: ";
            break;
        case 2:
            BubbleSort(arr, arrSize);
            cout << "\nBubble Sorted: ";
            break;
        case 3:
            InsertionSort(arr, arrSize);
            cout << "\nInsertion Sorted: ";
            break;
        case 4:
            QuickSort(arr, 0, arrSize);
            cout << "\nQuick Sorted: ";
            break;
        case 5:
            MergeSort(arr, 0, arrSize-1);
            cout << "\nMerge Sorted: ";
            break;
        case 6:
            HeapSort(arr, arrSize);
            cout << "\nHeap Sorted: ";
            break;
        default:
            cerr << "Please enter a valid selection!";
            return -1;
    }

    for(int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";

    cout << "\n\n";

    //system("pause"); // wait for input before closing console (windows)
    return 0;
}