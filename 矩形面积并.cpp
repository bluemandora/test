#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
const int maxn = 120005;
using namespace std;
int cnt[maxn<<2];
double t[maxn<<2], pos[maxn<<1];
struct line
{
    double l, r, h;
    int v;
}ln[maxn<<1];
void push_up(int l ,int r, int x)
{
    if (cnt[x]) t[x]=pos[r+1]-pos[l];
    else if (l==r) t[x]=0;
    else t[x]=t[x<<1]+t[x<<1|1];
}
void build(int l, int r, int x)
{
    t[x]=cnt[x]=0;
    if (l==r) return ;
    int mid=(l+r)>>1;
    build(l, mid, x<<1);
    build(mid+1, r, x<<1|1);
}
void change(int a, int b, int l, int r, int x, int num)
{
    if (a<=l&&b>=r){
        cnt[x]+=num;
        push_up(l, r, x);
        return ;
    }
    int mid=(l+r)>>1;
    if (a<=mid) change(a, b, l, mid, x<<1, num);
    if (b>mid) change(a, b, mid+1, r, x<<1|1, num);
    push_up(l, r, x);
}
bool cmp(line a, line b)
{
    return a.h<b.h;
}
int Find(int l, int r, double num)
{
    int mid;
    while (l<=r) {
        mid=(l+r)>>1;
        if (pos[mid]==num) return mid;
        else if(pos[mid]>num) r=mid-1;
        else l=mid+1;
    }
    return -1;
}
int main()
{
    int n, cas=0, m, l, r;
    double x1, x2, y1, y2, ans;
    while (scanf("%d", &n)==1 && n) {
        for (int i=0; i<n; i++) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            pos[i<<1]=x1; pos[i<<1|1]=x2;
            ln[i<<1].l=x1; ln[i<<1].r=x2; ln[i<<1].h=y1; ln[i<<1].v=1;
            ln[i<<1|1].l=x1; ln[i<<1|1].r=x2; ln[i<<1|1].h=y2; ln[i<<1|1].v=-1;
        }
        sort(pos, pos+2*n);
        sort(ln, ln+2*n, cmp);
        m=1;
        for (int i=1; i<2*n; i++)
            if (pos[i]!=pos[i-1])
                pos[m++]=pos[i];
        build(0, m-1, 1);
        ans=0;
        for (int i=0; i<2*n-1; i++) {
            l=Find(0, m-1, ln[i].l);
            r=Find(0, m-1, ln[i].r)-1;//-1不可少，对应push_up里的+1
            change(l, r, 0, m-1, 1, ln[i].v);
            ans+=t[1]*(ln[i+1].h-ln[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++cas, ans);
    }
    return 0;
}
 
