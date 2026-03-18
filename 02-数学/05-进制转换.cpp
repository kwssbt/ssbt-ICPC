#include<bits/stdc++.h>
using namespace std;


namespace X_to_Y{
    char dtoc(int d){
        if(d>9)return 'A'+d-10;
        return '0'+d;
    }
    int ctod(char c){
        if(c>'a')return c-'a'+10;
        if(c>='A')return c-'A'+10;
        return c-'0';
    }
    long long pos_to_ten(string num,int x){
        long long t=0;
        for(char c:num){
            t=t*x+ctod(c);
        }
        return t;
    }
    long long neg_to_ten(string num,int x) {
        long long t=0;
        long long b=1;
        for(int i=num.size()-1;i>=0;i--){
            t+=ctod(num[i])*b;
            b*=x;
        }
        return t;
    }
    string ten_to_y(long long t,int y){
        if(t==0)return "0";
        string ans="";
        while(t){
            int d=t%y;
            t/=y;
            if(d<0){
                d+=-y;
                t++;
            }
            ans=dtoc(d)+ans;
        }
        return ans;
    }
    string x_to_y(string num,int x,int y){
        if(num=="0")return num;
        long long t=(x<0)?neg_to_ten(num,x):pos_to_ten(num,x);
        return ten_to_y(t,y);
    }
}using namespace X_to_Y;



