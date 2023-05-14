#include <iostream>

using namespace std;

char c[102][102];
int m, n;

void print();
char num(int a, int b);

int main()
{
    cin >> m >> n;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> c[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (c[i][j] != '*')
            {
                c[i][j] = num(i, j);
            }
        }
    }
    print();
}

void print()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << c[i][j];
        }
        cout << endl;
    }
}

char num(int a, int b)
{
    int num1 = m, num2 = n;
    int num = 0;
    cout << a << " " << b << " " << num1 << " " << num2 << endl;
    if (num1 > 3)
    {
        num1 = 3;
    }
    if (num2 > 3)
    {
        num2 = 3;
    }
    if (a == 0 && num1 == 3)
    {
        num1--;
    }
    else
    {
        a--;
    }
    if (b == 0 && num2 == 3)
    {
        num2--;
    }
    else
    {
        b--;
    }
    print();
    cout << a << " " << b << " " << num1 << " " << num2 << endl;

    for (int i = a; i < a + num1; i++)
    {
        for (int j = b; j < b + num2; j++)
        {
            if (c[i][j] == '*')
            {
                num++;
            }
        }
    }
    cout << endl;
    char ch = num + '0';
    return ch;
}