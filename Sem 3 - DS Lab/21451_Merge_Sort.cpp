# include <iostream>
using namespace std;


void merge(int arr[], int low, int mid, int high)
{
    int n = mid - low + 1;     //size of left array
    int m = high - mid;        //size of right array

    int * leftArr = new int[n];
    int * rightArr = new int[m];

    for (int l=0; l<n; l++){
        leftArr[l] = arr[low + l];
    }

    for (int r=0; r<m; r++){    
        rightArr[r] = arr[mid + 1 + r];
    }

    int l = 0, r = 0, i = low;
    while (l < n && r < m){
        if (leftArr[l] <= rightArr[r]){
            arr[i] = leftArr[l];
            l++; 
        }
        else {
            arr[i] = rightArr[r];
            r++;
        }
        i++;
    }

    // if left array not exhausted
    while(l < n){
        arr[i] = leftArr[l];
        l++; 
        i++;
    }

    // if right array not exhausted
    while(r < m){
        arr[i] = rightArr[r];
        r++; 
        i++;
    }

    delete[] leftArr;
    delete[] rightArr;
}


void mergeSort(int arr[], int low, int high)
{
    if (low >= high){
        return;
    }
    else
    {
        int mid = (high + low)/2;
        // Sort left part
        mergeSort(arr, low, mid);
        // Sort right part
        mergeSort(arr, mid + 1, high);
        // merge two parts
        merge(arr, low, mid, high);
    }
}


// driver code
int main()
{
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int * arr = new int[n];
    cout << "Enter array elements: "<< endl;
    for (int i=0; i<n; i++){
        cin >> arr[i];
    }

    // Before Sorting
    cout << "Before Sorting:" << endl;
    for (int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    mergeSort(arr, 0, n-1);

    // After Sorting
    cout << "\nAfter Sorting:" << endl;
    for (int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}