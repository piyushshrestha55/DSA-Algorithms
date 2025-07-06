#include<iostream>
#include <cstdlib> // to randomaize the array elements
#include <chrono> // To determine the time searching the element
#include<utility>
using namespace std;
using namespace std::chrono;

//Binary Search
int binarySearch(int arr[],int left,int right, int target){
  while (left <= right)
  {
    int mid = left + (right-left)/2;
    if(arr[mid] == target)
      return mid;
    else if (arr[mid] < target)
    {
      left = mid + 1;
    }
    else{
      right = mid-1;
    }

  }
  return -1; //for not found cases
}

//Exponential Search
int exponentialSearch(int arr[],int n , int target){
  if(n == 0)
    return -1;//for not found cases
  else if(arr[0] == target)
    return 0;
  int i = 1;
  while (i < n && arr[i] < target)
  {
    i *= 2;
  }
  return binarySearch(arr , i/2 , min(i,n-1) , target);
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
int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) { // NOT j <= high
    if (arr[j] < pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  swap(arr[i + 1], arr[high]); // Place pivot in the correct position
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
void merge(int arr[], int left, int mid, int right){
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];

  for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
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

  //Getting array od random number
  getRandomNumbers(arr,n);

  //Making another array with the same elemebts as the other
  for (int i = 0; i < n; i++)
  {
    arrMerge[i] =arr[i];
  }

  cout<<"Unsorted Array:\n";
  displayArray(arr , n);

  // Start time
  auto quickStart = high_resolution_clock::now();

  quickSort(arr , 0 , n-1);
  // End time
  auto quickStop = high_resolution_clock::now();

  // Duration in microseconds
  auto quickDuration = duration_cast<microseconds>(quickStop - quickStart);

  //sorting the array using quick sort
  cout<<"After quick sort:\n";
  displayArray(arr , n);
  cout<<"Time Taken by quick sorting : "<<quickDuration.count()<<" microseconds"<<endl;

  //start time
  auto mergeStart = high_resolution_clock::now();
  mergeSort(arrMerge , 0 , n-1);
  //end time
  auto mergeStop = high_resolution_clock::now();

  //duration in ms
  auto mergeDuration = duration_cast<microseconds>(mergeStop - mergeStart);


  cout<<"After using merge sort:\n";
  displayArray(arrMerge , n);
  cout<<"Time Taken by merge sorting : "<<mergeDuration.count()<<" microseconds"<<endl;
  // Checking which sort is faster
  cout << (quickDuration < mergeDuration ? "Quick Sort was faster\n" : "Merge Sort was faster\n");

  cout << "\nEnter the number to be searched: ";
  cin >> target;
  cout<<endl;
  // Start time
  auto binaryStart = high_resolution_clock::now();
  //Binary Search
  int result = binarySearch(arr , 0 , n-1 , target);

  // End time
  auto binaryStop = high_resolution_clock::now();

  // Duration in microseconds
  auto binaryDuration = duration_cast<microseconds>(binaryStop - binaryStart);

  if(result != -1){
    cout<<"The element is found at index "<<result<<endl;
  }
  else{
    cout<<"The element is not found"<<endl;

  }
  cout<<"Time taken  by binary searching : "<< binaryDuration.count() <<" microseconds \n";

  //Exponential Searching.
  // Start time
  auto exponentialStart = high_resolution_clock::now();
  result = exponentialSearch(arrMerge ,n, target);

  // End time
  auto exponentialStop = high_resolution_clock::now();

  // Duration in microseconds
  auto exponentialDuration = duration_cast<microseconds>(exponentialStop - exponentialStart);

  if(result != -1){
    cout<<"The element is found at index "<<result<<endl;
  }
  else{
    cout<<"The element is not found"<<endl;

  }
  cout<<"Time taken  by exponential searching : "<< exponentialDuration.count() <<" microseconds \n";
  //Checking which selection algorithm is faster
  cout << (binaryDuration < exponentialDuration ? "Binary Search was faster.\n" : "Exponential Search was faster.\n");
  return 0;
}
