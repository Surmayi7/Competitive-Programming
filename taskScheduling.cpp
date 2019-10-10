#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;

struct Task {
    int deadline,penalty,id;
};

int toInt (string s) {
    int num = 0,n = s.size(),i = 0,neg = 1;
    if (s[0]=='-')
    {
        neg = -1;
        i++;
    }

    while (i<n)
    {
        num = num*10 + (s[i]-'0');
        i++;
    }
    return neg * num;
}

bool comparator (Task t1,Task t2) {
    //if (t1.penalty!=t2.penalty)
        return t1.penalty > t2.penalty;
    //return t1.deadline < t2.deadline;
}

// int findMax (vector<Task> arr,int n) {
//     int maxSize = 0;
//     for (int i=0;i<n;i++)
//         if (arr[i].deadline>maxSize)
//             maxSize = arr[i].deadline;
//     return maxSize;
// }

int main (int argc,char* argv[]) {
    char* inpFile = argv[1];
    char* outFile = argv[2];
    vector<Task> arr;
    int n = 0;
    ifstream fout;
    ofstream fin;
    fout.open(inpFile);
    fin.open(outFile);
    while (!fout.eof())
    {
        string s;
        getline (fout,s);
        int len = s.length();
        Task a;
        int curr = 0;
        for (int i=0;i<len;i++)
        {
            string num;
            while (i<len and s[i]!=' ' and s[i]!=',')
            {
                num += s[i++];
            }
            if (curr==0)
                a.id = toInt(num);
            if (curr==1)
                a.deadline = toInt(num);
            else
                a.penalty = toInt(num);
            curr++;
        }
        arr.push_back (a);
    }
    sort (arr.begin(),arr.end(),comparator);
    n = arr.size();
    int maxSize = n - 1;//findMax (arr,n);
    vector<int> done(maxSize,-1);
    for (int i=0;i<n;i++)
    {
        int index = min(maxSize,arr[i].deadline) - 1;
        while (index>=0 and done[index]!=-1)
            index--;
        if (index>=0)
        {
            done[index] = arr[i].id;
            arr[i].penalty = 0;
            arr[i].id = -1;
        }
    }
    vector<int> ans;
    int totalPenalty = 0;
    for (int i=0;i<n;i++)
    {
        if (arr[i].id!=-1)
        {
            ans.push_back (arr[i].id);
            totalPenalty += arr[i].penalty;
        }
    }
    sort (ans.begin(),ans.end());
    sort (done.begin(),done.end());
    for (int i=0;i<maxSize;i++)
    {
        if (done[i]==-1)
            continue;
        fin<<done[i];
        if (ans.size()==0 and i==maxSize-1)
            break;
        fin<<",";
    }
    n = ans.size();
    for (int i=0;i<n;i++)
    {
        fin<<ans[i];
        if (i!=n-1)
            fin<<",";
    }
    fin<<"\n"<<totalPenalty;
    fout.close();
    fin.close();
}
