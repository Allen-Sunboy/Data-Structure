//[first, mid) [mid, last)
void merge(int data[], int first, int mid, int last, int sorted[])
{
    int i = first, j = mid;
    int k = 0;
    while(i < mid && j < last)
        if(data[i] < data[j])
            sorted[k++] = data[i++];
        else
            sorted[k++] = data[j++];
    while(i < mid)
        sorted[k++] = data[i++];
    while(j < last)
        sorted[k++] = data[j++];
    for(int v = 0; v < k; ++v)
        data[first + v] = sorted[v];
}

//[first, last)
void mergeSort(int data[], int first, int last, int sorted[])
{
    if(last - first <= 1)
        return;
    int mid = (first + last) / 2;
    mergeSort(data, first, mid, sorted);
    mergeSort(data, mid, last, sorted);
    merge(data, first, mid, last, sorted);
}

#include <iostream>
using namespace std;

int main()
{
    int a[5] = {3, 2, 6, 5};
    int b[5];
    mergeSort(a, 0, 4, b);

}