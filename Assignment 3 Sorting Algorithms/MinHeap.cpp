void swap(int arr[], int q, int i)
{
    int temp = arr[q];
    arr[q] = arr[i];
    arr[i] = temp;
}

class MinHeap
{
    int size, capacity;
    int *arr;
    public:
        MinHeap(){}
        MinHeap(int n)
        {
            size = 0;
            capacity = n;
            arr = new int[capacity];
        }

        int parent(int i)
        {
            return (i-1)/2;
        }
        int left(int i)
        {
            return 2*i + 1;
        }
        int right(int i)
        {
            return 2*i + 2;
        }
        int getSize()
        {
            return size;
        }
        bool isLeaf(int i)
        {
            return (i >= size/2);
        }
        int getMin()
        {
            return arr[0];
        }

        void heapify(int *array, int n)
        {
            arr = array;
            size = n;
            capacity = n;
            int half = n/2 - 1;
            for(int i = half; i >= 0; i--)
                siftDown(i);
        }

        void siftUp(int i)
        {
            while(i > 0 && arr[parent(i)] > arr[i])
            {
                swap(arr, i, parent(i));
                i = parent(i);
            }
        }
        void siftDown(int i)
        {
            while(!isLeaf(i))
            {
                int l = left(i);
                int r = right(i);
                int smaller = l;
                if(r < size)
                    smaller = (arr[l] < arr[r]) ? l : r;
                if(arr[i] <= arr[smaller])
                    break;
                swap(arr, i, smaller);
                i = smaller;
            }
        }
        void insert(int k)
        {
            if(size >= capacity)
                throw Overflow();
            int i = size;
            arr[i] = k;
            siftUp(i);
            size++;
        }
        int removeAt(int i)
        {
            if(i < 0 || size <= i) throw UnderFlow();
            if(size == 1) return arr[--size];

            int result = arr[i];
            arr[i] = arr[--size];
            if(arr[i] > result)
                siftDown(i);
            else
                siftUp(i);
            
            return result;
        }
        int extractMin()
        {
            if(size <= 0) throw UnderFlow();
            if(size == 1) return arr[--size];

            int res = arr[0];
            arr[0] = arr[--size];
            siftDown(0);

            return res;
        }


        class Overflow{};
        class UnderFlow{};
};
