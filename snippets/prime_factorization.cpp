const int N = 10^7 +10;
vector<bool>isPrime(N,1);
vector<int>lp(N,0), hp(N,0);
int main()
{
    isPrime[0]=isPrime[1]=0;
    for(int i=2; i<N; ++i)
    {
        if(isPrime[i])
        {
            lp[i]=hp[i]=i;
            for(int j=2*i; j<N; j+=i)
            {
                isPrime[j]=0;
                hp[j]=i;
                if(lp[j]==0) lp[j]=i;
            }
        }
    }
    int num; cin>>num;
    unordered_map<int,int>prime_factors;
    while(num>1)
    {
        int prime_factor = hp[num];
        while(num % prime_factor == 0)
        {
            num /= prime_factor;
            prime_factors[prime_factor]++;
        }
    }
    for(auto factor:prime_factors)
        cout<<factor.first<<" "<<factor.second<<endl;
}
