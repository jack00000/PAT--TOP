1015. Letter-moving Game (35)

时间限制
200 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CAO, Peng
Here is a simple intersting letter-moving game. The game starts with 2 strings S and T consist of lower case English letters. S and T contain the same letters but the orders might be different. In other words S can be obtained by shuffling letters in String T. At each step, you can move one arbitrary letter in S either to the beginning or to the end of it. How many steps at least to change S into T?

Input Specification:

Each input file contains one test case. For each case, the first line contains the string S, and the second line contains the string T. They consist of only the lower case English letters and S can be obtained by shuffling T's letters. The length of S is no larger than 1000.

Output Specification:

For each case, print in a line the least number of steps to change S into T in the game.

Sample Input:
iononmrogdg
goodmorning
Sample Output:
8
Sample Solution:
(0) starts from iononmrogdg
(1) Move the last g to the beginning: giononmrogd
(2) Move m to the end: giononrogdm
(3) Move the first o to the end: ginonrogdmo
(4) Move r to the end: ginonogdmor
(5) Move the first n to the end: gionogdmorn
(6) Move i to the end: gonogdmorni
(7) Move the first n to the end: googdmornin
(8) Move the second g to the end: goodmorning

看似复杂的题目，其实如果换一个角度思考，其实是一道简单题。
不要从正面看，我们考虑把T串还原到S串，那么相当于把T串的两端删除一部分，重新填回去变成S串。
那么，只要保证，剩下的T串，可以在原来的S串中，找到对应的子序列，那么一定可以还原，
这样，答案就是删除掉的前后段的长度和。
为了效率，我们可以直接枚举剩余T串的起始位置，判断最长多少的剩余长度可以在S串中找到匹配。
这场顶级的压轴题意外的简单，只要能找到正确的思路。
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
const int N = 1e3 + 10;  
const int INF = 0x7FFFFFFF;  
char a[N], b[N];  
int f[N], n, mx;  
  
int main()  
{  
    while (scanf("%s%s", a + 1, b + 1) != EOF)  
    {  
        n = strlen(a + 1);  
        rep(i, 1, n)  
        {  
            for (int j = 1, k = i; j <= n; j++)  
            {  
                if (k <= n && a[j] == b[k]) k++;  
                mx = max(mx, k - i);  
            }  
        }  
        printf("%d\n", n - mx);  
    }  
    return 0;  
}  
