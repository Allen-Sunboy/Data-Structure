#include <iostream>
using namespace std;

int  main()
{
    long a, b;
    char c;
    cin >> a >> c >> b;
    if (c == '+')
        cout <<  a + b << endl;
    if (c == '-')
        cout << a - b << endl;
    if (c == '*')
        cout << a * b << endl;
}
