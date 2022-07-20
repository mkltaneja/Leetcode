#include <iostream>
#include <bits/stdc++.h>
using namespace std;

unordered_map<string,string> par;

string findpar(string a)
{
  return par[a] = (par[a] == a)? a : findpar(par[a]);
}

string TreeConstructor(string strArr[], int arrLength) 
{
  unordered_map<string,int> pcnt;
  for(int i = 0; i < arrLength; i++)
  {
    string a = "", b = "";
    int j = 1;
    while(strArr[i][j] >= '0' && strArr[i][j] <= '9')
      a += strArr[i][j++];
    j++;
    while(strArr[i][j] >= '0' && strArr[i][j] <= '9')
      b += strArr[i][j++];
    
    cout<<a<<", "<<b<<endl;

    if(++pcnt[b] > 2) return "false";
    cout<<a<<", "<<b<<endl;
    
    if(par.count(a) && par[a] != a) return "false";
    cout<<a<<", "<<b<<endl;
    if(!par.count(b)) par[b] = b;
    cout<<a<<", "<<b<<endl;
    string pb = findpar(b);
    cout<<"pb = "<<pb<<endl;
    par[a] = pb;
  }
  
  unordered_set<string> pars;
  for(auto p : par)
    pars.insert(findpar(p.first));
  cout<<"SOMETHING::::";
  return pars.size() == 1? "true" : "false";
}

int main(void) { 
   
  // keep this function call here
  // cout<<"ABCDEFGH";
  string A[] = {"(1,2)", "(2,4)", "(5,7)", "(7,2)", "(9,5)"};
  int arrLength = sizeof(A) / sizeof(*A);
  cout << TreeConstructor(A, arrLength);
  return 0;
    
}