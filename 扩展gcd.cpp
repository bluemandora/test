#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#define ll long long
using namespace std;
ll extend_gcd(ll a, ll b, ll &x, ll &y)//扩展欧几里得
{
    ll tmp, i;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i = extend_gcd(b, a % b, x, y);
    tmp = x;
    x = y;
    y = tmp - a / b*y;
    return i;
}
void modular_equation(ll a,ll b,ll c)//ax = c(mod b) ,ax+by=c
{
    ll gcd;
    ll x,y;
    gcd = extend_gcd(a,b,x,y);
    if ( c % gcd != 0 )
		printf("Impossible\n");
    else
    {
		x = (x * c/gcd) % b ;// 第一次求出的x ;
		ll t = b/gcd;
		if (t<0) t=-t;
		x = (x%t + t)%t;
		printf("%I64d\n",x);//最小的正数的值
		//for (int i=0;i<d;i++)
			//printf("The %dth answer is : %ld\n",i+1,(x+i*(b/d))%b); //所有的正数值
    }
}
