1007. Red-black Tree (35)

时间限制
150 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CAO, Peng
There is a kind of binary tree named red-black tree in the data structure. It has the following 5 properties:

(1) Every node is either red or black.
(2) The root is black.
(3) All the leaves are NULL nodes and are colored black.
(4) Each red node must have 2 black descends (may be NULL).
(5) All simple paths from any node x to a descendant leaf have the same number of black nodes.

We call a non-NULL node an internal node. From property (5) we can define the black-height of a red-black tree as the number of nodes on the simple path from the root (excluding the root itself) to any NULL leaf (including the NULL leaf). And we can derive that a red-black tree with black height H has at least 2H-1 internal nodes.

Here comes the question: given a positive N, how many distinct red-black trees are there that consist of exactly N internal nodes?

Input Specification:

Each input file contains one test case which gives a positive integer N (<= 500).

Output Specification:

For each case, print in a line the number of distinct red-black tees with N internal nodes. Since the answer may be very large, output the remainder of it divided by 1000000007 please.

Sample Input:
5
Sample Output:
8

此题给出的是红黑树的定义，然后求的是n个节点的红黑树有多少种。我用的是三维dp

f[i][j][k]表示的是含有i个节点的深度为j的根为k的树的数量

深度是只考虑从根节点到叶子节点（不含叶子节点）的黑点数量，k分为0和1,0是红，1是黑

然后就可以考虑状态的转移了，具体看代码，事实上500个点的红黑树深度也不超过8，所以红黑树最为二叉平衡树，本身有严格的logn深度，就是实现比较困难。

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
const int maxn = 5e2 + 10;  
const int mod = 1e9 + 7;  
int n;  
LL f[maxn][maxn][2], s[maxn][maxn];  
  
void Init()  
{  
  memset(f, 0, sizeof(f));  
  memset(s, 0, sizeof(s));  
  f[1][0][0] = f[0][0][1] = 1;  
  for (int i = 1; i < maxn; i++)  
  {  
    for (int j = 1; j <= min(i, 8); j++)  
    {  
      f[i][j][0] = f[i][j][1] = 0;  
      for (int k = 0; k < i; k++)  
      {  
        (f[i][j][1] += (f[k][j - 1][0] + f[k][j - 1][1]) * (f[i - k - 1][j - 1][0] + f[i - k - 1][j - 1][1]) % mod) %= mod;  
        (f[i][j][0] += f[k][j][1] * f[i - k - 1][j][1] % mod) %= mod;  
      }  
      s[i][j] = (s[i][j - 1] + f[i][j][1]) % mod;  
    }  
  }  
}  
  
int main()  
{  
  Init();  
  while (scanf("%d", &n) != EOF) printf("%d\n", s[n][min(n, 8)]);  
  return 0;  
}  


