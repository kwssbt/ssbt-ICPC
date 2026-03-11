#include<bits/stdc++.h>
using namespace std;

const int N=1e5;
bitset<N>isp;
vector<int>p;
 
void ehrlich(int n){
    isp.set();
    isp[0]=isp[1]=0;
    for(int i=2;i*i<=n;++i){
        if(isp[i]){
            p.push_back(i);
            for(int j=i*i;j<=n;j+=i){
                isp[j]=0;
            }
        }
    }
}

int ehrlich_cnt(int n){
    if(n<=1)return 0;
    vector<int>isp(n+1,1);
    int cnt=(n+1)/2;
    for(int i=3;i*i<=n;i+=2){
        if(isp[i]){
            for(int j=i*i;j<=n;j+=2*i){
                if(isp[j]){
                    isp[j]=0;
                    cnt--;
                }
            }
        }
    }
    return cnt;
}
 
void euler(int n){
    isp.set();
    isp[0]=isp[1]=0;
    for(int i=2;i<=n;++i){
        if(isp[i])p.push_back(i);
        for(int x:p){
            if(x*i>n)break;
            isp[x*i]=0;
            if(i%x==0)break;
        }
    }
}

