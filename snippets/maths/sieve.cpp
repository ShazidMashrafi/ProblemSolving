const int N = 1e7 + 10;
int spf[N];
vector<int> primes;

void sieve() {
    for (int i = 2; i < N; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p >= N) break;
            spf[i * p] = p;
        }
    }
}

vector<int> get_factors(int x) {
    vector<int> factors;
    while (x > 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }
    return factors;
}