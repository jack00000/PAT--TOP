1008. Airline Routes (35)

时间限制
400 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
Given a map of airline routes, you are supposed to check if a round trip can be planned between any pair of cities.

Input Specification:

Each input file contains one test case. For each case, the first line gives two positive integers N (2<= N <= 104) and M (<=6N), which are the total number of cities (hence the cities are numbered from 1 to N) and the number of airline routes, respectively. Then M lines follow, each gives the information of a route in the format of the source city index first, and then the destination city index, separated by a space. It is guaranteed that the source is never the same as the destination.

After the map information, another positive integer K is given, which is the number of queries. Then K lines of queries follow, each contains a pair of distinct cities' indices.

Output Specification:

For each query, output in a line "Yes" if a round trip is possible, or "No" if not.

Sample Input:
12 19
3 4
1 3
12 11
5 9
6 2
3 2
10 7
9 1
7 12
2 4
9 5
2 6
12 4
11 10
4 8
8 12
11 8
12 7
1 5
20
11 4
12 7
3 6
2 3
5 3
3 9
4 3
8 3
8 10
10 11
7 8
7 1
9 5
1 9
2 6
3 1
3 12
7 3
6 9
6 8
Sample Output:
Yes
Yes
No
No
No
No
No
No
Yes
Yes
Yes
No
Yes
Yes
Yes
No
No
No
No
No
题意是给出一个有向图，然后问两个点在不在一个环上。直接上tarjan强连通即可，是一道裸题，只要判断low【x】和low【y】是不是相同即可
[cpp] view plain copy 
#include<cstdio>  
#include<cstring>  
#include<cmath>  
#include<queue>  
#include<vector>  
#include<iostream>  
#include<stack>  
#include<algorithm>  
#include<bitset>  
#include<functional>  
using namespace std;  
typedef unsigned long long ull;  
typedef long long LL;  
const int maxn = 2e5 + 10;  
int n, m, x, y, tot, t;  
int dfn[maxn], low[maxn];  
int ft[maxn], nt[maxn], v[maxn];  
stack<int> p;  
  
void tarjan(int x)  
{  
  dfn[x] = low[x] = ++t;  
  p.push(x);  
  for (int i = ft[x]; i != -1; i = nt[i])  
  {  
    if (!dfn[v[i]])  
    {  
      tarjan(v[i]);  
      low[x] = min(low[x], low[v[i]]);  
    }  
    else low[x] = min(low[x], dfn[v[i]]);  
  }  
  if (low[x] == dfn[x])  
  {  
    int u;  
    do  
    {  
      u = p.top();  p.pop();  
      low[u] = low[x];  
    } while (u != x);  
  }  
}  
  
int main()  
{  
  while (scanf("%d%d", &n, &m) != EOF)  
  {  
    tot = t = 0;  
    while (!p.empty()) p.pop();  
    for (int i = 1; i <= n; i++) ft[i] = -1, dfn[i] = 0;  
    while (m--)  
    {  
      scanf("%d%d", &x, &y);  
      v[tot] = y;  nt[tot] = ft[x]; ft[x] = tot++;  
    }  
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);  
    scanf("%d", &m);  
    while (m--)  
    {  
      scanf("%d%d", &x, &y);  
      printf("%s\n", low[x] == low[y] ? "Yes" : "No");  
    }  
  }  
  return 0;  
}  

