const int MAX_N = 100000;
const int LOG = 17;
int st[MAX_N][LOG + 1];
int logTable[MAX_N + 1];
int n;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
void buildSparseTable(vector<int>& arr) {
    n = arr.size();
    logTable[1] = 0;
    for (int i = 2; i <= n; i++) {
        logTable[i] = logTable[i / 2] + 1;
    }
    for (int i = 0; i < n; i++) {
        st[i][0] = arr[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int queryGCD(int L, int R) {
    int j = logTable[R - L + 1];
    return gcd(st[L][j], st[R - (1 << j) + 1][j]); 
}
