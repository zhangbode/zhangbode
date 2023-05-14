// 全是细节
#include <iostream>
#include <math.h>
#include <string>

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
bool pdnum(int num)
{
    /* 在此之前，通过数字前后反转
     * 和字符串前后反转再比较都耗时较长，
     *此处使用转化为字符串前半段与后半段比较方式检查
     */
    // 转化为字符串，求出字符串长度后前后比对
    string s = to_string(num);
    int len = s.length();

    // 此处添加判断位数，偶数位数的数除了11必然不是质数
    if (len % 2 == 0 && num != 11)
    {
        return false;
    }

    for (int i = 0; i < (int)len / 2; i++)
    {
        if (s[i] != s[len - i - 1])
        {
            return false;
        }
    }
    return true;
}
// 主函数中先排除所有偶数，从第一个奇数开始判断大约节省一半时间
// 其次在题目要求5-100000000之间最大的回文质数为9989899，将循环设置为最多循环到9999999以此节约时间
// 第三，由于回文数比质数少，所以先判断是否为回文数，再判断是否为素数，进一步节约时间
// 第四，回文质数除11外，再无偶数位的回文数，故对偶数位的数字直接排除
// 第五，可使用printf()输出结果，用时较cout相对较少
// 最后，磁体可通过创造回文数再判断是否为质数的方式解决，为最优解。
int main()
{
    int a, b;
    cin >> a >> b;
    if (a % 2 == 0)
    {
        a++;
    }
    b = min(9999999, b);
    for (int i = a; i <= b; i = i + 2)
    {
        if (!pdnum(i))
        {
            continue;
        }
        if (!prime(i))
        {
            continue;
        }
        cout << i << endl;
    }
}