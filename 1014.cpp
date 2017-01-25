1014. Circles of Friends (35)

时间限制
1000 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
A circle of friends is a network of friend relationships. If A is a friend of B, then B is considered a friend of A no matter B admits or not, and they are said to belong to the same circle. Here we assume that friendship is transitive, that is, if A is a friend of B, and B is a friend of C, then A is a friend of C and the three of them all belong to the same circle.

On the other hand, A is not so close to C as B is. We define the distance D(X, Y) between two friends X and Y as the minimum number of friends between them. For example, D(A, B) = 0, and D(C, A) = 1. The diameter of a friends circle is the maximum distance between any pair of friends in the circle.

Now given some people's relationships, you are supposed to find the number of friends circles and the circle with the largest diameter.

Input Specification:

Each input file contains one test case. For each case, the first line gives an integer N (2 <= N <= 1000), which is the total number of people involved, and hence they are numbered from 1 to N. Then N lines follow, each in the format:

k p1 ... pk

where k (0 <= k < min(10, N)) is the number of friends and p1 to pk (if k>0) are the friends' indices. The i-th line corresponds to the i-th person. All the numbers in a line are separated by spaces. It is guaranteed that no one is given as a friend of oneself.

Output Specification:

For each case, print in a line the number of friends circles, and the largest diameter, separated by exactly one space.

Sample Input:
17
2 15 12
1 17
2 16 9
1 8
4 10 13 15 14
0
2 11 14
1 4
2 2 3
2 13 11
2 15 7
2 1 14
2 5 15
0
0
1 3
1 2
Sample Output:
4 3

判断有几个联通块，同时求块里最远的最近距离,用邻接表存图，然后对于每个点都bfs一遍即可

[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
#include<cmath>  
#include<queue>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
#define ms(x,y) memset(x,y,sizeof(x))  
#define rep(i,j,k) for(int i=j;i<=k;i++)  
#define loop(i,j,k) for (int i=j;i!=-1;i=k[i])  
#define inone(x) scanf("%d",&x)  
#define intwo(x,y) scanf("%d%d",&x,&y)  
#define inthr(x,y,z) scanf("%d%d%d",&x,&y,&z)  
#define lson x<<1,l,mid  
#define rson x<<1|1,mid+1,r  
const int N = 1e5 + 10;  
const int INF = 0x7FFFFFFF;  
int n, x, y;  
int ft[N], nt[N], u[N], sz;  
int vis[N], f[N];  
  
int main()  
{  
    while (inone(n) != EOF)  
    {  
        rep(i, 1, n) ft[i] = -1;  
        rep(i, 1, n)  
        {  
            vis[i] = 0;  
            inone(x);  
            rep(j, 1, x)  
            {  
                inone(y);  
                u[sz] = y; nt[sz] = ft[i]; ft[i] = sz++;  
                u[sz] = i; nt[sz] = ft[y]; ft[y] = sz++;  
            }  
        }  
        int ans = 0, cnt = 0;  
        rep(i, 1, n)  
        {  
            queue<int> p; p.push(i);  
            if (!vis[i]) cnt++;  
            rep(j, 1, n) f[j] = 0; f[i] = 1;  
            while (!p.empty())  
            {  
                int q = p.front(); p.pop();  
                vis[q] = 1;  
                ans = max(ans, f[q] - 2);  
                loop(k, ft[q], nt)  
                {  
                    if (f[u[k]]) continue;  
                    p.push(u[k]); f[u[k]] = f[q] + 1;  
                }  
            }  
        }  
        printf("%d %d\n", cnt, ans);  
    }  
    return 0;  
}  

