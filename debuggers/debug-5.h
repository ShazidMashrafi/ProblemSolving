#include <bits/stdc++.h>
using namespace std;

void dbg_out() { cerr << endl; }

void debug(bool x) { cerr << (x ? "true" : "false"); }
void debug(char x) { cerr << '\'' << x << '\''; }
void debug(const string &x) { cerr << '"' << x << '"'; }
void debug(const char *x) { cerr << '"' << x << '"'; }

template<size_t N>
void debug(const char (&x)[N]) { cerr << '"' << x << '"'; }

template<typename T>
requires (requires(const T &x) { cerr << x; } && !requires(const T &x) { std::begin(x); })
void debug(const T &x) { cerr << x; }

template<typename A, typename B>
void debug(const pair<A, B> &p) {
    cerr << '('; debug(p.first); cerr << ", "; debug(p.second); cerr << ')';
}

template<typename... T>
void debug(const tuple<T...> &t) {
    cerr << '(';
    int f = 0;
    apply([&f](auto... args) { ((cerr << (f++ ? ", " : ""), debug(args)), ...); }, t);
    cerr << ')';
}

template<typename T>
requires (requires(const T &x) { std::begin(x); } && !is_same_v<T, string>)
void debug(const T &x) {
    cerr << '{';
    bool f = 0;
    for (const auto &i : x) {
        if (f) cerr << ", ";
        f = 1;
        debug(i);
    }
    cerr << '}';
}

template<typename T>
requires requires(T x) { x.pop(); }
void debug(T x) {
    cerr << '{';
    bool f = 0;
    while (!x.empty()) {
        if (f) cerr << ", ";
        f = 1;
        if constexpr (requires { x.top(); }) {
            debug(x.top());
        } else {
            debug(x.front());
        }
        x.pop();
    }
    cerr << '}';
}

template<typename Head, typename... Tail>
void dbg_out(const Head &H, const Tail &... T) {
    debug(H);
    if (sizeof...(T)) cerr << ", ";
    dbg_out(T...);
}

#define dbg(...) cerr << #__VA_ARGS__ << " = ", dbg_out(__VA_ARGS__)
