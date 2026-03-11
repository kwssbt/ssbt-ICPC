typedef long long ll;
const int N=1e6+5;
const int P=1e9+7;
ll f[N],inv[N];
ll qpow(ll b,ll e){
    ll res=1;
    while(e){
        if(e&1)res=res*b%P;
        b=b*b%P;
        e>>=1;
    }
    return res;
}
void init(){
    f[0]=f[1]=1;
    for(int i=2;i<=N;++i){
        f[i]=i*f[i-1]%P;
    }
    inv[N]=qpow(f[N],P-2);
    for(int i=N;i;--i){
        inv[i-1]=i*inv[i]%P;
    }
}
ll C(int n,int m){//组合数
    if(n<0||m<0||n<m)return 0;
    return f[n]*inv[m]%P*inv[n-m]%P;
}
ll C_1(int n,int m){//隔板：将 n 个元素分成 m 份(每份至少一个元素)
    if(m==0)return n==0?1:0;
    if(n<m)return 0;
    return C(n-1,m-1);
}
ll A(int n,int m){//排列数
    if(n<0||m<0||n<m)return 0;
    return f[n]*inv[n-m]%P;
}