struct Point {
    ll x, y;
};

// 2 * Area (exact integer, / 2.0 for double)
ll poly_area2(auto& p) {
    ll area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return abs(area);
}
