#include <iostream>

using namespace std;

struct student
{
    string name;
    int num;
    int score;
};

int main()
{
    int n;
    cin >> n;
    student s[6];
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].name >> s[i].num >> s[i].score;
        s[i].num++;
        s[i].score *= 1.2;
    }
    for (int i = 0; i < n; i++)
    {
        cout << s[i].name << " " << s[i].num << " ";
        if (s[i].score > 600)
        {
            s[i].score = 600;
        }
        cout << s[i].score << endl;
    }
}