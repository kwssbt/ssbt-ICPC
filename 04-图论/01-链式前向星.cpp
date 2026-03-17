#include<bits/stdc++.h>
using namespace std;

const int N=1e5;
const int M=1e6;

typedef long long T;

int tot;
int head[N];
int nex[M];
int to[M];
T weight[M];

void init(int n){
    tot=0;
    memset(head,-1,sizeof(head));
}

void addEdge(int u,int v,T w){
    nex[tot]=head[u];
    to[tot]=v;
    weight[tot]=w;
    head[u]=tot++;
}