#include <iostream>

using namespace std;

struct student
{
    int num;
    int score;
    int quscore;
    int sum_score;
    int total_score;
    bool score0(int score1, int score2)
    {
        if (score1 > 140 && score2 >= 800)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    int n;
    student s[1000], st;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].num >> s[i].score >> s[i].quscore;
        s[i].sum_score = s[i].score + s[i].quscore;
        s[i].total_score = s[i].score * 7 + s[i].quscore * 3;
    }
    for (int i = 0; i < n; i++)
    {
        if (st.score0(s[i].sum_score, s[i].total_score))
        {
            cout << "Excellent" << endl;
        }
        else
        {
            cout << "Not excellent" << endl;
        }
    }
    return 0;
}