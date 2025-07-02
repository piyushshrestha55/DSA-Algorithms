#include<iostream>
#include <cstdlib>
#include<algorithm>
using namespace std;
int binarySearch(int arr[], int size , int target){
  int left = 0, right = size-1;
  while(left <= right){
    int mid = left + ( right - left )/2;
    if (arr[mid] == target)
    {
      return mid;
    }
    else if(arr[mid] < target){
      left = mid+1;
    }
    else{
      right = mid - 1;

    }
  }
  return -1;
}
void insertRandom(int arr[] , int size){
  for ( int i = 0; i < size; i++)
    {
     arr[i] = rand() % 100; // Numbers between 0–99; // Numbers between 0–99
    }

}
void displayArray(int arr[] , int size){
  for (int i = 0; i < size; i++)
  {
    cout<<arr[i]<<" ";
  }

}

int main(){
  int x , target;
  cout<<"Enter the size of the array you want:";
  cin>>x;
  int arr[x];
  insertRandom(arr , x);
  cout<<"\nUnsorted Array:\n";
  displayArray(arr , x);
  sort(arr, arr + x);
  cout<<"\nSorted Array:\n";
  displayArray(arr , x);

  cout << "\nEnter the number to search: ";
  cin >> target;
  cout<<endl;

  int result = binarySearch(arr , x , target);
  if(result != -1){
    cout<<"The element is found at index "<<result<<endl;
  }
  else{
    cout<<"The element is not found"<<endl;

  }


}
