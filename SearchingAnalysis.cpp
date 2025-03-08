#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MAX_N = 1000000;
const int NUM_SEARCHES = 1000; // Number of searches to repeat

void generateSortedArray(int arr[], int N) {
    arr[0] = rand() % 10;
    for (int i = 1; i < N; i++)
        arr[i] = arr[i - 1] + (rand() % 10 + 1);
}

int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int interpolationSearch(int arr[], int left, int right, int target) {
    while (left <= right && target >= arr[left] && target <= arr[right]) {
        if (left == right) {
            if (arr[left] == target) return left;
            return -1;
        }

        int pos = left + (((target) - arr[left]) * (right - left)) / (arr[right] - arr[left]);
        if (pos < left || pos > right) {
            return -1;
        }

        if (arr[pos] == target)
            return pos;
        else if (arr[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }
    return -1;
}

void testSearchAlgorithms(int N) {
    int* arr = new int[N];
    generateSortedArray(arr, N);
    int target = arr[rand() % N];

    // Measure Binary Search time (repeated searches)
    auto binaryStart = high_resolution_clock::now();
    for (int i = 0; i < NUM_SEARCHES; i++) {
        binarySearch(arr, 0, N - 1, target);
    }
    auto binaryEnd = high_resolution_clock::now();
    auto binaryDuration = duration_cast<nanoseconds>(binaryEnd - binaryStart);

    // Measure Interpolation Search time (repeated searches)
    auto interpolationStart = high_resolution_clock::now();
    for (int i = 0; i < NUM_SEARCHES; i++) {
        interpolationSearch(arr, 0, N - 1, target);
    }
    auto interpolationEnd = high_resolution_clock::now();
    auto interpolationDuration = duration_cast<nanoseconds>(interpolationEnd - interpolationStart);

    cout << "N = " << N
         << " | Binary Search: " << binaryDuration.count() / NUM_SEARCHES << " ns"
         << " | Interpolation Search: " << interpolationDuration.count() / NUM_SEARCHES << " ns" << endl;

    delete[] arr;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // initialize the random number generator

    int sizes[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    cout << "Performance Comparison:" << endl;
    for (int N : sizes)
        testSearchAlgorithms(N);

    return 0;
}