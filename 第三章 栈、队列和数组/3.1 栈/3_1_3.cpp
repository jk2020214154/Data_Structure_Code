#include<iostream>

using namespace std;

bool check_legality(string s)
{
    int cnt_o=0,cnt_i=0;

    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='O')
            cnt_o++;
        else cnt_i++;
        if(cnt_o>cnt_i)
        {
            cout << "序列不合法" << endl;
            return false;
        }
    }
    if(cnt_o!=cnt_i)
    {
        cout << "序列不合法" << endl;
        return false;
    }
    else
    {
        cout << "序列合法" << endl;
        return true;
    }
}

int main()
{
    string s;
    cin >> s;

    check_legality(s);

    return 0;
}