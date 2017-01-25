/* 
1003. Universal Travel Sites (35)

时间限制
200 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
After finishing her tour around the Earth, CYLL is now planning a universal travel sites development project. 
After a careful investigation, she has a list of capacities of all the satellite transportation stations in hand.
 To estimate a budget, she must know the minimum capacity that a planet station must have to guarantee that every 
 space vessel can dock and download its passengers on arrival.

Input Specification:

Each input file contains one test case. For each case, the first line contains the names of the source 
and the destination planets, and a positive integer N (<=500). Then N lines follow, each in the format:

sourcei destinationi capacityi

where sourcei and destinationi are the names of the satellites and the two involved planets, and capacityi > 0 
is the maximum number of passengers that can be transported at one pass from sourcei to destinationi. 
Each name is a string of 3 uppercase characters chosen from {A-Z}, e.g., ZJU.

Note that the satellite transportation stations have no accommodation facilities for the passengers. Therefore none
 of the passengers can stay. Such a station will not allow arrivals of space vessels that
  contain more than its own capacity. It is guaranteed that the list contains neither
   the routes to the source planet nor that from the destination planet.

Output Specification:

For each test case, just print in one line the minimum capacity that a planet station must have to guarantee that every space vessel can dock and download its passengers on arrival.

Sample Input:
EAR MAR 11
EAR AAA 300
EAR BBB 400
AAA BBB 100
AAA CCC 400
AAA MAR 300
BBB DDD 400
AAA DDD 400
DDD AAA 100
CCC MAR 400
DDD CCC 200
DDD MAR 300
Sample Output:
700

这个题意有点难懂，不过其实就是个最裸的网络最大流，效率低的ek算法也能过，这里我用的是dinic

[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
*/ 
#include<cstdio>  
#include<cstring>  
#include<cmath>  
#include<queue>  
#include<vector>  
#include<map>  
#include<iostream>  
#include<string>  
#include<stack>  
#include<algorithm>  
#include<bitset>  
#include<functional>  
using namespace std;  
typedef unsigned long long ull;  
typedef long long LL;  
const int maxn = 1e5 + 10;  
const int INF = 0x7FFFFFFF;  
map<string, int> M;  
char x[maxn], y[maxn];  
int n, z, tot;  
  
struct MaxFlow  
{  
  const static int maxe = 1e6 + 10;    //边数  
  const static int maxp = 1e5 + 10;   //点数  
  const static int INF = 0x7FFFFFFF;  
  struct Edges  
  {  
    int x, f;  
    Edges(){}  
    Edges(int x, int f) :x(x), f(f){}  
  }edge[maxe];  
  int first[maxp], next[maxe], dis[maxp], tot, work[maxp], n;  
  
  void clear(int x){ n = x; tot = 0; for (int i = 0; i <= n; i++) first[i] = -1; }  
  
  void AddEdge(int s, int t, int f)  
  {  
    edge[tot] = Edges(t, 0); next[tot] = first[s]; first[s] = tot++;  
    edge[tot] = Edges(s, f); next[tot] = first[t]; first[t] = tot++;  
  }  
  
  bool bfs(int s, int t)  
  {  
    for (int i = 0; i <= n; i++) dis[i] = -1;  
    queue<int> p;    p.push(s);    dis[s] = 0;  
    while (!p.empty())  
    {  
      int q = p.front();    p.pop();  
      for (int i = first[q]; i != -1; i = next[i])  
      {  
        if (edge[i ^ 1].f&&dis[edge[i].x] == -1)  
        {  
          p.push(edge[i].x);  
          dis[edge[i].x] = dis[q] + 1;  
          if (dis[t] != -1) return true;  
        }  
      }  
    }  
    return false;  
  }  
  
  int dfs(int s, int t, int low)  
  {  
    if (s == t) return low;  
    for (int &i = work[s], x; i >= 0; i = next[i])  
    {  
      if (dis[s] + 1 == dis[edge[i].x] && edge[i ^ 1].f && (x = dfs(edge[i].x, t, min(low, edge[i ^ 1].f))))  
      {  
        edge[i].f += x;    edge[i ^ 1].f -= x;  return x;  
      }  
    }  
    return 0;  
  }  
  
  int dinic(int s, int t)  
  {  
    int maxflow = 0, inc = 0;  
    while (bfs(s, t))  
    {  
      for (int i = 0; i <= n; i++) work[i] = first[i];  
      while (inc = dfs(s, t, INF)) maxflow += inc;  
    }  
    return maxflow;  
  }  
}solve;  
  
int main()  
{  
  while (scanf("%s%s%d", x, y, &n) != EOF)  
  {  
    solve.clear(2 * n + 2);  
    M[x] = 1;  M[y] = 2;  tot = 3;  
    while (n--)  
    {  
      scanf("%s%s%d", x, y, &z);  
      if (!M[x]) M[x] = tot++;  
      if (!M[y]) M[y] = tot++;  
      solve.AddEdge(M[x], M[y], z);  
    }  
    printf("%d\n", solve.dinic(1, 2));  
  }  
  return 0;  
}  
