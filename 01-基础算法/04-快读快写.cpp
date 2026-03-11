#include<bits/stdc++.h>
using namespace std;

namespace IO{
    template<typename T>void read(T&x){
        x=0;bool f=0;
        char ch=getchar();
        while(ch<'0'||ch>'9'){
            if(ch=='-')f=1;
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            x=(x<<3)+(x<<1)+(ch^48);
            ch=getchar();
        }
        if(f)x=-x;
    }
    void read(string&s){
        s.clear();
        char ch=getchar();
        while(isspace(ch))ch=getchar();
        while(!isspace(ch)&&ch!=EOF){
            s+=ch;ch=getchar();
        }
    }
    template<typename T>void wr(T x){
        if(x==0){
            putchar('0');
            return;
        }
        if(x<0)putchar('-'),x=-x;
        char stk[20];
        int top=0;
        while(x)stk[++top]=x%10+'0',x/=10;
        while(top)putchar(stk[top--]);
    }
    void wr(const string &s){
        for(char c:s)putchar(c);
    }
    template<typename T>void wr(const T&x,char sep){
        wr(x);
        putchar(sep);
    }
    template<typename T,typename...Args>void read(T&first,Args&...rest){
        read(first);
        read(rest...);
    }
    void read(char &c){
        c=getchar();
        while(isspace(c))c=getchar();
    }
    void wr(const char c){
        putchar(c);
    }
    void wr(const char*s){
        while(*s)putchar(*s++);
    }
    template<typename T,typename...Args>void wr(const T&first, const Args&...rest){
        wr(first);
        ((putchar(' '),wr(rest)), ...);
    }
}using namespace IO;



namespace IO{
    char buf[1<<20],*p1=buf,*p2=buf;
    #define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
    template<typename type>inline void read(type&x){
        x=0;
        bool f(0);
        char ch=nc();
        if(ch==EOF)return;
        while(ch<'0'||ch>'9')f=ch=='-',ch=nc();
        while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=nc();
        f?x=-x:0;
    }
    template<typename T>void wr(T x){
        if(x==0){
            putchar('0');
            return;
        }
        if(x<0)putchar('-'),x=-x;
        char stk[20];
        int top=0;
        while(x)stk[++top]=x%10+'0',x/=10;
        while(top)putchar(stk[top--]);
    }
    void wr(const string &s){
        for(char c:s)putchar(c);
    }
    template<typename T>void wr(const T&x,char sep){
        wr(x);
        putchar(sep);
    }
    template<typename T,typename...Args>void read(T&first,Args&...rest){
        read(first);
        read(rest...);
    }
    void read(char &c){
        c=getchar();
        while(isspace(c))c=getchar();
    }
    void wr(const char c){
        putchar(c);
    }
    void wr(const char*s){
        while(*s)putchar(*s++);
    }
    template<typename T,typename...Args>void wr(const T&first, const Args&...rest){
        wr(first);
        ((putchar(' '),wr(rest)), ...);
    }
}using namespace IO;


