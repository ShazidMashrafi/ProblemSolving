const int N = 1e7 +10;
vector<bool>isPrime(N,1);
void sieve()
{
    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i * i < N; ++i) {
        if(isPrime[i])
            for(int j = i * i; j < N; j += i) isPrime[j] = false;
    }
}