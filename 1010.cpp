1010. Lehmer Code (35)

时间限制
300 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
LIU, Yaoting
According to Wikipedia: "In mathematics and in particular in combinatorics, the Lehmer code is a particular way to encode each possible permutation of a sequence of n numbers." To be more specific, for a given permutation of items {A1, A2, ..., An}, Lehmer code is a sequence of numbers {L1, L2, ..., Ln} such that Li is the total number of items from Ai to An which are less than Ai. For example, given {24, 35, 12, 1, 56, 23}, the second Lehmer code L2 is 3 since from 35 to 23 there are three items, {12, 1, 23}, less than the second item, 35.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<= 105). Then N distinct numbers are given in the next line.

Output Specification:

For each test case, output in a line the corresponding Lehmer code. The numbers must be separated by exactly one space, and there must be no extra space at the beginning or the end of the line.

Sample Input:
6
24 35 12 1 56 23
Sample Output:
3 3 1 0 1 0
其实就是求个逆序数而已，不过数字范围大了点，先离散化一下然后树状数组
[cpp] view plain copy
#include<iostream>  
#include<cstring>  
#include<algorithm>  
#include<cstdio>  
using namespace std;  
const int maxn = 1e5 + 10;  
const int low(int x){ return x&-x; }  
int n, a[maxn], b[maxn], c[maxn], d[maxn], f[maxn];  
  
bool cmp(const int &x, const int &y)  
{  
  return a[x] < a[y];  
}  
  
int get(int x)  
{  
  int ans = 0;  
  for (int i = x; i; i -= low(i)) ans += f[i];  
  return ans;  
}  
  
void add(int x)  
{  
  for (int i = x; i <= n; i += low(i)) f[i]++;  
}  
  
int main()  
{  
  scanf("%d", &n);  
  for (int i = 0; i < n; i++) scanf("%d", &a[i]), b[i] = i;  
  sort(b, b + n, cmp);  
  for (int i = 0; i < n; i++) c[b[i]] = i + 1;  
  for (int i = n - 1; i >= 0; i--)  
  {  
    d[i] = get(c[i]);  
    add(c[i]);  
  }  
  for (int i = 0; i < n; i++)  
  {  
    printf("%d", d[i]);  
    if (i == n - 1) printf("\n");  
    else printf(" ");  
  }  
  return 0;  
}  
