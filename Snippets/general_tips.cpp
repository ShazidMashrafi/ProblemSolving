bool cmp(pair<int,int> x, pair<int,int> y) {
    if (x.first == y.first) {
        return (x.second < y.second);
    }
    return (x.first < y.first);
}
