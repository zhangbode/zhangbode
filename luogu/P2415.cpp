#include <iostream>

using namespace std;

int main()
{
    int s[30];
    int i = 0, num;
    long sum = 0;
    do
    {
        cin >> s[i];
        i++;
    } while (getchar() != '\n');
    num = i;
    int j = 0, m = 0, n;
    for (j = 0; j < num; j++)
    {
        for (m = 0; m < num - j; m++)
        {
            for (n = m; n <= m + j; n++)
            {
                sum += s[n];
            }
        }
    }
    cout << sum;
}