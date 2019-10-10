#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include<climits>
#include<cstring>

using namespace std;
int chartoint (string s) 
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

int minvertexcalc(bool*check,int *distance,int vertices)
{

  int ans=-1;
  for(int i=0;i<vertices;i++)
  {
    if(!check[i]&&(ans==-1||distance[i]<distance[ans]))
    {
      ans=i;
    }
  }
  return ans;
}

void dijiktra(int mat[100][100],int vertices,bool*check,int *parent,int source,int *distance)
{
  int x=0;
  while(x<vertices)
  {
    distance[x]=INT_MAX;
      check[x]=false;
      x++;
  }

  distance[0]=0;
  x=0;
  while(x<vertices)
  {
       int minvvalue=minvertexcalc(check,distance,vertices);
       check[minvvalue]=true;
       for(int k=0;k<vertices;k++)
       {
         if(mat[minvvalue][k]!=0&&!check[k])
         {
             if((distance[minvvalue]+mat[minvvalue][k])<distance[k]){
                 parent[k]=minvvalue;
               distance[k]=distance[minvvalue]+mat[minvvalue][k];
             }
          }
      }
      x++;
  }

}






int main(int argc,char **argv)
{
    ifstream fileinm(argv[1]);
    ofstream fileoutput(argv[2]);
    // string c="";
    string stri;
    fileinm>>stri; //first line input from file
    int vertices=stri[0]-'0'; //number of vertices 
    fileinm>>stri;  //second line input from file
    int mat[100][100];
    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            mat[i][j]=0; //initalizing every value of matix to infinity
        }
    }
    //int e=0;
    int startvertex;
   
    while(fileinm)
    {
        string tempstr;
        fileinm>>tempstr;
        int templen=tempstr.length();
        if(templen>1)
        {
          int startpoint=tempstr[0]-'a'; 
          int endpoint=tempstr[2]-'a';
          string s;
          int itr=4;
          while(tempstr[itr]!='\0')
          {
            s+=tempstr[itr];
            itr++;
          }
          int ans=chartoint(s);
          mat[startpoint][endpoint]=ans;  //initialized wieghts
         
    
      
        }

        else if(tempstr[0]!=0)
        {
          startvertex=tempstr[0]-'a'; //source vertex
        }
    }

  int *distance=new int[vertices];
  bool*check=new bool[vertices];
  int *parent=new int[vertices];

  // for(int i=0;i<vertices;i++)

  memset(check,false,vertices);
  int x=0;
    while(x<vertices)
    {
        parent[x]=x;
        x++;
    }

  dijiktra(mat,vertices,check,parent,startvertex,distance);


    for(int i=1;i<vertices;i++)
    {
        vector<int>ansarray; 
        ansarray.push_back(i);
        int j=i;
        j=parent[j];
         while(parent[j]!=j)
         {
             ansarray.push_back(j);
             j=parent[j];
         }
       ansarray.push_back(j);
        fileoutput<<char(startvertex+'a')<<"-"<<char(i+'a')<<":";
          for(int itr=ansarray.size()-1;itr>0;itr--)
          {
              
             fileoutput<<char(ansarray[itr]+'a')<<",";
          }
          fileoutput<<char(ansarray[0]+'a');
          fileoutput<<":"<<distance[i]<<endl;

    }
 }