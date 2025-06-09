vector<int> fact(101, 0), factinv(101, 0);
int md = 998244353;
int genfact(int n) {if(!n)return 1;return fact[n]?fact[n]:fact[n]=n*genfact(n-1)%md;}
int genfactinv(int n){if(!n)return 1;return factinv[n]?factinv[n]:factinv[n]=power(genfact(n),md-2);}
int ncrmod(int n, int r) {return (genfact(n) * genfactinv(r) % md) * genfactinv(n - r) % md; }
int nprmod(int n, int r) {return genfact(n) * genfactinv(n - r) % md; }
