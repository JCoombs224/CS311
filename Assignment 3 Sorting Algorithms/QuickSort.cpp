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

int main()
{
    int arr[] = {555, 1, 46, 92, 4, 98, 3};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "A unsorted: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl << "A sorted with QuickSort: ";

    QuickSort(arr, 0, n);

    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}