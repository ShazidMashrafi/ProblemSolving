ll lo = 0, hi = 1e18, ans = -1;

auto check = [&](ll mid) -> bool {
    return true;
};

while (lo <= hi) {
    ll mid = lo + (hi - lo) / 2;
    if (check(mid)) {
        ans = mid;
        hi = mid - 1;
    } else {
        lo = mid + 1;
    }
}
