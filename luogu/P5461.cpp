#include <iostream>
#include <math.h>

using namespace std;

int a[1025][1025];

void search(int x, int m, int n)
{ // 此处传递参数下为正方形边长，m,n分别为递归正方形左上角坐标点
    if (x == 2)
    {
        a[m][n] = 0;
        return;
    }
    else
    {
        for (int i = m; i < m + x / 2; i++)
        {
            for (int j = n; j < n + x / 2; j++)
            {
                a[i][j] = 0;
            }
        }

        search(x / 2, m + x / 2, n);
        search(x / 2, m + x / 2, n + x / 2);
        search(x / 2, m, n + x / 2);
    }
}

int main()
{
    int n;
    cin >> n;
    int length = pow(2, n);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            a[i][j] = 1;
        }
    }
    search(length, 0, 0);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}