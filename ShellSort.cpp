void ShellSort(int data[], int count)
{
    int step = 0;
    int auxiliary = 0;
    for (step = count / 2; step > 0; step /= 2)
    {
        for (int i = step; i < count; i++)
        {
            if (data[i] < data[i - step])
            {
                auxiliary = data[i];
                int j = i - step;
                while (j >= 0 && data[j] > auxiliary)
                {
                    data[j + step] = data[j];
                    j -= step;
                }
                data[j + step] = auxiliary;
            }
        }
    }
}

#include <iostream>
using namespace std;

int main()
{
    
}