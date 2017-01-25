/* 
1001. Battle Over Cities - Hard Version (35)

时间限制
800 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
It is vitally important to have all the cities connected by highways in a war. 
If a city is conquered by the enemy, all the highways from/toward that city will be closed.
 To keep the rest of the cities connected, we must repair some highways with the minimum cost.
  On the other hand, if losing a city will cost us too much to rebuild the connection,
   we must pay more attention to that city.

Given the map of cities which have all the destroyed and remaining highways marked, 
you are supposed to point out the city to which we must pay the most attention.

Input Specification:

Each input file contains one test case. Each case starts with a line containing 2 numbers N (<=500),
 and M, which are the total number of cities, and the number of highways, respectively. Then M lines follow,
  each describes a highway by 4 integers:

City1 City2 Cost Status
where City1 and City2 are the numbers of the cities the highway connects (the cities are numbered from 1 to N),
 Cost is the effort taken to repair that highway if necessary, and Status is either 0, meaning that highway is destroyed,
  or 1, meaning that highway is in use.

Note: It is guaranteed that the whole country was connected before the war.

Output Specification:

For each test case, just print in a line the city we must protest the most, that is,
 it will take us the maximum effort to rebuild the connection if that city is conquered by the enemy.

In case there is more than one city to be printed, output them in increasing order of the city numbers,
 separated by one space, but no extra space at the end of the line. 
 In case there is no need to repair any highway at all, simply output 0.

Sample Input 1:
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 1 0
Sample Output 1:
1 2
Sample Input 2:
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 2 1
Sample Output 2:
0

简单来说就是枚举删除每个点的最小生成树的最大的花费是多少，注意如果不能联通那么一定是最大的，最后在遍历一遍输出答案即可
*/ 
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
const int maxn = 1e5 + 10;  
const int INF = 0x7FFFFFFF;  
int n, m, fa[maxn], cost[maxn];  
  
int get(int x)  
{  
  return x == fa[x] ? x : fa[x] = get(fa[x]);  
}  
  
struct point  
{  
  int x, y, c, u;  
  void read(){ scanf("%d%d%d%d", &x, &y, &c, &u); }  
  bool operator<(const point&a)const{ return u == a.u ? c<a.c : u>a.u; }  
}a[maxn];  
  
int main()  
{  
  while (scanf("%d%d", &n, &m) != EOF)  
  {  
    for (int i = 0; i < m; i++) a[i].read();  
    sort(a, a + m);  
    int ans = 0;  
    for (int i = 1; i <= n; i++)  
    {  
      for (int j = 1; j <= n; j++) fa[j] = j;  
      int cnt = n - 2;  
      cost[i] = 0;  
      for (int j = 0; j < m; j++)  
      {  
        if (a[j].x == i || a[j].y == i) continue;  
        int fx = get(a[j].x), fy = get(a[j].y);  
        if (fx == fy) continue;  cnt--;  
        fa[fx] = fy;  if (!a[j].u) cost[i] += a[j].c;  
      }  
      if (cnt > 0) cost[i] = INF;  
      ans = max(ans, cost[i]);  
    }  
    if (ans)  
    {  
      int flag = 0;  
      for (int i = 1; i <= n; i++)  
      if (cost[i] == ans)  
      {  
        printf("%s%d", flag ? " " : "", i);  flag = 1;  
      }  
    }  
    else printf("%d\n", ans);  
  }  
  return 0;  
}  
