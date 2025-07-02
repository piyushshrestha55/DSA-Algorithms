#include<iostream>
#include <cstdlib> // to randomaize the array elements
#include<algorithm>//  to sort the array in ascending order
using namespace std;
// Binary Search Function
int binarySearch(int arr[],int left ,int right , int x){
  while (left <= right)
  {
    int mid =  left + (right - left)/2;
    if(arr[mid] == x)
      return mid;
    else if(arr[mid] < x)
      left =mid + 1;
    else
      right=mid-1;
  }
  return -1; // for not found

}
//Exponential Search Function
int exponentialSearch(int arr[], int n, int x) {
    if (n == 0)
        return -1;
    if (arr[0] == x)
        return 0;

    int i = 1;
    while (i < n && arr[i] < x) {
        i *= 2;
    }

    return binarySearch(arr, i / 2, min(i, n - 1), x);
}
void insertRandom(int arr[],int n){
  for (int i = 0; i < n; i++)
  {
    arr[i] = rand() % 100;
  }

}
void displayArray(int arr[] , int size){
  for (int i = 0; i < size; i++)
  {
    cout<<arr[i]<<" ";
  }

}
int main(){
  int n , x;
  cout<<"Enter the size of the array you want:";
  cin>>n;
  int arr[n];
  insertRandom(arr , n);

  sort(arr , arr + n);
  displayArray(arr , n);
  cout<<"Enter the element you want to search:";
  cin>>x;
  int result = exponentialSearch(arr , n , x);
  if(result != -1)
    cout<<"The element is located at index "<<result<<endl;
  else
    cout<<"There is no such element present.\n";


}
