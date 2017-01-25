1012. Greedy Snake (35)

时间限制
1000 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
LIU, Rujia
Have you ever played the game "Greedy Snake"? In the game, we control the movements of the snake to eat the fruits scattered in the game field, while the snake's body gets longer whenever it eats a fruit. The goal of the game is to make the snake eat as many fruits as possible, before its head has no where to Go. It would be a real challenge to let you program this game, right now.


But hey! Relax! This time you are only asked to program a simplified version of the game. In this simple version, the fruits are all over the place except at some extra obstacle cells. The snake's body will extend all the way along the path while it eats the fruits. You may take any fruit cell as the starting position of the snake. Then you have four directions to choose from: UP, DOWN, LEFT or RIGHT. Once you pick up a direction for the snake, it must keep going until it hits an obstacle or its own body. This procedure repeats until the head of the snake has no where to go -- that is, every adjacent cell of its head is either an obstacle or its own body. Your task is to minimize the number of fruits left.

For example, let's define the game field to be a 6 by 6 maze, surrounded by obstacle cells "#", with one extra obstacle "@". "S" is the starting position of the snake. All the fruits are represented by dots.

######
#..S@#
#....#
#....#
#....#
######
Then if you decide to move DOWN, RIGHT, and UP, the results are shown below.

######
#..*@#
#..*.#
#..*.#
#..S.#
######

######
#..*@#
#..*.#
#..*.#
#..*S#
######

######
#..*@#
#..*S#
#..**#
#..**#
######
Now the snake is stucked, the game is over, and there are 8 fruits left. However, by carefully changing your moves or choosing another starting position, you can actually control the snake to eat up all the fruits. Try it out!

Task 1: minimize the number of fruits left, and count the number of starting positions that can lead to the optimal solution.

Task 2: To make things more interesting, you may replace one fruit cell by an obstacle, to obtain a better result, and count the number of ways to add an obstacle that leads to the better result. In case there is no way to improve the result by adding one obstacle, you should point out this situation.

Input Specification:

Each input file contains one test case. For each case, the first line contains two integers N (4 <= N <= 15), the size of the game field, and K (0 <= K <= 2), the number of extra obstacles. Then K lines follow, each gives the coordinates of an obstacle in the format "xi yi" where 2 <= xi, yi<= N-1.

Output Specification:

For each case, print the results in two lines. In the first line print the minimal number of fruits left, and the number of different optimal starting positions. Then in the second line, either print -1 if there is no way to improve the result, or two integers: the better result and the number of optimal ways to add an obstacle.

Sample Input 1:
6 1
2 5
Sample Output 1:
0 4
-1
Sample Input 2:
6 2
2 2
3 3
Sample Output 2:
2 1
0 2

简单来说就是个搜索题，从每个点出发，必须一直走到不能再走才停下，用深搜遍历一遍，求出最大值即可，其他枚举一下。
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
#define loop(i,j,k) for (int i = j;i != -1; i = k[i])  
#define lson x << 1, l, mid  
#define rson x << 1 | 1, mid + 1, r  
#define ff first  
#define ss second  
#define mp(i,j) make_pair(i,j)  
#define pb push_back  
#define pii pair<int,LL>  
#define in(x) scanf("%d", &x);  
using namespace std;  
typedef long long LL;  
const int low(int x) { return x&-x; }  
const double eps = 1e-4;  
const int INF = 0x7FFFFFFF;  
const int mod = 998244353;  
const int N = 20;  
int n, m, f[N][N], x, y;  
int a[4] = { 1,-1,0,0 };  
int b[4] = { 0,0,1,-1 };  
  
int dfs(int x, int y)  
{  
    int res = 1;  
    rep(i, 0, 3)  
    {  
        int cnt = 1;  
        while (f[x + a[i] * cnt][y + b[i] * cnt]) cnt++;  
        if (cnt-- < 2) continue;  
        rep(j, 0, cnt - 1) f[x + a[i] * j][y + b[i] * j] = 0;  
        res = max(res, cnt + dfs(x + a[i] * cnt, y + b[i] * cnt));  
        rep(j, 0, cnt - 1) f[x + a[i] * j][y + b[i] * j] = 1;  
    }  
    return res;  
}  
  
int main()  
{  
    scanf("%d%d", &n, &m);  
    rep(i, 1, n) rep(j, 1, n) f[i][j] = 1 < i&&i < n && 1 < j&&j < n;  
    rep(i, 1, m) scanf("%d%d", &x, &y), f[x][y] = 0;  
    int ans = 0, cnt = 0;  
    rep(i, 1, n) rep(j, 1, n)  
    {  
        if (!f[i][j]) continue;  
        int res = dfs(i, j);  
        if (ans < res) ans = res, cnt = 1;  
        else cnt += ans == res;  
    }  
    printf("%d %d\n", (n - 2) * (n - 2) - m - ans, cnt);  
    int Ans = 0, Cnt = 0;  
    rep(i, 1, n) rep(j, 1, n)  
    {  
        if (!f[i][j]) continue;  
        int res = f[i][j] = 0;  
        rep(k, 1, n) rep(kk, 1, n)  
        {  
            if (!f[k][kk]) continue;  
            res = max(res, dfs(k, kk));  
        }  
        if (Ans < res) Ans = res, Cnt = 1;  
        else Cnt += res == Ans;  
        f[i][j] = 1;  
    }  
    if (Ans >= ans) printf("%d %d\n", (n - 2) * (n - 2) - m - Ans - 1, Cnt);  
    else printf("-1\n");  
    return 0;  
}
