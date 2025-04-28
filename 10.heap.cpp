#include<iostream>
using namespace std;

void maxHeapify(int heap[], int i, int n) {

    int left = 2 * i;
    int right = (2 * i) + 1;
    int largest = i;

    if (left <= n && heap[i] < heap[left])
        largest = left;

    if (right <= n && heap[largest] < heap[right])
        largest = right;

    if (largest != i) {
        swap(heap[largest], heap[i]);
        maxHeapify(heap, largest, n);
    }
}

void buildHeap(int heap[], int n) {

    for (int i = n / 2; i >= 1; i--)
        maxHeapify(heap, i, n);
}

int main() {
    int n;
    cout << "Enter Number of Students : ";
    cin >> n;

    int heap[n + 1];

    cout << "Enter Marks : \n";
    for (int i = 1; i <= n; i++)
        cin >> heap[i];

    buildHeap(heap, n);

    int heapSize = n;
    
    for (int i = n; i >= 2; i--) {
        swap(heap[1], heap[i]);
        --heapSize;
        maxHeapify(heap, 1, heapSize);
    }

    cout << "\nAfter Sorting :: ";
    for (int i = 1; i <= n; i++)
        cout << heap[i] << " ";
    cout << "\nMAXIMUM MARKS :" << heap[n] << endl;
    cout << "MINIMUM MARKS :" << heap[1] << endl;
    return 0;
}
