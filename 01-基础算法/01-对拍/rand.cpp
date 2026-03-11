#include <bits/stdc++.h>
using namespace std;
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>T get_rand(T l, T r) {
    uniform_int_distribution<T> dis(l, r);
    return dis(rng);
}


template<typename T>void pri(T l, T r) {
    uniform_int_distribution<long long> dis(l, r);
    cout<<dis(rng);
}

template<typename T>void pri(T l, T r, char op) {
    uniform_int_distribution<long long> dis(l, r);
    cout<<dis(rng)<<op;
}



template<typename T>void pri_arr(int len, T l, T r) {
    uniform_int_distribution<long long> dis(l, r);
    for (int i = 1; i < len; i++) {
    cout<<dis(rng)<<' ';
    }
    cout<<dis(rng)<<'\n';
}

int main() {
    //cout<<"1\n";
    int n=get_rand(100,6000);
    pri_arr(n,-100,100);
}