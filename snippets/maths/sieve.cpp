struct Sieve {
    vector<int> spf, primes;

    Sieve(int n = 1e7 + 10) : spf(n, 0) {
        for (int i = 2; i < n; ++i) {
            if (!spf[i]) {
                spf[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > spf[i] || 1LL * i * p >= n) break;
                spf[i * p] = p;
            }
        }
    }

    vector<int> factors(int x) {
        vector<int> res;
        while (x > 1) {
            res.push_back(spf[x]);
            x /= spf[x];
        }
        return res;
    }
};