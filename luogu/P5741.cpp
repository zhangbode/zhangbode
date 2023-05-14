#include <iostream>

using namespace std;

typedef struct student
{
    char name[9];
    int score1, score2, score3;
    int sumscore;
} student;

bool score(int scorem, int scoren)
{
    if (-5 <= (scorem - scoren) && (scorem - scoren) <= 5)
    {
        return true;
    }
    return false;
}

bool sumscore(int sumscorem, int sumscoren)
{
    if (-10 <= (sumscorem - sumscoren) && (sumscorem - sumscoren) <= 10)
    {
        return true;
    }
    return false;
}

int main()
{
    int num;
    cin >> num;
    student s[1000];
    for (int i = 0; i < num; i++)
    {
        cin >> s[i].name >> s[i].score1 >> s[i].score2 >> s[i].score3;
        s[i].sumscore = s[i].score1 + s[i].score2 + s[i].score3;
    }
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (score(s[i].score1, s[j].score1) && score(s[i].score2, s[j].score2) && score(s[i].score3, s[j].score3) && sumscore(s[i].sumscore, s[j].sumscore))
            {
                cout << s[i].name << " " << s[j].name << endl;
            }
        }
    }
}