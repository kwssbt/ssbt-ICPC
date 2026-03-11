template<typename T>class MonotonicQueue{
    deque<T>q,m,M;
    public:
    void push(T e){
        q.push_back(e);
        while(!m.empty()&&m.back()>e)m.pop_back();
        m.push_back(e);
        while(!M.empty()&&M.back()<e)M.pop_back();
        M.push_back(e);
    }
    T max(){return M.front();}
    T min(){return m.front();}
    T pop(){
        T x=q.front();
        q.pop_front();
        if(x==m.front())m.pop_front();
        if(x==M.front())M.pop_front();
        return x;
    }
    int size()const{return q.size();}
    bool empty()const{return q.size()==0;}
};