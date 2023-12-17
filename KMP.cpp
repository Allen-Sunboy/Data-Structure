#include <cstring> //strlen()

int *buildNext(char *P)
{
    int m = strlen(P), j = 0;
    int *N = new int[m];
    int t = N[0] = -1;
    while (j < m - 1)
        if (t < 0 || P[j] == P[t])
        {
            j++;
            t++;
            N[j] = (P[j] != P[t] ? t : N[t]); //原始next表的这里是N[j] = t
        }
        else
            t = N[t];
    return N;
}

int match(char *P, char *T)
{
    int *next = buildNext(P);
    int n = strlen(T), i = 0;
    int m = strlen(P), j = 0;
    while (j < m && i < n)
        if (j < 0 || T[i] == P[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    delete[] next;
    return i - j;
}

#include <iostream>
using namespace std;

int main()
{
    
}