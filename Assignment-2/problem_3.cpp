#include <iostream>
using namespace std;

const int MAXN = 10113;
char str[MAXN];

int sumA, sumB, sumC;
int n;

int main()
{
    cin >> n;
    cin >> str;
    for(int i = 0; i < n; i++)
    {
        switch(str[i])
        {
            case 'A': sumA++; break;
            case 'B': sumB++; break;
            case 'C': sumC++; break;
        }
    }

    if(sumA > sumB)
    {
        int k = sumA - sumB;
        if(sumC < k)
        {
            cout << "False";
            return 0;
        }
        else
        {
            int p = n-1;
            while(k > 0)
            {
                while(str[p] != 'C')
                {
                    p--;
                }
                str[p] = 'B';
                k--;
                sumC--;
            }
        }
    }

    if(sumA < sumB)
    {
        int k = sumB - sumA;
        if(sumC < k)
        {
            cout << "False";
            return 0;
        }
        else
        {
            int p = 0;
            while(k > 0)
            {
                while(str[p] != 'C')
                {
                    p++;
                }
                str[p] = 'A';
                k--;
                sumC--;
            }
        }
    }

    int half = sumC / 2;
    int p1 = 0;
    for(int i = 0; i < half; i++)
    {
        while(str[p1] != 'C')
        {
            p1++;
        }
        str[p1] = 'A';
    }
    
    int p2 = n - 1;
    for(int i = 0; i < half; i++)
    {
        while(str[p2] != 'C')
        {
            p2--;
        }
        str[p2] = 'B';
    }

    if(sumC % 2)
    {
        while(str[p1] != 'C')
            p1++;
        for(int i = p1; i < n-1; i++)
        {
            str[i] = str[i+1];
        }
        n--;
    }


    int sumANew = 0;
    int sumBNew = 0;
    for(int i = 0; i < n; i++)
    {
        if(str[i] == 'A')
            sumANew++;
        if(str[i] == 'B')
            sumBNew++;
        if(sumBNew > sumANew)
        {
            cout << "False";
            return 0;
        }
    }
    cout << "True";


}