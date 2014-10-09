//求三对角方程组
//b0 c0                x0   =   d0
//a1 b1 c1             x1   =   d1
//   a2 b2 c2          x2   =   d2
//      a3 b3 c3       x3   =   d3
//................................
//         an bn       xn   =   dn
void zhuigan(int n)
{
    B[0]=b[0];
    for (int i=0; i<=n; i++) {
        C[i]=c[i];
        if (i) {
            Aa[i]=a[i]/B[i-1];
            B[i]=b[i]-Aa[i]*C[i-1];
        }
    }
    y[0]=d[0];
    for (int i=1; i<=n; i++)
        y[i]=d[i]-Aa[i]*y[i-1];
    x[n]=y[n]/B[n];
    for (int i=n-1; i>=0; i--)
        x[i]=(y[i]-c[i]*x[i+1])/B[i];
}
