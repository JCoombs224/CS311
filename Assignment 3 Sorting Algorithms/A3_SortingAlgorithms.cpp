// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
#include <string>
using namespace std;

void swap(int arr[], int q, int i)
{
    int temp = arr[q];
    arr[q] = arr[i];
    arr[i] = temp;
}

// *** MergeSort ***

void MergeSort(int arr[], int n)
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
    }
}

// Bubble Sort
void BubbleSort(int arr[], int n)
{
    bool didSwap = true;

    while(didSwap)
    {
        didSwap = false;
        for(int i = 0; i < n-1; i++)
        {
            if(arr[i] > arr[i+1])
            {
                swap(arr, i, i+1);
                didSwap = true;
            }
        }
    }
}

// Insertion Sort
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
    }
}

// *** QuickSort ***
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

void QuickSort(int arr[], int p, int r)
{
    if(p >= r)
        return;
    else
    {
        int q = Partition(arr, p, r);
        QuickSort(arr, p, q-1);
        QuickSort(arr, q, r);
    }
}

// MergeSort
void Merge(int arr[], int p, int q, int r)
{
    int bArr[7];
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
    
    for(int i = p; i < r; i++)
    {
        arr[i] = bArr[i];
    }

    
    for(int i = 0; i < r; i++)
        cout << bArr[i] << " ";
    cout << endl;
    
}

void MergeSort(int arr[], int p, int r)
{
    if(p == r)
        return;
    
    int q = (p + r)/2;

    MergeSort(arr, p, q);
    MergeSort(arr, q+1, r);
    Merge(arr, p, q, r);
}


int main()
{
    int size = 0;
    string input, temp = "";
    int arr[50];

    cout << "Enter up to 50 integers seperated by spaces to be sorted: ";
    getline(cin, input);

    // Get set of integers from user.
    for(int i = 0; i < input.size(); i++)
    {
        // Break loop if max elements have been added to array.
        if(size > 49)
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
                arr[size++] = stoi(temp);
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
    if(size < 50 && temp != "")
    {
        arr[size++] = stoi(temp);
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
    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";
    
    cout << "\n\nArray Sorted With ";
    switch(selection)
    {
        case 1:
            //SelectionSort(arr, size);
            cout << "Selection Sort: ";
            break;
        case 2:
            BubbleSort(arr, size);
            cout << "Bubble Sort: ";
            break;
        case 3:
            InsertionSort(arr, size);
            cout << "Insertion Sort: ";
            break;
        case 4:
            QuickSort(arr, 0, size);
            cout << "Quick Sort: ";
            break;
        case 5:
            MergeSort(arr, size);
            cout << "Merge Sort: ";
            break;
        case 6:
            //HeapSort(arr, size);
            cout << "Heap Sort: ";
            break;
        default:
            cerr << "Please enter a valid selection!";
            break;
    }

    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";

    cout << "\n\n";

    system("pause"); // wait for input before closing console (windows)
    return 0;
}