auto check = [&](int mid) -> bool {
        return false;
    };
int lo = 0, hi = n - 1, ans, target;
while(lo <= hi){
    int mid = lo + (hi - lo) / 2;
    if(check(mid)){
        ans = mid;
        hi = mid - 1;
    } else lo = mid + 1;
}
