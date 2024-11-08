/**
 * Author: Gamal
 * Description: Modular
 */
const int MOD = 998244353;
int add(ll a, ll b) {
    a %= MOD, b %= MOD;
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int sub(ll a, ll b) {
    a %= MOD, b %= MOD;
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
int mul(ll a, ll b) { return (a % MOD) * (b % MOD) % MOD; }
int powmod(ll x, ll y) {
    x %= MOD;
    int ans = 1;
    while (y) {
        if (y & 1) ans = mul(ans, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ans;
}
int inv(ll a) { return powmod(a, MOD - 2); }
