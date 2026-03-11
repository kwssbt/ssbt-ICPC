#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    int n;
    cin>>n;
    vector<int>arr(n);
    for(int i=0;i<n;++i)cin>>arr[i];
    sort(arr.begin(),arr.end());
    for(int x:arr)cout<<x<<' ';
}

int main(void){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    //cin>>T;
    while(T--)solve();
}