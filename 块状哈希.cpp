//#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
const int maxn = 100005;
const int hsize = 123;
int bsize, n, bnum, x[maxn];
struct Hash {
    int v,cnt;
    Hash *next;
};
struct hash_block
{
    int cls, sz;
    Hash p[hsize];
}b[350];
int hash(int k)
{
    return k%hsize;
}
int Min(int a, int b)
{
    if (a<=b) return a;
    return b;
}
void add(int id, int c, int num)
{
    int ha=hash(c);
    if (b[id].p[ha].next==NULL) {
        Hash *p=new Hash;
        p->next=NULL;
        p->v=c;
        p->cnt=num;
        b[id].p[ha].next=p;
        return ;
    }
    Hash *p=&b[id].p[ha];
    while (p->next!=NULL) {
        if (p->next->v==c) {
            p->next->cnt+=num;
            if (p->next->cnt==0) {
                Hash *del=p->next;
                p->next=del->next;
                delete del;
            }
            return ;
        }
        p=p->next;
    }
    p=new Hash;
    p->next=b[id].p[ha].next;
    p->v=c;
    p->cnt=num;
    b[id].p[ha].next=p;
}
int ask(int id, int c)
{
    int ha=hash(c);
    Hash *p=b[id].p[ha].next;
    while (p) {
        if (p->v==c) return p->cnt;
        p=p->next;
    }
    return 0;
}
void push_down(int id)
{
    if (b[id].cls==-1) return ;
    for (int i=id*bsize; i<id*bsize+b[id].sz; i++) x[i]=b[id].cls;
    for (int j=0; j<hsize; j++) {
            b[id].p[j].cnt=0;
            b[id].p[j].next=NULL;
            b[id].p[j].v=0;
        }
    add(id, b[id].cls, b[id].sz);
    b[id].cls=-1;
}
void initblock()
{
    bsize=(int)sqrt(n+1e-8);
    bnum=(n-1)/bsize+1;
    for (int i=0; i<bnum; i++) {
        for (int j=0; j<hsize; j++) {
            b[i].p[j].cnt=0;
            b[i].p[j].next=NULL;
            b[i].p[j].v=0;
        }
        b[i].cls=-1;
        b[i].sz=Min(i*bsize+bsize, n)-i*bsize;
    }
    for (int i=0; i<n; i++) {
        scanf("%d", &x[i]);
        add(i/bsize, x[i], 1);
    }
}
void update(int l, int r, int c)
{
    int lb=l/bsize, rb=r/bsize;
    for (int i=lb+1; i<rb; i++) b[i].cls=c;
    if (lb!=rb) {
        push_down(lb); push_down(rb);
        for (int i=l; i<lb*bsize+b[lb].sz; i++) {
            add(lb, x[i], -1);
            x[i]=c;
            add(lb, c, 1);
        }
        for (int i=rb*bsize; i<=r; i++) {
            add(rb, x[i], -1);
            x[i]=c;
            add(rb, c, 1);
        }
    } else {
        push_down(lb);
        for (int i=l; i<=r; i++) {
            add(lb, x[i], -1);
            x[i]=c;
            add(lb, c, 1);
        }
    }
}
int query(int l, int r, int c)
{
    int lb=l/bsize, rb=r/bsize, ans=0;
    for (int i=lb+1; i<rb; i++) {
        if (b[i].cls==c) ans+=b[i].sz;
        else if (b[i].cls==-1) ans+=ask(i, c);
    }
    if (lb!=rb) {
        push_down(lb); push_down(rb);
        for (int i=l; i<lb*bsize+b[lb].sz; i++) {
            ans+=(x[i]==c);
        }
        for (int i=rb*bsize; i<=r; i++) {
            ans+=(x[i]==c);
        }
    } else {
        push_down(lb);
        for (int i=l; i<=r; i++) {
            ans+=(x[i]==c);
        }
    }
    return ans;
}
int main()
{
    int m, l, r, z, a;
    while (scanf("%d%d", &n, &m)==2) {
        initblock();
        while (m--) {
            scanf("%d%d%d%d", &a, &l, &r, &z);
            if (a==1) update(l, r, z);
            else if (a==2) printf("%d\n", query(l, r, z));
        }
    }
    return 0;
}
