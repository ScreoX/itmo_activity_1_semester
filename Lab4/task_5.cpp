#include <iostream>
using namespace std;


void heapify(int arr[], int size, int i) {
    int left_parent = 2 * i + 1;
    int right_parent = 2 * i + 2;

    int largest_element = i;

    if (left_parent < size && arr[left_parent] > arr[largest_element])
        largest_element = left_parent;

    if (right_parent < size && arr[right_parent] > arr[largest_element])
        largest_element = right_parent;

    if (largest_element != i) {
        swap(arr[largest_element], arr[i]);

        heapify(arr, size, largest_element);
    }
}

void Build_Heap(int a[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(a, size, i);
    }
}
void heapSort(int arr[], int size) {

    Build_Heap(arr, size);

    for (int i = size - 1; i >= 1; i--) {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}


int main() {
    int n; cin >> n;
    int mas[n];
    for (int i = 0; i < n; i++) {
        cin >> mas[i];
    }

    heapSort(mas, n);

    for (int i = 0; i < n; ++i)
        cout << mas[i] << " ";
}
