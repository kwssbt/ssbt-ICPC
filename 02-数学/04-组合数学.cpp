#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;
const int MOD=1e9+7;

ll qpow(ll b,ll e){
    ll res=1;
    while(e){
        if(e&1)res=res*b%MOD;
        b=b*b%MOD;
        e>>=1;
    }
    return res;
}

ll f[N],inv[N];

void init(){
    f[0]=f[1]=1;
    for(int i=2;i<N;++i){
        f[i]=i*f[i-1]%MOD;
    }
    inv[N-1]=qpow(f[N-1],MOD-2);
    for(int i=N-1;i;--i){
        inv[i-1]=i*inv[i]%MOD;
    }
}

ll A(int n,int m){ //排列数
    if(n<0||m<0||n<m)return 0;
    return f[n]*inv[n-m]%MOD;
}

ll C(int n,int m){ //组合数
    if(n<0||m<0||n<m)return 0;
    return f[n]*inv[m]%MOD*inv[n-m]%MOD;
}

ll C_1(int n,int m){ //隔板：将n个元素分成m份(每份至少一个元素)
    if(m==0)return n==0?1:0;
    if(n<m)return 0;
    return C(n-1,m-1);
}