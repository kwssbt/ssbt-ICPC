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

int dis[N];
bool vis[N];
void init(int n){
    for(int i=0;i<n;++i){
        dis[i]=0x3f3f3f3f;
        vis[i]=0;
    }
}
void dijkstra(int start){
    // {w,u}
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    dis[start]=0;
    pq.push({0,start});
    while(pq.size()){
        auto [c,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int ei=head[u];ei!=-1;ei=nex[ei]){
            int v=to[ei];
            int w=weight[ei];
            int nc=c+w;
            if(dis[v]>nc){
                dis[v]=nc;
                pq.push({nc,v});
            }
        }
    }
}