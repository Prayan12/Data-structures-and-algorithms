#include <iostream>
#include <algorithm> // For sort()
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

using namespace std;

// Function for binary search
int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // Element not found
}

// Function for interpolation search
int interpolationSearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }
        int pos = low + ((high - low) / (arr[high] - arr[low])) * (target - arr[low]);
        if (arr[pos] == target)
            return pos;
        if (arr[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1; // Element not found
}

int main() {
    srand(time(0)); // Seed for random number generation

    int N, target;
    cout << "Enter number of elements (N): ";
    cin >> N;

    int arr[N]; // Declare array of size N

    // Generate N random numbers and fill the array
    cout << "Generated Random Numbers: ";
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100; // Random numbers between 0 and 99
        cout << arr[i] << " ";
    }
    cout << endl;

    // Sort the array before searching
    sort(arr, arr + N);

    cout << "Sorted Array: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Take user input for target
    cout << "Enter element to search: ";
    cin >> target;

    // Perform binary search
    int binaryResult = binarySearch(arr, N, target);
    if (binaryResult != -1)
        cout << "Binary Search: Element found at index " << binaryResult << endl;
    else
        cout << "Binary Search: Element not found" << endl;

    // Perform interpolation search
    int interpolationResult = interpolationSearch(arr, N, target);
    if (interpolationResult != -1)
        cout << "Interpolation Search: Element found at index " << interpolationResult << endl;
    else
        cout << "Interpolation Search: Element not found" << endl;

    return 0;
}