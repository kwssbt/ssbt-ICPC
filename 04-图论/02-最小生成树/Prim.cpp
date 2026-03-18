#include<bits/stdc++.h>
using namespace std;

// 0 ~ n-1

const int N=1e5;
const int M=1e6;

typedef long long T;

int tot;
int head[N];
int nex[M];
int to[M];
T weight[M];

T prim(int start,int n){
    // {w,u}
    priority_queue<pair<T,int>,vector<pair<T,int>>,greater<>>pq;
    vector<char>vis(n,0);
    T sum=0;
    int cnt=0;
    pq.push({0,start});
    while(pq.size()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=1;
        sum+=d;
        cnt++;
        if(cnt==n){
            return sum;
        }
        for(int ei=head[u];ei!=-1;ei=nex[ei]){
            int v=to[ei];
            if(!vis[v]){
                pq.push({weight[ei],v});
            }
        }
    }
    return -1;
}