/* notes: 
1. modifies string by adding '#' bef&after every char;
2. p[i] = size of palindrome that exist in original string; here i is the center of that palindrome of modified string;
3. palindrome at ith(modified string's) position is: s.substr((index/2) - (pal_size/2), pal_size);
*/
struct Manachers { // O(n)
    vector<int> p;
    string s;
    Manachers(string &_s) {
        s = "#";  // build new string
        for(int i = 0; i < size(_s); i++) {
            s.push_back(_s[i]);  s.push_back('#');
        }
        int n = size(s);
        p.assign(n, 0);
        int l = 0, r = 0; //curr largest pal range
        for(int i = 0; i < n; i++) {
            int mirror = l + (r - i);
            if (i < r)  p[i] = min(r - i, p[mirror]);
            while(i + p[i] + 1 < n && i - p[i] - 1 >= 0 && s[i + p[i] + 1] == s[i - p[i] - 1]) {
                p[i]++;
            }
            if(i + p[i] > r) {  // if new largest pal found
                l = i - p[i]; r = i + p[i];
            }
        }
    }
    bool is_palindrome(int l, int r) { // O(1)
        l = 2 * l + 1; r = 2 * r + 1;
        int center = (l + r) / 2; // of modified string
        return p[center] >= (r - l + 1) / 2;
    }
};
