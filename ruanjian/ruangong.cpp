#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <stack>
#include <string>

using namespace std;

bool t;   // 控制是否保存到文件
int m, n; // 题目结果范围，题目数量
int temp; //+-*/选择
char ch;
string str; // 将算式保存为字符串
int num0;

void menu()
{
    system("cls");
    cout << "<---------------------menu--------------------->" << endl;
    cout << "欢迎使用算式生成程序，请按照指示使用本程序" << endl;
    cout << "一年级（20以内加法或减法）\t\t\t1" << endl;
    cout << "二年级（50以内加减混合运算）\t\t\t2" << endl;
    cout << "三年级（1000以内加、减及乘混合运算\t\t3" << endl;
    cout << "四到六年级（非负整数混合运算）\t\t\t4" << endl;
    cout << "退出程序\t\t\t\t\t0" << endl;
    cout << "<---------------------------------------------->" << endl;
}
random_device rd; // 为随机数做准备
mt19937 gen(rd());

ofstream outfile; // 为输出到文件做准备

string select_Ch(int num)
{
    if (num == 1)
    {
        return "+";
    }
    else if (num == 2)
    {
        return "-";
    }
    else if (num == 3)
    {
        return "*";
    }
    else
    {
        return "/";
    }
}

void add(int m, int n, bool t)
{ // 传入数据限制生成算式结果
    uniform_int_distribution<> bernoulli_distribution(1, m);
    int num1, num2;
    int i = 0;
    if (t == false)
    {
        outfile.open("test.txt", ios::trunc);
        outfile.close();
        outfile.open("test.txt", ios::out | ios::app);
        if (!outfile)
        {
            cerr << "open error!";
            exit(1);
        }
    }
    while (i < n)
    {
        num1 = bernoulli_distribution(gen);
        num2 = bernoulli_distribution(gen);
        if (num1 + num2 <= m)
        {
            str = to_string(num1) + "+" + to_string(num2) + "=";
            if (t == true)
            {
                cout << str << endl;
                i++;
            }
            else
            {
                outfile << str << endl;
                i++;
            }
        }
    }
    outfile.close();
    cout << "生成完毕" << endl;
}
void sub(int m, int n, bool t)
{ // 传入数据限制生成算式结果
    uniform_int_distribution<> bernoulli_distribution(1, m);
    int num1, num2;
    int i = 0;
    if (t == false)
    {
        outfile.open("test.txt", ios::trunc);
        outfile.close();
        outfile.open("test.txt", ios::out | ios::app);
        if (!outfile)
        {
            cerr << "open error!";
            exit(1);
        }
    }
    while (i < n)
    {
        num1 = bernoulli_distribution(gen);
        num2 = bernoulli_distribution(gen);
        int temp0;
        if (num1 < num2)
        {
            temp0 = num1;
            num1 = num2;
            num2 = temp0;
        }
        if (num1 - num2 >= 0)
        {
            str = to_string(num1) + "-" + to_string(num2) + "=";
            if (t == true)
            {
                cout << str << endl;
                i++;
            }
            else
            {
                outfile << str << endl;
                i++;
            }
        }
    }
    outfile.close();
    cout << "生成完毕" << endl;
}
void add_sub_two(int m, int n, bool t)
{
    int num1, num2, num3;
    uniform_int_distribution<> bernoulli_distribution(1, m);
    uniform_int_distribution<> selectNum(1, 4);
    if (t == 0)
    {
        outfile.open("test.txt", ios::trunc);
        outfile.close();
        outfile.open("test.txt", ios::out | ios::app);
        if (!outfile)
        {
            cerr << "open error!";
            exit(1);
        }
    }
    string ch1, ch2;
    int i = 0;
    int num = 100;
    while (i < n)
    {
        ch1 = "-", ch2 = "-";
        num1 = bernoulli_distribution(gen);
        num2 = bernoulli_distribution(gen);
        num3 = bernoulli_distribution(gen);
        num = selectNum(gen);
        switch (num)
        {
        case 1:
            if (num1 + num2 + num3 <= 50)
            {
                str = to_string(num1) + "+" + to_string(num2) + "+" + to_string(num3) + "=";
            }
            else
            {
                continue;
            }
            break;
        case 2:
            if ((num1 + (num2 - num3)) <= 50 && (num1 + (num2 - num3)) >= 0)
            {
                str = to_string(num1) + "+(" + to_string(num2) + "-" + to_string(num3) + ")=";
            }
            else
            {
                continue;
            }
            break;
        case 3:
            if ((num1 - (num2 + num3)) <= 50 && (num1 - (num2 + num3)) >= 0)
            {
                str = to_string(num1) + "-(" + to_string(num2) + "+" + to_string(num3) + ")=";
            }
            else
            {
                continue;
            }
            break;
        case 4:
            if ((num1 - num2 - num3) >= 0)
            {
                str = to_string(num1) + "-" + to_string(num2) + "-" + to_string(num3) + "=";
            }
            else
            {
                continue;
            }
            break;
        }
        if (t == true)
        {
            cout << str << endl;
            i++;
        }
        else
        {
            outfile << str << endl;
            i++;
        }
    }
    outfile.close();
    cout << "生成完毕" << endl;
}
void third_num(int m, int n, bool t)
{
    uniform_int_distribution<> bernoulli_distribution(1, m);
    uniform_int_distribution<> selectChnum(1, 3);
    if (t == 0)
    {
        outfile.open("test.txt", ios::trunc);
        outfile.close();
        outfile.open("test.txt", ios::out | ios::app);
        if (!outfile)
        {
            cerr << "open error!";
            exit(1);
        }
    }
    string ch1, ch2;
    int num1, num2, num3;
    int num = 100;
    int i = 0;
    while (i < n)
    {
        // ch1 = "-", ch2 = "-";
        num1 = bernoulli_distribution(gen);
        num2 = bernoulli_distribution(gen);
        num3 = bernoulli_distribution(gen);
        num = selectChnum(gen);
        ch1 = select_Ch(num);
        num = selectChnum(gen);
        ch2 = select_Ch(num);
        str = to_string(num1) + ch1 + to_string(num2) + ch2 + to_string(num3) + "=";
        if (t == true)
        {
            cout << str << endl;
            i++;
        }
        else
        {
            outfile << str << endl;
            i++;
        }
    }
    outfile.close();
    cout << "生成完毕" << endl;
}
void four_num(int m, int n, bool t)
{
    uniform_int_distribution<> bernoulli_distribution(1, m);
    uniform_int_distribution<> selectChnum(1, 3);
    uniform_int_distribution<> select(0, 1);
    if (t == 0)
    {
        outfile.open("test.txt", ios::trunc);
        outfile.close();
        outfile.open("test.txt", ios::out | ios::app);
        if (!outfile)
        {
            cerr << "open error!";
            exit(1);
        }
    }
    string ch1, ch2;
    int num1, num2, num3;
    int n1, n2;
    int num = 100;
    int i = 0;
    while (i < n)
    {
        num1 = bernoulli_distribution(gen);
        num2 = bernoulli_distribution(gen);
        num3 = bernoulli_distribution(gen);
        num = selectChnum(gen);
        ch1 = select_Ch(num);
        num = selectChnum(gen);
        ch2 = select_Ch(num);
        n1 = select(gen);
        n2 = select(gen) + 1;
        if (n1 == n2)
        {
            str = to_string(num1) + ch1 + "(" + to_string(num2) + ch2 + to_string(num3) + ")=";
        }
        else if (n1 == 0 && n2 == 1)
        {
            str = "(" + to_string(num1) + ch1 + to_string(num2) + ")" + ch2 + to_string(num3) + "=";
        }
        else if (n1 == 0 && n2 == 2)
        {
            str = to_string(num1) + ch1 + to_string(num2) + ch2 + to_string(num3) + "=";
        }
        else if (n1 == 1 && n2 == 2)
        {
            str = to_string(num1) + ch1 + "(" + to_string(num2) + ch2 + to_string(num3) + ")=";
        }
        if (t == true)
        {
            cout << str << endl;
            i++;
        }
        else
        {
            outfile << str << endl;
            i++;
        }
    }
    outfile.close();
    cout << "生成完毕" << endl;
}
void one()
{
    str = "";
    cout << "请输入题目数量：";
    cin >> n;
    cout << "请选择加法或者减法,1/0(1表示加法,0表示减法)：";
    cin >> temp;
    cout << "请选择是否输出到文件，Y/N：";
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
    {
        t = false;
    }
    else
    {
        t = true;
    }
    m = 20;
    if (temp == 1)
    {
        add(m, n, t);
    }
    else
    {
        sub(m, n, t);
    }
}
void two()
{
    str = "";
    cout << "请输入题目数量：";
    cin >> n;
    cout << "请选择是否输出到文件，Y/N：";
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
    {
        t = false;
    }
    else
    {
        t = true;
    }
    m = 50;
    add_sub_two(m, n, t);
}
void third()
{
    str = "";
    cout << "请输入题目数量：";
    cin >> n;
    cout << "请选择是否输出到文件，Y/N：";
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
    {
        t = false;
    }
    else
    {
        t = true;
    }
    m = 1000;
    third_num(m, n, t);
}
void four()
{
    str = "";
    cout << "请输入题目数量：";
    cin >> n;
    cout << "请选择是否输出到文件，Y/N：";
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
    {
        t = false;
    }
    else
    {
        t = true;
    }
    m = 100;
    four_num(m, n, t);
}
int main()
{
    int num;
    while (true)
    {
        menu();
        cin >> num;
        switch (num)
        {
        case 1:
            one();
            system("pause");
            break;
        case 2:
            two();
            system("pause");
            break;
        case 3:
            third();
            system("pause");
            break;
        case 4:
            four();
            system("pause");
            break;
        default:
            return 0;
        }
    }
}