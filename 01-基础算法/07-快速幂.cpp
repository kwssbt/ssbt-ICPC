#include<bits/stdc++.h>;
using namespace std;
//算数快速幂
typedef long long ll;
ll qpow(ll b,ll e){
    ll res=1;
    while(e){
        if(e&1)res*=b;
        b*=b;
        e>>=1;
    }
    return res;
}
ll qpow(ll b,ll e,ll p){
    b%=p;
    ll res=1;
    while(e){
        if(e&1)res=res*b%p;
        b=b*b%p;
        e>>=1;
    }
    return res;
}
//高精度
typedef __int128 i128;
i128 mul(i128 a,i128 b,i128 mod){
    a%=mod;
    i128 res=0;
    while(b){
        if(b&1)res=(res+a)%mod;
        a=(a<<1)%mod;
        b>>=1;
    }
    return res;
}
i128 qpow(i128 b,i128 e,i128 mod){
    b%=mod;
    i128 ans=1;
    while(e){
        if(e&1)ans=mul(ans,b,mod);
        b=mul(b,b,mod);
        e>>=1;
    }
    return ans;
}
//矩阵快速幂
vector<vector<ll>>mul(vector<vector<ll>>&A,vector<vector<ll>>&B,int n){
    vector<vector<ll>>C(n,vector<ll>(n));
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            for(int k=0;k<n;++k){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    return C;
}
vector<vector<ll>>qpow(vector<vector<ll>>b,int n,ll e){
    vector<vector<ll>>res(n,vector<ll>(n));
    for(int i=0;i<n;++i)res[i][i]=1;
    while(e){
        if(e&1){
            res=mul(res,b,n);
        }
        b=mul(b,b,n);
        e>>=1;
    }
    return res;
}
vector<vector<ll>>mul(vector<vector<ll>>&A,vector<vector<ll>>&B,int n,ll p){
    vector<vector<ll>>C(n,vector<ll>(n));
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            for(int k=0;k<n;++k){
                C[i][j]=(C[i][j]+A[i][k]*B[k][j])%p;
            }
        }
    }
    return C;
}
vector<vector<ll>>qpow(vector<vector<ll>>b,int n,ll e,ll p){
    vector<vector<ll>>res(n,vector<ll>(n));
    for(int i=0;i<n;++i)res[i][i]=1;
    while(e){
        if(e&1){
            res=mul(res,b,n,p);
        }
        b=mul(b,b,n,p);
        e>>=1;
    }
    return res;
}