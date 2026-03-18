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

T dis[N];
bool in[N];

void spfa(int start){
    memset(dis,0x3f,sizeof(dis));
    memset(in,0,sizeof(in));
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
            T w=weight[ei];
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

int cnt[N]; //cnt[u]:从起点到u的最短路上的边数

bool spfa_check(int s, int n){
    memset(dis,0x3f,sizeof(dis));
    memset(cnt,0,sizeof(cnt));
    memset(in,0,sizeof(in));
    queue<int> q;
    q.push(s);
    dis[s]=0;
    cnt[s]=0;
    in[s]=1;
    while(q.size()){
        int u=q.front();
        q.pop();
        in[u]=0;
        for(int ei=head[u];ei!=-1;ei=nex[ei]){
            int v=to[ei];
            T w=weight[ei];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;
                
                if(cnt[v]>=n)return 1; //有负环
                
                if(in[v]==0){
                    q.push(v);
                    in[v]=1;
                }
            }
        }
    }
    return 0; //无负环
}
