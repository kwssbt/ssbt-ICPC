template<typename T>
class Trie{
    int N;
    struct node{
        int p;
        vector<node*>nex;
        node():p(0),nex(2,nullptr){}
    };
    node*root;
public:
    Trie(int n):N(n){
        root=new node();
    }
    void add(T x){
        node*cur=root;
        for(int i=N-1;i>=0;--i){
            int j=(x>>i)&1;
            if(cur->nex[j]==nullptr)cur->nex[j]=new node();
            cur=cur->nex[j];
            cur->p++;
        }
    }
    void del(T x){
        node*cur=root;
        for(int i=N-1;i>=0;--i){
            int j=(x>>i)&1;
            cur=cur->nex[j];
            cur->p--;
        }
    }
    T query(T x){
        T y=0;
        node*cur=root;
        for(int i=N-1;i>=0;--i){
            int u=(x>>i)&1;
            int v=u^1;
            if(cur->nex[v]&&cur->nex[v]->p){
                y|=(v<<i);
                cur=cur->nex[v];
            }
            else{
                y|=(u<<i);
                cur=cur->nex[u];
            }
        }
        return x^y;
    } 
};
