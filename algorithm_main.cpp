#include<iostream>
#include <cstdlib> // to randomaize the array elements
#include<ctime> // For using time(0)
#include <chrono> // To determine the time searching the element
#include<algorithm>// To swap the array in different positions
using namespace std;
using namespace std::chrono;

//Binary Search
int binarySearch(int arr[],int left,int right, int target){
  int index;
  if (left > right)
      index = -1;
  else{

    int mid = left + (right-left)/2;
    if(arr[mid] == target){
      index = mid;
    }
    else if (arr[mid] < target)
    {
      index = binarySearch(arr , mid+1 , right , target);// Recursively calling the binary algorithm
    }
    else{
      index = binarySearch(arr , left , mid-1 , target);
    }

  }
  return index;
}


//Exponential Search
int exponentialSearch(int arr[],int n , int target){
  if(n == 0){//for not found cases
    return -1;
  }
  else if(arr[0] == target){
    return 0;
  }

  int i = 1;
  //Finding range for binary
  while (i < n && arr[i] < target)
  {
    i *= 2;
  }
  return binarySearch(arr , i/2 , min(i,n-1),target );// calling the binary search

}

//Function for Getting random numbers to insert in n size array
void getRandomNumbers(int arr[],int n){
  srand(time(0));
  for(int i=0;i<n;i++){
      arr[i]=rand()%100;
  }
}


//Displaying the array elements
void displayArray(int arr[],int n){
  for(int i=0;i<n;i++){
      cout<<arr[i]<<" ";
  }
  cout<<endl;
}

//For Quick sort
// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Simple pivot to reduce overhead
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int p = partition(arr, low, high);
    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);
  }
}

//Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int* L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int main(){
  int n, target;
  cout<<"Enter the size of array you want:";
  cin>>n;
  int* arr = new int[n];
  int* arrMerge = new int[n];

  getRandomNumbers(arr, n);

// Clone arr into arrMerge
  for (int i = 0; i < n; i++) {
      arrMerge[i] = arr[i];
  }

  cout<<"Unsorted Array:\n";
  displayArray(arr , n);

  // Start time
  auto quickStart = high_resolution_clock::now();
  //Quick Sort
  quickSort(arr , 0 , n-1);
  // End time
  auto quickStop = high_resolution_clock::now();

  // Duration in microseconds
  auto quickDuration = duration_cast<nanoseconds>(quickStop - quickStart);

  //sorting the array using quick sort
  cout<<"After quick sort:\n";
  displayArray(arr , n);
  cout<<"Time Taken by quick sorting : "<<quickDuration.count()<<" nanoseconds"<<endl;

  //start time
  auto mergeStart = high_resolution_clock::now();
  //Merge Sort
  mergeSort(arrMerge , 0 , n-1);
  //end time
  auto mergeStop = high_resolution_clock::now();

  //duration in ns
  auto mergeDuration = duration_cast<nanoseconds>(mergeStop - mergeStart);


  cout<<"After using merge sort:\n";
  displayArray(arrMerge , n);
  cout<<"Time Taken by merge sorting : "<<mergeDuration.count()<<" nanoseconds"<<endl;
  // Checking which sort is faster
  cout << (quickDuration < mergeDuration ? "Quick Sort was faster\n" : "Merge Sort was faster\n");


  cout << "\nEnter the number to be searched: ";
  cin >> target;

  // Start time
  auto binaryStart = high_resolution_clock::now();
  //Binary Search
  int result = binarySearch(arr , 0 , n-1 , target);

  // End time
  auto binaryStop = high_resolution_clock::now();

  // Duration in microseconds
  auto binaryDuration = duration_cast<nanoseconds>(binaryStop - binaryStart);
  if(result != -1){
    cout<<"The element is found at the index "<<result<<endl;
  }
  else
    cout<<"The element is not found.\n";
  cout<<"Time taken  by binary searching : "<< binaryDuration.count() <<" nanoseconds \n";

  //Exponential Searching.
  // Start time
  auto exponentialStart = high_resolution_clock::now();
  result = exponentialSearch(arrMerge ,n, target);

  // End time
  auto exponentialStop = high_resolution_clock::now();

  // Duration in microseconds
  auto exponentialDuration = duration_cast<nanoseconds>(exponentialStop - exponentialStart);

  if(result != -1){
    cout<<"The element is found at the index "<<result<<endl;
  }
  else
    cout<<"The element is not found.\n";
  cout<<"Time taken  by exponential searching : "<< exponentialDuration.count() <<" nanoseconds \n";
  //Checking which selection algorithm is faster
  cout << (binaryDuration < exponentialDuration ? "Binary Search was faster.\n" : "Exponential Search was faster.\n");
  return 0;
}
