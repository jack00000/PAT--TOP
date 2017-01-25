1011. Cut Rectangles (35)

时间限制
150 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
LIU, Rujia
When a rectangle is cut by a straight line, we can easily obtain two polygons as the result. But the reversed problem is harder: given two polygons, your task is to check whether or not they could be obtained by cutting a rectangle.

To give you more trouble, the input polygons are possibly moved, rotated (90 degrees, 180 degrees, or 270 degrees counter-clockwise), or even flipped (mirrored).

It is assumed that the original rectangle's edges are parallel to the axis.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N(<=20), and then N pairs of polygons are given. Each polygon is described in the format:

k x1 y1 ... xk yk

where k (2 < k <= 10) is the number of vertices on the polygon, and (xi, yi) (0 <= xi, yi <= 108) are the coordinates of the vertices, given in either clockwise or counter-clockwise order.

Note: there is no redundant vertex. That is, it is guaranteed that all the vertices are distinct for each polygon, and that no three consecutive vertices are on the same line.

Output Specification:

For each pair of polygons, print in a line either "YES" or "NO" as the answer.

Sample Input:
8
3 0 0 1 0 1 1
3 0 0 1 1 0 1
3 0 0 1 0 1 1
3 0 0 1 1 0 2
4 0 4 1 4 1 0 0 0
4 4 0 4 1 0 1 0 0
3 0 0 1 1 0 1
4 2 3 1 4 1 7 2 7
5 10 10 10 12 12 12 14 11 14 10
3 28 35 29 35 29 37
3 7 9 8 11 8 9
5 87 26 92 26 92 23 90 22 87 22
5 0 0 2 0 1 1 1 2 0 2
4 0 0 1 1 2 1 2 0
4 0 0 0 1 1 1 2 0
4 0 0 0 1 1 1 2 0
Sample Output:
YES
NO
YES
YES
YES
YES
NO
YES
简单来说题意就是说给你两个多边形，问是不是一条线划过矩形形成的。
总共有4种情况，两个三角形，两个四边形，一个三角形一个四边形，一个三角形一个五边形。
由于数据是按顺逆时针给出，也只有直角旋转的，所以除了两个矩形以为其他的都可以看作是三角形，然后判断三角形是否一样就好了。
[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
#include<cmath>  
#include<vector>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
typedef long long LL;  
int T,n,xx,yy;  
  
struct point  
{  
  LL x,y;  
  point(LL x=0,LL y=0):x(x),y(y){}  
  bool operator==(const point&a) const  
  {  
    return x==a.x||y==a.y;  
  }  
};  
  
LL dis(const point&a,const point&b)  
{  
  return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);  
}  
  
vector<point> a,b;  
vector<LL> x,y;  
  
bool check()  
{  
  x.clear();  y.clear();  
  int lena=a.size(),lenb=b.size(),flaga=0,flagb=0;  
  for (int i=0;i<lena;i++) flaga+=a[i]==a[(i+1)%lena];  
  for (int i=0;i<lenb;i++) flagb+=b[i]==b[(i+1)%lenb];  
  if (lena==4&&lenb==4&&flaga>=3&&flagb>=3&&flaga==flagb)  
  {  
    if (flaga==4)  
    {  
      for (int i=0;i<4;i++)   
      {  
        x.push_back(dis(a[i],a[(i+1)%4]));  
        y.push_back(dis(b[i],b[(i+1)%4]));  
      }  
      return x[0]==y[0]||x[0]==y[1]||x[1]==y[0]||x[1]==y[1];  
    }  
    else   
    {  
      for (int i=0;i<4;i++)   
      {  
        if (a[i]==a[(i+1)%4]) continue;  
        int x1=i,x2=(i+1)%4,x3=(i+2)%4,x4=(i+3)%4;  
        x.push_back(dis(a[x1],a[x2]));  
        LL k=sqrt(1.0*dis(a[x2],a[x3]))-sqrt(1.0*dis(a[x1],a[x4]));  
        x.push_back(k*k);  
        x.push_back(dis(a[x3],a[x4]));  
      }  
      for (int i=0;i<4;i++)   
      {  
        if (b[i]==b[(i+1)%4]) continue;  
        int x1=i,x2=(i+1)%4,x3=(i+2)%4,x4=(i+3)%4;  
        y.push_back(dis(b[x1],b[x2]));  
        LL k=sqrt(1.0*dis(b[x2],b[x3]))-sqrt(1.0*dis(b[x1],b[x4]));  
        y.push_back(k*k);  
        y.push_back(dis(b[x3],b[x4]));  
      }  
      return x==y;  
    }  
  }  
  if (lena!=3||flaga!=2) return false;  
  for (int i=0;i<3;i++) x.push_back(dis(a[i],a[(i+1)%3]));  
  if (lenb==3&&flagb==2) for (int i=0;i<3;i++) y.push_back(dis(b[i],b[(i+1)%3]));  
  if (lenb==4&&flagb==3)  
  {  
    for (int i=0;i<4;i++)   
    {  
      if (b[i]==b[(i+1)%4]) continue;  
      int x1=i,x2=(i+1)%4,x3=(i+2)%4,x4=(i+3)%4;  
      y.push_back(dis(b[x1],b[x2]));  
      LL k=sqrt(1.0*dis(b[x2],b[x3]))-sqrt(1.0*dis(b[x1],b[x4]));  
      y.push_back(k*k);  
      y.push_back(dis(b[x3],b[x4]));  
    }  
  }  
  if (lenb==5&&flagb==4)  
  {  
    for (int i=0;i<5;i++)   
    {  
      if (b[i]==b[(i+1)%5]) continue;  
      int x1=i,x2=(i+1)%5,x3=(i+2)%5,x4=(i+3)%5,x5=(i+4)%5;  
      y.push_back(dis(b[x1],b[x2]));  
      LL k=sqrt(1.0*dis(b[x2],b[x3]))-sqrt(1.0*dis(b[x4],b[x5]));  
      y.push_back(k*k);  
      k=sqrt(1.0*dis(b[x3],b[x4]))-sqrt(1.0*dis(b[x5],b[x1]));  
      y.push_back(k*k);  
    }  
  }  
  sort(x.begin(),x.end());  
  sort(y.begin(),y.end());  
  return x==y;  
}  
  
int main()  
{  
  scanf("%d",&T);  
  while (T--)  
  {  
    a.clear();  b.clear();  
    scanf("%d",&n); while (n--) {scanf("%d%d",&xx,&yy); a.push_back(point(xx,yy));}  
    scanf("%d",&n); while (n--) {scanf("%d%d",&xx,&yy); b.push_back(point(xx,yy));}  
    if (a.size()>b.size()) swap(a,b);  
    printf("%s\n",check()?"YES":"NO");  
  }  
  return 0;  
}  


