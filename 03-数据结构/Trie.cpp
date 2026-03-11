#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
class Trie{
    private:
    static const int N=1e7+5;
    int T[N][26+26+10];
    int pass[N];
    int end[N];
    int cnt=1;
    int get_index(char x){
        if(x>='0'&&x<='9')return x-'0';
        if(x>='a'&&x<='z')return x-'a'+10;
        return x-'A'+36;
    }
public:
    void add(string word){
        int cur=1;
        pass[cur]++;
        for(char x:word){
            int nex=get_index(x);
            if(T[cur][nex]==0){
                T[cur][nex]=++cnt;
            }
            cur=T[cur][nex];
            pass[cur]++;
        }
        end[cur]++;
    }
    int search(string word){
        int cur=1;
        for(char x:word){
            int nex=get_index(x);
            if(T[cur][nex]==0)return 0;
            cur=T[cur][nex];
        }
        return end[cur];
    }
    int pre_cnt(string pre){
        int cur=1;
        for(char x:pre){
            int nex=get_index(x);
            if(T[cur][nex]==0)return 0;
            cur=T[cur][nex];
        }
        return pass[cur];
    }
    void remove(string word){
        if(search(word)==0)return;
        int cur=1;
        for(char x:word){
            int nex=get_index(x);
            if(--pass[T[cur][nex]]==0){
                T[cur][nex]=0;
                return;
            }
            cur=T[cur][nex];
        }
        end[cur]--;
    }
    void clean(){
        for(int i=1;i<=cnt;++i){
            pass[i]=0;
            end[i]=0;
            memset(T[i],0,sizeof(T[0]));
        }
        cnt=1;
    }
};

class Trie{
    struct node{
        int pass;
        int end;
        vector<node*>nex;
        node():pass(0),end(0),nex(26+26+10,nullptr){}
        ~node(){
            for(auto n:nex){
                delete n;
            }
        }
    };
    int get_index(char x){
        if(x>='0'&&x<='9')return x-'0';
        if(x>='a'&&x<='z')return x-'a'+10;
        return x-'A'+36;
    }
    node*root;
    bool remove(string&s,node*cur,int idx){
        if(idx==s.size()){
            if(cur->end==0)return 0;
            cur->end--;
            cur->pass--;
            return 1;
        }
        int i=get_index(s[idx]);
        if(cur->nex[i]==nullptr)return 0;
        bool removed=remove(s,cur->nex[i],idx+1);
        if(removed){
            cur->pass--;
            if(cur->nex[i]->pass==0){
                delete cur->nex[i];
                cur->nex[i]=nullptr;
            }
        }
        return removed;
    }
public:
    Trie(){
        root=new node;
    }
    ~Trie(){
        delete root;
    }
    void add(string&s){
        node*cur=root;
        cur->pass++;
        for(char c:s){
            int i=get_index(c);
            if(cur->nex[i]==nullptr)cur->nex[i]=new node();
            cur=cur->nex[i];
            cur->pass++;
        }
        cur->end++;
    }
    int search(string&s){
        node*cur=root;
        for(char c:s){
            int i=get_index(c);
            if(cur->nex[i]==nullptr)return 0;
            cur=cur->nex[i];
        }
        return cur->end;
    }
    int pre_cnt(string&pre){
        node*cur=root;
        for(char c:pre){
            int i=get_index(c);
            if(cur->nex[i]==nullptr)return 0;
            cur=cur->nex[i];
        }
        return cur->pass;
    }
    void remove(string&s){
        if(search(s)==0)return;
        remove(s,root,0);
    }
    void clean(){
        delete root;
        root=new node();
    }
};