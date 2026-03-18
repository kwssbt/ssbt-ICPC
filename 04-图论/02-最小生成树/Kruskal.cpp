#include<bits/stdc++.h>
using namespace std;

// 0 ~ n-1

class UF{
    vector<int>fa;
    int cnt;
public:
    UF(int n):fa(n),cnt(n){
        for(int i=0;i<n;++i){
            fa[i]=i;
        }
    }
    int find(int x){
        return fa[x]==x?x:fa[x]=find(fa[x]);
    }
    bool merge(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b)return 0;
        fa[a]=b;
        cnt--;
        return 1;
    }
    int count(){
        return cnt;
    }
};

typedef long long T;

struct edge{
    int u,v;
    T w;
};

T kruskal(int n,vector<edge>&Edges){
    UF st(n);
    T sum=0;
    for(auto&[u,v,w]:Edges){
        if(st.merge(u,v)){
            sum+=w;
        }
    }
    if(st.count()==1){
        return sum;
    }
    return -1;
}