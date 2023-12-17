#include <iostream>

using namespace std;

const int MAXN = 600003;

int a[MAXN];
int n, m;

int output[MAXN];
int p = 0;

void merge(int a[], int l, int mid, int r)
{
    int i = l;
    int j = mid + 1;
    int k = l;
    int *temp = new int[k+1];
    while (i <= mid && j <= r)
    {
        if (a[i] > a[j])
            temp[k++] = a[j++];
        else
            temp[k++] = a[i++];
    }
    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= r)
        temp[k++] = a[j++];
    for (i = l; i <= r; i++)
        a[i] = temp[i];
    delete []temp;
}

void mergeSort(int a[], int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    mergeSort(a, l, mid);
    mergeSort(a, mid+1, r);
    merge(a, l, mid, r);

}

//找第一个大于等于key的值对应的下标，如果没有，则返回n
int binarySearch(int a[], int key)
{
    int l = 0;
    int r = n - 1;
    if (a[r] < key)
        return n;
    if (a[l] > key)
        return 0;
    while (l < r)
    {
        int mid = (l + r) >> 1;

        if (a[mid] < key)
            l = mid + 1;
        else
            r = mid;
    }
        return l;
}


int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    mergeSort(a, 0, n-1);

    int l, r;
    while (m--)
    {
        cin >> l >> r;
        int ln = binarySearch(a, l);
        int rn = binarySearch(a, r);
        if (a[rn] == r)
            cout << rn - ln + 1 << "\n";
        else
            cout << rn - ln << "\n";
    }

}