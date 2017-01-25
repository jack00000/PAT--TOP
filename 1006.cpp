1006. Tree Traversals - Hard Version (35)

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
Given the partial results of a binary tree's traversals in in-order, pre-order, and post-order. You are supposed to output the complete results and the level order traversal sequence of the corresponding tree.

Input Specification:

Each input file contains one test case. For each case, a positive integer N (<=100) is given in the first line. Then three lines follow, containing the incomplete in-order, pre-order and post-order traversal sequences, respectively. It is assumed that the tree nodes are numbered from 1 to N and no number is given out of the range. A "-" represents a missing number.

Output Specification:

For each case, print in four lines the complete in-order, pre-order and post-order traversal sequences, together with the level order traversal sequence of the corresponding tree. The numbers must be separated by a space, and there must be no extra space at the end of each line. If it is impossible to reconstruct the unique tree from the given information, simply print "Impossible".

Sample Input 1:
9
3 - 2 1 7 9 - 4 6
9 - 5 3 2 1 - 6 4
3 1 - - 7 - 6 8 -
Sample Output 1:
3 5 2 1 7 9 8 4 6
9 7 5 3 2 1 8 6 4
3 1 2 5 7 4 6 8 9
9 7 8 5 6 3 2 4 1
Sample Input 2:
3
- - -
- 1 -
1 - -
Sample Output 2:
Impossible

此题给出的是一棵二叉树的三种遍历，然后挖了空要求还原，并且输出bfs的结果。

简单的说就是考虑暴力的递归求解即可，然后注意边界，顺便加一点剪枝就好了。

[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
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
#include<ctime>  
using namespace std;  
typedef unsigned long long ull;  
typedef long long LL;  
const int maxn = 1e2 + 10;  
const int INF = 0x7FFFFFFF;  
int n, ch[maxn][2], root = 0, f[maxn], cnt, flag, res;  
int a[maxn], b[maxn], c[maxn], fa[maxn], fb[maxn], fc[maxn], t[maxn];  
char s[5];  
  
int get()  
{  
  scanf("%s", s);  
  if (s[0] == '-') return 0;  
  int res = 0;  
  for (int i = 0; s[i]; i++) res = res * 10 + s[i] - '0';  
  return res;  
}  
  
bool dfs(int &x, int al, int ar, int bl, int br, int cl, int cr)  
{  
  if (al > ar) { x = 0; return true; }  
  for (int i = al; i <= ar; i++)  
  {  
    if (a[i] && b[bl] && a[i] != b[bl]) continue;  
    if (a[i] && c[cr] && a[i] != c[cr]) continue;  
    if (c[cr] && b[bl] && c[cr] != b[bl]) continue;  
    t[i] = max(a[i], max(b[bl], c[cr]));  
    if (fa[t[i]] && fa[t[i]] != i) continue;  
    if (fb[t[i]] && fb[t[i]] != bl) continue;  
    if (fc[t[i]] && fc[t[i]] != cr) continue;  
    x = i;   
    if (!dfs(ch[x][0], al, i - 1, bl + 1, bl + i - al, cl, cl + i - al - 1)) continue;  
    if (!dfs(ch[x][1], i + 1, ar, bl + 1 + i - al, br, cl + i - al, cr - 1)) continue;  
    return true;  
  }  
  return false;  
}  
  
void dfs(int x, int y)  
{  
  if (!x) return;  
  if (y == 2) { printf("%s%d", flag ? " " : "", t[x]); flag = 1; }  
  dfs(ch[x][0], y);  
  if (y == 1) { printf("%s%d", flag ? " " : "", t[x]); flag = 1; }  
  dfs(ch[x][1], y);  
  if (y == 3) { printf("%s%d", flag ? " " : "", t[x]); flag = 1; }  
}  
  
void bfs(int x)  
{  
  queue<int> p;  
  p.push(x);  
  while (!p.empty())  
  {  
    int q = p.front();  p.pop();  
    printf("%s%d", flag ? " " : "", t[q]); flag = 1;  
    if (ch[q][0]) p.push(ch[q][0]);  
    if (ch[q][1]) p.push(ch[q][1]);  
  }  
}  
  
int main()  
{  
  scanf("%d", &n);  
  for (int i = 1; i <= n; i++) a[i] = get(), f[a[i]]++, fa[a[i]] = i;  
  for (int i = 1; i <= n; i++) b[i] = get(), f[b[i]]++, fb[b[i]] = i;  
  for (int i = 1; i <= n; i++) c[i] = get(), f[c[i]]++, fc[c[i]] = i;  
  for (int i = 1; i <= n; i++) if (!f[i]){ cnt++; res = i; }  
  if (cnt > 1 || !dfs(root, 1, n, 1, n, 1, n)) printf("Impossible\n");  
  else  
  {  
    for (int i = 1; i <= n; i++) if (!t[i]) t[i] = res;  
    flag = 0; dfs(root, 1); putchar(10);  
    flag = 0; dfs(root, 2); putchar(10);  
    flag = 0; dfs(root, 3); putchar(10);  
    flag = 0; bfs(root); putchar(10);  
  }  
  return 0;  
}  


