template<class>
class UF{
    vector<int>siz,fa;
    int cnt;
public:
    UF(int n):cnt(n),fa(n),siz(n){
        for(int i=0;i<n;++i){
            fa[i]=i;
            siz[i]=1;
        }
    }
    int find(int x){
        return x==fa[x]?x:fa[x]=find(fa[x]);
    }
    bool check(int a,int b){
        return find(a)==find(b);
    }
    bool merge(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b)return 0;
        if(siz[a]>siz[b]){
            fa[b]=a;
            siz[a]+=siz[b];
        }
        else{
            fa[a]=b;
            siz[b]+=siz[a];
        }
        cnt--;
        return 1;
    }
    int count(){
        return cnt;
    }
    int size(int x){
        return siz[find(x)];
    }
};