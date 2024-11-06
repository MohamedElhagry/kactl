/**
 * Author: Mohamed ElHagry
 * Description: Left is the most significant digit
 */ 
const int p1 = 31, p2 = 37, MOD = 1e9 + 7;
const int N = 1e6 + 5;
int pw1[N], pw2[N];
ll powmod(ll x, ll y) {
    x %= MOD;
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}
ll add(ll a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
ll sub(ll a, ll b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
ll mul(ll a, ll b) { return a * b % MOD; }
ll inv(ll a) { return powmod(a, MOD - 2); }
void pre() {
    pw1[0] = 1;
    pw2[0] = 1;
    for (int i = 1; i < N; ++i) {
        pw1[i] = mul(pw1[i - 1], p1);
        pw2[i] = mul(pw2[i - 1], p2);
    }
}
struct Hash {
    vector<pi> h;
    int n;
    Hash(string &s) {
        n = s.size();
        h.resize(n);
        h[0].F = h[0].S = s[0] - 'a' + 1;
        for (int i = 1; i < n; ++i) {
            h[i].F = add(mul(h[i - 1].F, p1), s[i] - 'a' + 1);
            h[i].S = add(mul(h[i - 1].S, p2), s[i] - 'a' + 1);
        }
    }
    pi getRange(int l, int r) {
        assert(l <= r);
        assert(r < n);
        return {
                sub(h[r].F, mul(l ? h[l - 1].F : 0, pw1[r - l + 1])),
                sub(h[r].S, mul(l ? h[l - 1].S : 0, pw2[r - l + 1]))
        };
    }
};