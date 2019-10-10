#include<iostream>
#include<fstream>
#include<stack>
using namespace std;

int toInt (string s) {
    int num = 0,n = s.size(),i = 0;
    while (i<n)
    {
        num = num * 10 + (s[i]-'0');
        i++;
    }
    return num;
}

void dfs (int n,int graph[100][100],bool visited[],int i,stack<int>& s) {
	if (visited[i])
		return;
	visited[i] = true;
	for (int j=0;j<n;j++)
	{
		if (graph[i][j] && !visited[j])
			dfs (n,graph,visited,j,s);
	}
	s.push(i);
}

void topologicalSort (int n,int graph[100][100],stack<int>& s) {
	bool visited[n];
	for (int i=0;i<n;i++)
		visited[i] = false;
	for (int i=0;i<n;i++)
		if (!visited[i])
			dfs (n,graph,visited,i,s);
}

int main (int argc,char* argv[]) {
    char* inpFile = argv[1];
    char* outFile = argv[2];
    ifstream fout;
    ofstream fin;
    fout.open(inpFile);
    fin.open(outFile);
    string s;
    getline (fout,s);
    string temp = "";
    int curr = 0;
    while (isdigit(s[curr]))
    {
    	temp += s[curr];
    	curr++;
    }
    int vertices = toInt(temp);
    int graph[100][100];
    for (int i=0;i<vertices;i++)
        for (int j=0;j<vertices;j++)
            graph[i][j] = 0;
    getline (fout,s);
    char init = s[0];
    while (!fout.eof())
    {
    	getline (fout,s);
    	int start = s[0] - init;
    	int finish = s[2] - init;
    	graph[start][finish] = 1;
    }
    stack<int> stk;
    topologicalSort (vertices,graph,stk);
    while (!stk.empty())
    {
    	char node = stk.top() + init;
    	stk.pop();
    	fin<<node;
    	if (!stk.empty())
    		fin<<",";
    }
    fout.close();
    fin.close();

}
