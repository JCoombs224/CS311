// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>
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
    int arr[] = {555, 1, 46, 92, 4, 98, 3};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "A unsorted: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    //cout << endl << "A sorted with QuickSort: ";
    //QuickSort(arr, 0, n);
    
    //cout << endl << "A sorted with MergeSort: ";
    //MergeSort(arr, n);

    //cout << endl << "A sorted with BubbleSort: ";
    //BubbleSort(arr, n);

    //cout << endl << "A sorted with InsertionSort: ";
    //InsertionSort(arr, n);

    cout << endl << "A sorted with MergeSort: ";
    MergeSort(arr, 0, n);

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}