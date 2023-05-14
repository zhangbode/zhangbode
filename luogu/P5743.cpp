#include <iostream>
using namespace std;
int main()
{
    int n;
    int num = 1;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        num = (num + 1) * 2;
    }
    cout << num;
}