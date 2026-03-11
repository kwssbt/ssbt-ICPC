#include<bits/stdc++.h>
using namespace std;

typedef __int128 i128;

istream &operator>>(istream &is, __int128 &n) {
    string s;
    is >> s;
    n = 0;
    int sign = 1;
    int i = 0;
    if (s[0] == '-') {
        sign = -1;
        i = 1;
    }
    for (; i < (int)s.size(); i++) {
        n = n * 10 + (s[i] - '0');
    }
    n *= sign;
    return is;
}

i128 p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43};//k = 14

i128 mul(i128 a,i128 b,i128 mod){//龟速乘(防溢出)
    i128 res=0;
    a%=mod;
    while(b){
        if(b&1)res=(res+a)%mod;
        a=(a<<1)%mod;
        b>>=1;
    }
    return res;
}

i128 qpow(i128 b,i128 e,i128 mod){
    i128 ans=1;
    b%=mod;
    while(e){
        if(e&1)ans=mul(ans,b,mod);
        b=mul(b,b,mod);
        e>>=1;
    }
    return ans;
}
bool mii128er_rabin(i128 n){
    if(n<3||n%2==0)return n==2;
    i128 u=n-1,t=0;
    while(u%2==0)u/=2,++t;
    for(auto a:p){
        if(n==a)return 1;
        if(n%a==0)return 0;
        i128 v=qpow(a,u,n);
        if(v==1)continue;
        i128 s=1;
        for(;s<=t;++s){
            if(v==n-1)break;
            v=mul(v,v,n);
        }
        if(s>t)return 0;
    }
    return 1;
}