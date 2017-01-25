1015. Letter-moving Game (35)

ʱ������
200 ms
�ڴ�����
65536 kB
���볤������
8000 B
�������
Standard
����
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

���Ƹ��ӵ���Ŀ����ʵ�����һ���Ƕ�˼������ʵ��һ�����⡣
��Ҫ�����濴�����ǿ��ǰ�T����ԭ��S������ô�൱�ڰ�T��������ɾ��һ���֣��������ȥ���S����
��ô��ֻҪ��֤��ʣ�µ�T����������ԭ����S���У��ҵ���Ӧ�������У���ôһ�����Ի�ԭ��
�������𰸾���ɾ������ǰ��εĳ��Ⱥ͡�
Ϊ��Ч�ʣ����ǿ���ֱ��ö��ʣ��T������ʼλ�ã��ж�����ٵ�ʣ�೤�ȿ�����S�����ҵ�ƥ�䡣
�ⳡ������ѹ��������ļ򵥣�ֻҪ���ҵ���ȷ��˼·��
[cpp] view plain copy ��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
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
