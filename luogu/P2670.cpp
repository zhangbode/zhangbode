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
            num(i, j);
        }
    }
}

num(int a, int m)
{
}