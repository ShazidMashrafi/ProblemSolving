#include <bits/stdc++.h>
namespace debugger {
    using namespace std;
    template<typename T> concept Iter = requires(T x){begin(x);} && !is_same_v<remove_cvref_t<T>,string>;
    template<typename T> void p(T&& x) {
        using C = remove_cvref_t<T>;
        if constexpr(is_same_v<C,bool>) cerr << (x?"T":"F");
        else if constexpr(is_same_v<C,char>) cerr << '\'' << x << '\'';
        else if constexpr(is_same_v<C,string> || is_same_v<C,const char*>) cerr << '"' << x << '"';
        else if constexpr(Iter<T>) {
            cerr << '[';
            bool f = 0;
            for(auto&& e:x) {if(f)cerr << ','; f=1; p(e);}
            cerr << ']';
        }
        else if constexpr(requires{x.first;x.second;}) {cerr << '('; p(x.first); cerr << ','; p(x.second); cerr << ')';}
        else cerr << x;
    }
    template<typename T, typename... V> void pr(const char* s, T&& x, V&&... r) {
        int i=0, b=0;
        while(s[i] && (s[i]!=',' || b)) b+=(s[i]=='('||s[i]=='{'||s[i]=='<')-(s[i]==')'||s[i]=='}'||s[i]=='>'), i++;
        cerr.write(s,i) << " = "; p(x);
        if constexpr(sizeof...(r)) cerr << " | ", pr(s+i+1,forward<V>(r)...);
        else cerr << '\n';
    }
}

#define dbg(...) cerr << __LINE__ << ": ", debugger::pr(#__VA_ARGS__,__VA_ARGS__)