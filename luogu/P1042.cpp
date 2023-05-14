#include <iostream>

using namespace std;

int main()
{
    char c[65000];
    int num1 = 0, num2 = 0;
    int i;
    int j = 0;
    for (i = 0;; i++)
    {
        cin >> c[i];
        if (c[i] == 'E')
        {
            break;
        }
    }
    int num = i;
    for (i = 0; i < num; i++)
    {
        if (c[i] == 'W')
        {
            num1++;
        }
        else
        {
            num2++;
        }
        if ((num1 >= 11 || num2 >= 11) && (num1 - num2 <= -2 || num1 - num2 >= 2))
        {
            j++;
            cout << num1 << ':' << num2 << endl;
            num1 = num2 = 0;
        }
    }
    cout << num1 << ':' << num2 << endl;
    cout << endl;
    num1 = num2 = 0;
    for (i = 0; i < num; i++)
    {
        if (c[i] == 'W')
        {
            num1++;
        }
        else
        {
            num2++;
        }

        if ((num1 >= 21 || num2 >= 21) && (num1 - num2 <= -2 || num1 - num2 >= 2))
        {
            j++;
            cout << num1 << ':' << num2 << endl;
            num1 = num2 = 0;
        }
    }
    cout << num1 << ':' << num2 << endl;
    return 0;
}