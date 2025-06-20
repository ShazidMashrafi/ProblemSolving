vector<ll> z_function(const string& s) {
	ll n = s.length();
	vector<ll> z(n);
	for (ll i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r) {
			z[i] = min(z[i-l], r-i+1);
		}
		while (i + z[i] < n and s[z[i]] == s[i+z[i]]) {
			++z[i];
		}
		if (i + z[i] - 1 > r) {
			l = i, r = i + z[i] - 1;
		}
	}
	return z;
}
