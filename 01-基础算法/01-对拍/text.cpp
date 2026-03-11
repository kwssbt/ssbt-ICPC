#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int partition(vector<int>&arr,int l,int r,int x){
    while(1){
        while(l<=r&&arr[l]<x)++l;
        while(l<=r&&arr[r]>x)--r;
        if(l>r)break;
        swap(arr[l++],arr[r--]);
    }
    return l-1;
}
void quick_sort(vector<int>&arr,int l,int r){
    if(l>=r){
        return;
    }
    int x=arr[l+rand()%(r-l+1)];
    int mid=partition(arr,l,r,x);
    quick_sort(arr,l,mid);
    quick_sort(arr,mid+1,r);
}
void solve(){
    int n;
    cin>>n;
    vector<int>arr(n);
    for(int i=0;i<n;++i)cin>>arr[i];
    quick_sort(arr,0,n-1);
    //sort(arr.begin(),arr.end());
    for(int x:arr)cout<<x<<' ';
}

int main(void){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    //cin>>T;
    while(T--)solve();
}