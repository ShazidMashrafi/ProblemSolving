struct Point {
    ll x, y;
    bool operator<(Point o) const { return x == o.x ? y < o.y : x < o.x; }
    bool operator==(Point o) const { return x == o.x && y == o.y; }
};

ll cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

struct Hull {
    vector<Point> h;

    Hull(auto pts) { // Monotone Chain
        int n = pts.size(), k = 0;
        if (n <= 2) { h = pts; return; }
        h.resize(2 * n);
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        n = pts.size();

        for (int i = 0; i < n; ++i) {
            while (k >= 2 && cross(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
            h[k++] = pts[i];
        }
        for (int i = n - 2, t = k + 1; i >= 0; --i) {
            while (k >= t && cross(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
            h[k++] = pts[i];
        }
        h.resize(k - 1);
    }
};