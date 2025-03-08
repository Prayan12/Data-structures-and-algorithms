#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate N random numbers within a given range
vector<int> generateRandomNumbers(int N, int minVal = 1, int maxVal = 100) {
    vector<int> numbers(N);
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
    return numbers;
}

// Selection Sort Algorithm
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Merge function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }
    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

// Merge Sort Algorithm
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to measure sorting time
void measureSortingTime(vector<int>& numbers, void (*sortFunction)(vector<int>&), const string& sortName) {
    vector<int> tempNumbers = numbers;
    auto start = high_resolution_clock::now();
    sortFunction(tempNumbers);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();
    cout << sortName << " Time: " << duration << " ns" << endl;
}

// Overloaded function for Merge Sort
void measureMergeSortTime(vector<int>& numbers) {
    vector<int> tempNumbers = numbers;
    auto start = high_resolution_clock::now();
    mergeSort(tempNumbers, 0, tempNumbers.size() - 1);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();
    cout << "Merge Sort Time: " << duration << " ns" << endl;
}

int main() {
    srand(time(0)); // Seed for random number generation
    int N, choice;

    cout << "Enter the number of elements to sort: ";
    cin >> N;
    vector<int> numbers = generateRandomNumbers(N);

    cout << "\nChoose Sorting Algorithm to Analyze:\n";
    cout << "1. Selection Sort\n";
    cout << "2. Merge Sort\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        measureSortingTime(numbers, selectionSort, "Selection Sort");
    } else if (choice == 2) {
        measureMergeSortTime(numbers);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
