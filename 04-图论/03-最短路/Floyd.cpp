#include<bits/stdc++.h>
using namespace std;

// 0 ~ n-1

const int N=105;
const int INF=0x3f3f3f3f;

typedef long long T;

T dis[N][N];

void init(int n){
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(i==j)dis[i][j]=0;
            else dis[i][j]=INF;
        }
    }
}
void floyd(int n){
    for(int k=0;k<n;++k){
        for(int i=0;i<n;++i){
            if(i==k||dis[i][k]==INF)continue;
            for(int j=0;j<n;++j){
                if(j==k||dis[k][j]==INF)continue;
                if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
}
bool check(int n){
    // floyd(n);
    for(int i=0;i<n;++i){
        if(dis[i][i]<0){
            return 1; //有负环
        }
    }
    return 0; //无负环
}