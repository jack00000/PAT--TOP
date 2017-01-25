Image segmentation is usually formulated as a graph partition problem, where each segment corresponds to a connected component. Moreover, each pixel is the vertex of the graph. Each edge has a weight, which is a non-negative dissimilarity between neighboring pixels. So, the goal of image segmentation is to decompose the image graph into several disconnected components, where the elements in a component are similar and the elements in the different components are dissimilar.

The components are defined as follows:

A component is made of a set of connected vertices;
Any two components have no shared vertices;
The dissimilarity D(C1, C2) of any two components C1 and C2 is larger than the confidence H of any of C1 and C2.
The dissimilarity D(C1, C2) is defined to be the minimum edge weight of all the edges connecting C1 and C2, or infinity if no such edge exists;
The confidence of a component C, H(C), is defined to be the maximum edge weight of the minimum spanning tree of C, plus a function f(C) = c/|C| where c is a positive constant and |C| is the size of the component C;
A set of vertices must not be treated as a component if they can be partitioned into two or more components.
Your job is to write a program to list all the components.

Input Specification:

Each input file contains one test case. For each case, the first line contains three integers: Nv (0 < Nv <=1000), the total number of vertices (and hence the vertices are numbered from 0 to Nv-1); Ne, the total number of edges; and c, the constant in the function f(C). Then Ne lines follow, each gives an edge in the format:

V1 V2 Weight

Note: it is guaranteed that each pixel has no more than 8 neighboring pixels. The constant and all the weights are positive and are no more than 1000.

Output Specification:

For each case, list each component in a line. The vertices in a component must be printed in increasing order, separated by one space with no extra space at the beginning or the end of the line. The components must be listed in increasing order of their first vertex.

Sample Input 1:
10 21 100
0 1 10
0 3 60
0 4 90
1 2 90
1 3 50
1 4 200
1 5 86
2 4 95
2 5 5
3 4 95
3 6 15
3 7 101
4 5 500
4 6 100
4 7 101
4 8 101
5 7 300
5 8 50
6 7 90
7 8 84
7 9 34
Sample Output 1:
0 1 3 6
2 5 8
4
7 9
Sample Input 2:
7 7 100
0 1 10
1 2 61
2 3 50
3 4 200
4 5 82
5 0 200
3 6 90
Sample Output 2:
0 1
2 3 6
4 5
题面有点恶心，对于我这种英语水平弱渣到不行的人来说简直就是读题比写题难啊。拖了好久的题了，之前一直不是很理解样例二怎么来的，现在拿起来猜了猜，竟然猜对了。
简单解释一下题意吧，给你一个图，和一些有边权的边，要你分块，每个分块自身有一个H=最小生成树的最大边+常数C/块内的点数，
要求，任意两个分块之间最小的连接边的长度要大于一个分块的H（随便哪个都行，这个地方理解看题目any of）,
我的做法就是，把所有边按权值排序，一条一条加入，判断是否需要这条边，不用就不加。然后就分完块了，排个序输出就好了。
正确性的话，想想应该是对的，证明就略了吧。
[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
#include<cmath>  
#include<vector>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
#define rep(i,j,k) for(int i=j;i<=k;i++)  
#define loop(i,j,k) for (int i=j;i!=-1;i=k[i])  
#define inone(x) scanf("%d",&x)  
#define intwo(x,y) scanf("%d%d",&x,&y)  
#define inthr(x,y,z) scanf("%d%d%lf",&x,&y,&z)  
const int N = 1e5+ 10;  
const double INF = 1e18;  
int n, m;  
int fa[N], c[N];  
double s[N], C;  
vector<int> p[N];  
  
struct point  
{  
    int x, y;  
    double z;  
    bool operator<(const point&a)const { return z < a.z; }  
}a[N];  
  
int get(int x)   
{   
    if (x == fa[x]) return x;  
    fa[x] = get(fa[x]);  
    c[fa[x]] += c[x]; c[x] = 0;  
    return fa[x];  
}  
  
bool cmp(vector<int> a,vector<int> b)  
{  
    if (!a.size() && b.size()) return true;  
    if (b.size() == 0) return false;  
    return a[0] < b[0];  
}  
  
int main()  
{  
    while (inthr(n, m, C) != EOF)  
    {  
        rep(i, 0, n - 1) s[i] = 0, c[i] = 1, fa[i] = i;  
        rep(i, 0, n - 1) p[i].clear();  
        rep(i, 1, m) inthr(a[i].x, a[i].y, a[i].z);  
        sort(a + 1, a + m + 1);  
        rep(i, 1, m)  
        {  
            int fx = get(a[i].x), fy = get(a[i].y);  
            if (fx == fy) continue;  
            if (fx < fy) swap(fx, fy);  
            if (s[fx] + C / c[fx] < a[i].z) continue;  
            if (s[fy] + C / c[fy] < a[i].z) continue;  
            fa[fx] = fy; get(fx); s[fy] = a[i].z;  
        }  
        rep(i, 0, n - 1) p[get(i)].push_back(i);  
        rep(i, 0, n - 1) sort(p[i].begin(), p[i].end());  
        sort(p, p + n, cmp);  
        rep(i, 0, n - 1)  
        {  
            if (p[i].size())  
            {  
                for (int j = 0; j < p[i].size(); j++)  
                {  
                    printf("%s%d", j ? " " : "", p[i][j]);  
                }  
                putchar(10);  
            }  
        }  
    }  
    return 0;  
}  


