double ternary_search_real(double l, double r) {
    for (int iter = 0; iter < 100; ++iter) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) r = m2; // > for max
        else l = m1;
    }
    return l;
}

ll ternary_search_int(ll l, ll r) {
    while (r - l >= 3) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) r = m2; // > for max
        else l = m1;
    }
    ll opt = l;
    for (ll i = l + 1; i <= r; ++i) {
        if (f(i) < f(opt)) opt = i; // > for max
    }
    return opt;
}