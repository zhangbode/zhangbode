#include <iostream>
#include <math.h>

using namespace std;

bool prime(int num)
{
    if (num == 1)
    {
        return false;
    }
    if (num == 2)
    {
        return true;
    }
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int num;
    cin >> num;
    for (int i = 4; i <= num; i = i + 2)
    {
        for (int j = 2; j <= i; j++)
        {
            if (prime(j))
            {
                if (prime(i - j))
                {
                    cout << i << "=" << j << "+" << i - j << endl;
                    break;
                }
            }
        }
    }
    return 0;
}