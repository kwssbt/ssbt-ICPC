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

int dis[N]; // dis[u] = 起点到 u 的最短距离
bool in[N]; // in[u]=1 ：点 u 在队列中
void init(int n){
    for(int i=0;i<n;++i){
        in[i]=0;
        dis[i]=0x3f3f3f3f;
    }
}
void spfa(int start){
    queue<int>q;
    dis[start]=0;
    q.push(start);
    in[start]=1;
    while(q.size()){
        int u=q.front();
        q.pop();
        in[u]=0;
        for(int ei=head[u];ei!=-1;ei=nex[ei]){
            int v=to[ei];
            int w=weight[ei];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(in[v]==0){
                    q.push(v);
                    in[v]=1;
                }
            }
        }
    }
}

// 检查负环

int cnt[N]; // cnt[u] : 从起点到 u 的最短路上的边数

bool spfa_check(int s, int n){
    for(int i=0;i<n;++i){
        dis[i]=0x3f3f3f3f;
        in[i]=0;
        cnt[i]=0;
    }
    queue<int> q;
    q.push(s);
    in[s]=1;
    cnt[s]=0;
    dis[s]=0;
    while(q.size()){
        int u=q.front();
        q.pop();
        in[u] = 0;
        for(int ei=head[u];ei!=-1;ei=nex[ei]){
            int v=to[ei];
            int w=weight[ei];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>=n)return 1; // 有负环
                if(in[v]==0){
                    q.push(v);
                    in[v]=1;
                }
            }
        }
    }
    return 0; // 无负环
}
