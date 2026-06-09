bool prime_check(int n) {
    if(n<2) return false;
    else if(n <4) return true;
    else if(!(n&1)) return false;
    else {
        for(int i = 3; i*i<=n; i+= 2) {
            if(n%i==0) return false;
        }
        return true;
    }
}
