#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int inf = 1e9+7;
const double eps = 1e-7;
const int maxn = 305;
struct Matrix
{
    int sz;
    ll mat[105][105];
    void clear() {memset(mat, 0, sizeof(mat));}
    friend void operator*=(Matrix &a, Matrix b)
    {
        Matrix ret;
        ret.clear(); ret.sz=a.sz;
        for (int i=0; i<a.sz; i++)
        for (int k=0; k<a.sz; k++) {
            if (!a.mat[i][k]) continue;
            for (int j=0; j<a.sz; j++)
                ret.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
        }
        a=ret;
    }
}A, E, ans;
void pow_mod(Matrix &a, int b)
{
    Matrix ret, tmp; ret.clear(); tmp.clear();
    ret.sz=a.sz; tmp.sz=a.sz;
    for (int i=0; i<a.sz; i++)
        for (int j=0; j<a.sz; j++) {
            tmp.mat[i][j]=a.mat[i][j];
            ret.mat[i][i]=1;
        }
    while (b) {
        if (b&1) ret*=tmp;
        tmp*=tmp;
        b>>=1;
    }
    a=ret;
}
int one[maxn], add[maxn];
int main() {
    E.clear();
    for (int i=0; i<101; i++)
        E.mat[i][i]=1;
    int n, m, k, x, y;
    char op;
    while (scanf("%d%d%d", &n, &m, &k)==3&&(n||m||k)) {
        A.clear();
        for (int i=0; i<=n; i++) {
            A.mat[i][i]=1;
        }
        while (k--) {
            scanf(" %c", &op);
            if (op=='s') {
                scanf("%d%d", &x, &y);
                x--; y--;
                for (int i=0; i<=n; i++)
                    swap(A.mat[x][i], A.mat[y][i]);
            } else {
                scanf("%d", &x);
                x--;
                if (op=='e') {
                    for (int i=0; i<=n; i++)
                        A.mat[x][i]=0;
                } else {
                    A.mat[x][n]++;
                }
            }
        }
        A.sz=n+1;
        pow_mod(A, m);
        for (int i=0; i<n; i++) {
            printf("%I64d", A.mat[i][n]);
            if (i==n-1) printf("\n");
            else printf(" ");
        }
    }
    return 0;
}
