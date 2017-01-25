/* 
1005. Programming Pattern (35)

时间限制
600 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
HOU, Qiming
Programmers often have a preference among program constructs. For example, some may prefer "if(0==a)", while others may prefer "if(!a)". Analyzing such patterns can help to narrow down a programmer's identity, which is useful for detecting plagiarism.

Now given some text sampled from someone's program, can you find the person's most commonly used pattern of a specific length?

Input Specification:

Each input file contains one test case. For each case, there is one line consisting of the pattern length N (1<=N<=1048576), followed by one line no less than N and no more than 1048576 characters in length, terminated by a carriage return '\n'. The entire input is case sensitive.

Output Specification:

For each test case, print in one line the length-N substring that occurs most frequently in the input, followed by a space and the number of times it has occurred in the input. If there are multiple such substrings, print the lexicographically smallest one.

Whitespace characters in the input should be printed as they are. Also note that there may be multiple occurrences of the same substring overlapping each other.

Sample Input 1:
4
//A can can can a can.
Sample Output 1:
 can 4
Sample Input 2:
3
int a=~~~~~~~~~~~~~~~~~~~~~0;
Sample Output 2:
~~~ 19

此题求的是重复出现次数最多的长度为n的字串，要使用后缀数组，然后求出height数组，最长一段的连续大于n的就是答案

先放个hash的吧，应用了BKDR字符串hash，因为这个hash貌似基本是不会出现冲突的，成功AC了。

但是按道理来说，找字典序最小这种东西这样暴力跑的话是可能被卡住的，然而数据应该是水了可能。


[cpp] view plain copy
*/ 
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
typedef long long LL;  
const int maxn = 1e6 + 5e5;  
const int mod = 1e9 + 7;  
  
char s[maxn];  
int n, Hash[maxn], x, y, tot, ans, m;  
int cnt[maxn], t[maxn], a[maxn];  
  
int Inv(int x)  
{  
    if (x == 1) return 1;  
    return (LL)Inv(mod % x)*(mod - mod / x) % mod;  
}  
  
int main()  
{  
    scanf("%d", &n);  getchar();  
    gets(s + 1);  s[0] = 0;  x = 1; y = Inv(131);  
  
    for (int i = 1; i <= n; i++)  
    {  
        Hash[n] = ((LL)s[i] * x + Hash[n]) % mod;//BKDR 字符串hash  
        if (i < n) x = (LL)x * 131 % mod;  
    }  
    a[tot++] = Hash[n];  
    for (int i = n + 1; s[i]; i++)  
    {  
        Hash[i] = ((LL)(Hash[i - 1] - s[i - n] + mod) * y + (LL)s[i] * x) % mod;  
        a[tot++] = Hash[i];  
    }  
  
    sort(a, a + tot);   m = unique(a, a + tot) - a;  
  
    ans = 0;  
    for (int i = n; s[i]; i++)  
    {  
        x = lower_bound(a, a + m, Hash[i]) - a;  
        if (!t[x]) t[x] = i - n + 1;  
        ans = max(ans, ++cnt[x]);  
    }  
    x = 0;  
    for (int i = 0; i < m; i++)  
    {  
        if (cnt[i] == ans)  
        {  
            if (!x) x = t[i];  
            else  
            {  
                for (int j = 0; j < n; j++)  
                {  
                    if (s[x + j] > s[t[i] + j]) { x = t[i]; break; }  
                    if (s[x + j] < s[t[i] + j]) break;  
                }  
            }  
        }  
    }  
    for (int i = 0; i < n; i++) printf("%c", s[x + i]);  
    printf(" %d\n", ans);  
    return 0;  
}  
/*后缀数组的，搞不懂为啥自己重写了一遍倍增的就过了。。。
[cpp] view plain copy
#include<set>  
#include<map>  
#include<ctime>  
#include<cmath>  
#include<stack>  
#include<queue>  
#include<bitset>  
#include<cstdio>  
#include<string>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#include<functional>  
#define rep(i,j,k) for (int i = j; i <= k; i++)  
#define per(i,j,k) for (int i = j; i >= k; i--)  
using namespace std;  
typedef long long LL;  
const int low(int x) { return x&-x; }  
const double eps = 1e-8;  
const int INF = 0x7FFFFFFF;  
const int mod = 1e9 + 7;  
const int N = 1e6 + 5e4;  
int T, m;  
  
struct Sa  
{  
    char s[N];  
    int rk[2][N], sa[N], h[N], w[N], now, n;  
    int rmq[N][20], lg[N];  
  
    void GetS()  
    {  
        //scanf("%s", s + 1);  
        getchar();  
        gets(s + 1);  
        //gets_s(s + 1, N);  
    }  
  
    void getsa(int z, int &m)  
    {  
        int x = now, y = now ^= 1;  
        rep(i, 1, z) rk[y][i] = n - i + 1;  
        for (int i = 1, j = z; i <= n; i++)  
            if (sa[i] > z) rk[y][++j] = sa[i] - z;  
  
        rep(i, 1, m) w[i] = 0;  
        rep(i, 1, n) w[rk[x][rk[y][i]]]++;  
        rep(i, 1, m) w[i] += w[i - 1];  
        per(i, n, 1) sa[w[rk[x][rk[y][i]]]--] = rk[y][i];  
        for (int i = m = 0; i <= n; i++)  
        {  
            int *a = rk[x] + sa[i], *b = rk[x] + sa[i - 1];  
            rk[y][sa[i]] = *a == *b&&*(a + z) == *(b + z) ? m : ++m;  
        }  
    }  
  
    void getsa(int m)  
    {  
        now = 0; n = strlen(s + 1);  
        rep(i, 1, m) w[i] = 0;  
        rep(i, 1, n) w[s[i]]++;  
        rep(i, 1, m) rk[1][i] = rk[1][i - 1] + (bool)w[i];  
        rep(i, 1, m) w[i] += w[i - 1];  
        rep(i, 1, n) rk[0][i] = rk[1][s[i]];  
        rep(i, 1, n) sa[w[s[i]]--] = i;  
        for (int x = 1, y = rk[1][m]; x <= n && y < n; x <<= 1) getsa(x, y);  
        for (int i = 1, j = 0; i <= n; h[rk[now][i++]] = j ? j-- : 0)  
        while (s[sa[rk[now][i] - 1] + j] == s[i + j]) ++j;  
    }  
  
    void getrmq()  
    {  
        lg[1] = 0;  
        rep(i, 2, n) rmq[i][0] = h[i], lg[i] = lg[i >> 1] + 1;  
        for (int i = 1; (1 << i) <= n; i++)  
        {  
            rep(j, 2, n)  
            {  
                if (j + (1 << i) > n + 1) break;  
                rmq[j][i] = min(rmq[j][i - 1], rmq[j + (1 << i - 1)][i - 1]);  
            }  
        }  
    }  
  
    int lcp(int x, int y)  
    {  
        int l = min(rk[now][x], rk[now][y]) + 1, r = max(rk[now][x], rk[now][y]);  
        return min(rmq[l][lg[r - l + 1]], rmq[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]);  
    }  
  
    void work()  
    {  
        int b, t = 0;  
        for (int i = 2, j = 1; i <= n; i++)  
        {  
            if (h[i] >= m) j++; else j = 1;  
            if (t < j) t = j, b = sa[i - 1];  
        }  
        rep(i, 0, m - 1) printf("%c", s[b + i]);  
        printf(" %d\n", t);  
    }  
}sa;  
  
int main()  
{  
    scanf("%d", &m);  
    sa.GetS();  
    sa.getsa(256);  
    sa.work();  
    return 0;  
} */ 
