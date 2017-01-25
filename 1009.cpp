1009. Triple Inversions (35)

时间限制
300 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CAO, Peng
Given a list of N integers A1, A2, A3,...AN, there's a famous problem to count the number of inversions in it. An inversion is defined as a pair of indices i < j such that Ai > Aj.

Now we have a new challenging problem. You are supposed to count the number of triple inversions in it. As you may guess, a triple inversion is defined as a triple of indices i < j < k such that Ai > Aj > Ak. For example, in the list {5, 1, 4, 3, 2} there are 4 triple inversions, namely (5,4,3), (5,4,2), (5,3,2) and (4,3,2). To simplify the problem, the list A is given as a permutation of integers from 1 to N.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N in [3, 105]. The second line contains a permutation of integers from 1 to N and each of the integer is separated by a single space.

Output Specification:

For each case, print in a line the number of triple inversions in the list.

Sample Input:
22
1 2 3 4 5 16 6 7 8 9 10 19 11 12 14 15 17 18 21 22 20 13
Sample Output:
8

求三个数的逆序对数，只要求出一个数前后的逆序数相乘即可，直接树状数组都不用离散。

[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
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
const int low(int x){ return x&-x; }  
int n, a[maxn], f[maxn], L[maxn], R[maxn];  
  
void add(int x)  
{  
  for (int i = x; i <= n; i += low(i)) f[i]++;  
}  
  
int get(int x)  
{  
  int ans = 0;  
  for (int i = x; i; i -= low(i)) ans += f[i];  
  return ans;  
}  
  
int main()  
{  
  while (scanf("%d", &n) != EOF)  
  {  
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);  
    for (int i = 1; i <= n; i++) f[i] = 0;  
    for (int i = 1; i <= n; i++) L[i] = i - 1 - get(a[i]), add(a[i]);  
    for (int i = 1; i <= n; i++) f[i] = 0;  
    for (int i = n; i; i--) R[i] = get(a[i]), add(a[i]);  
    LL ans = 0;  
    for (int i = 1; i <= n; i++) ans += (LL)L[i] * R[i];  
    printf("%lld\n", ans);  
  }  
  return 0;  
}  
