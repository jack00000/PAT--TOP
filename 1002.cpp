/* 
1002. Business (35)

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
As the manager of your company, you have to carefully consider, for each project, the time taken to finish it, the deadline, and the profit you can gain, in order to decide if your group should take this project. For example, given 3 projects as the following:

Project[1] takes 3 days, it must be finished in 3 days in order to gain 6 units of profit.
Project[2] takes 2 days, it must be finished in 2 days in order to gain 3 units of profit.
Project[3] takes 1 day only, it must be finished in 3 days in order to gain 4 units of profit.
You may take Project[1] to gain 6 units of profit. But if you take Project[2] first, then you will have 1 day left to complete Project[3] just in time, and hence gain 7 units of profit in total. Notice that once you decide to work on a project, you have to do it from beginning to the end without any interruption.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N(<=50), and then followed by N lines of projects, each contains three numbers P, L, and D where P is the profit, L the lasting days of the project, and D the deadline. It is guaranteed that L is never more than D, and all the numbers are non-negative integers.

Output Specification:

For each test case, output in a line the maximum profit you can gain.

Sample Input:
4
7 1 3
10 2 3
6 1 2
5 1 1
Sample Output:
18

这道题简单来说其实就是个01背包，稍微多了一点点限制，然而坑爹的是题目没有数据范围，数组开多大不知道，所以考虑用map

好在此题n比较小，用map也不会爆内存。

[cpp] view plain copy
*/ 
#include<cstdio>  
#include<cstring>  
#include<cmath>  
#include<queue>  
#include<vector>  
#include<map>  
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
int n;  
map<LL, LL> M[55];  
map<LL, LL> ::iterator it;  
  
struct point  
{  
  int x, y, z;  
  void read(){ scanf("%d%d%d", &x, &y, &z); }  
  bool operator<(const point &a)const  
  {  
    return z < a.z;  
  }  
}a[maxn];  
  
int main()  
{  
  while (scanf("%d", &n) != EOF)  
  {  
    for (int i = 0; i <= n; i++) M[i].clear();  
    LL ans = 0;  M[0][0] = 0;  
    for (int i = 0; i < n; i++) a[i].read();  
    sort(a, a + n);  
    for (int i = 0; i < n; i++)  
    {    
      M[i + 1] = M[i];  
      for (it = M[i].begin(); it != M[i].end(); it++)  
      {  
        if (it->first + a[i].y <= a[i].z)  
        {  
          ans = max(ans, M[i + 1][it->first + a[i].y] = max(M[i + 1][it->first + a[i].y], it->second + a[i].x));  
        }  
      }  
    }  
    printf("%lld\n", ans);  
  }  
  return 0;  
}  


