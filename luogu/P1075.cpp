// 从大到小找比较费时，故此处通过找最小的的方式反向求出最大质因数
// 此时，最小质因数一定不会超过n的开方，故此消耗时间较少

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
    int n;
    cin >> n;
    int num = n;
    for (int i = 2; i < sqrt(num); i++)
    {
        if (prime(i))
        {
            if (num % i == 0)
            {
                if (prime(num % i))
                {
                    cout << num / i;
                    break;
                }
            }
        }
    }
    return 0;
}
