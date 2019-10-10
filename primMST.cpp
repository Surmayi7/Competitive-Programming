#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<stack>
#include<climits>
using namespace std;

int findLeastNode (bool done[],int weight[],int totalVer)
{

  int minVertex = -1;
  for (int i=0;i<totalVer;i++)
  {
    if (done[i]==false and (minVertex ==-1||weight[i]<weight[minVertex]))
    {
      minVertex = i;
    }
  }
  return minVertex;
}

int toInt (string s) 
{
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



void dijkstraAlgo(int graph[100][100],int totalVer,bool done[],int predecessorArr[],int src,int weight[])
{
  for (int x=0;x<totalVer;x++)
  {
    weight[x] = INT_MAX;
      done[x] = false;
  }

  weight[0] = 0;
  int x = 0;
  while (x<totalVer)
  {
       int chosenVertex = findLeastNode (done,weight,totalVer);
       done[chosenVertex] = true;
       for(int adj=0;adj<totalVer;adj++)
       {
         if(graph[chosenVertex][adj]!=0 and !done[adj])
         {
int newDis = weight[chosenVertex]+graph[chosenVertex][adj];
             if(newDis<weight[adj]){
                 predecessorArr[adj] = chosenVertex;
               weight[adj] = newDis;
             }
          }
      }
      x++;
  }

}






int main (int argc,char* argv[])
{
    char* inpFile = argv[1];
    char* outFile = argv[2];
    ifstream fout;
    ofstream fin;
    fout.open (inpFile);
    fin.open (outFile);    
string s;
    getline(fout,s); 
   int totalVer = s[0]-'0'; 
    getline(fout,s);  

   int graph[100][100];
    for(int i=0;i<totalVer;i++)
    {
        for(int j=0;j<totalVer;j++)
        {
            graph[i][j]=0;        }
    }
    //int e=0;
    int src;
   
    while(!fout.eof())
    {
        string varStr;

        getline(fout,varStr);
        if (!fout.eof())
        {
          int one = varStr[0]-'a'; 
          int two = varStr[2]-'a';
          string temp;
          int position = 4;
          while (varStr[position]!='\0')
          {
            temp += varStr[position];
            position++;
}
          graph[one][two]= toInt(temp);   
      
        }

        else
        {
          src = varStr[0]-'a';        }
    }

  int weight[totalVer];
  bool done[totalVer];
  int predecessorArr[totalVer];


  memset(done,false,totalVer);
  int x = 0;
    while (x<totalVer)
    {
        predecessorArr[x]=x;
        x++;
    }

  dijkstraAlgo(graph,totalVer,done,predecessorArr,src,weight);


    for (int i=1;i<totalVer;i++)
    {
        vector<int> displayArr; 
        displayArr.push_back(i);
        int j = i;
        j = predecessorArr[j];
         while (predecessorArr[j]!=j)
         {
             displayArr.push_back(j);
             j=predecessorArr[j];
         }
       displayArr.push_back(j);
        fin<<char(src+'a')<<"-"<<char(i+'a')<<":";
          for (int position=displayArr.size()-1;position>0;position--)
          {
              
             fin<<char(displayArr[position]+'a')<<",";
          }
          fin<<char(displayArr[0]+'a');
          fin<<":"<<weight[i]<<endl;

    }
 }