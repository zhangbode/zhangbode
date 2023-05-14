#include <iostream>

using namespace std;

typedef struct student
{
    char name[9];
    int yuwen, shuxue, yingyu;
    int sum;
} student;

int main()
{
    student s[1000];
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> s[i].name >> s[i].yuwen >> s[i].shuxue >> s[i].yingyu;
        s[i].sum = s[i].yuwen + s[i].shuxue + s[i].yingyu;
    }
    int max, temp_max;
    max = s[0].sum;
    temp_max = 0;
    for (int i = 0; i < num; i++)
    {
        if (max < s[i].sum)
        {
            max = s[i].sum;
            temp_max = i;
        }
    }
    cout << s[temp_max].name << " " << s[temp_max].yuwen << " " << s[temp_max].shuxue << " " << s[temp_max].yingyu;
}