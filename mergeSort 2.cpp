//[l, r]
void mergeSort(int a[], int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    int *an = new int[r + 1];
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (a[i] < a[j])
            an[k++] = a[i++];
        else
            an[k++] = a[j++];
    }
    while (i <= mid)
        an[k++] = a[i++];
    while (j <= r)
        an[k++] = a[j++];
    for (i = l; i <= r; ++i)
        a[i] = an[i];
    delete[] an;
}

#include <iostream>
using namespace std;

int main()
{

}