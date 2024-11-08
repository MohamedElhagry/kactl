/**
 * Author: Hagry
 * Description: Executes point update/ range queries both in O($\log(N)$) on arrays for invertible functions, can query prefix for all functions
*/

const int N = 1e5 + 5;
struct BIT {
    vector<ll> tree;
    BIT(int _n = N) {
        tree.resize(_n + 2);
    }
    ll get_prefix(int k) {
        ll ans = 0;
        while (k >= 1) {
            ans += tree[k];
            k -= k & -k;
        }
        return ans;
    }
    void update_point(int k, ll v) {
        while (k < tree.size()) {
            tree[k] += v;
            k += k & -k;
        }
    }
    ll query(int l, int r) {
        return get_prefix(r) - get_prefix(l - 1);
    }
    // binary search for first prefix with sum x
    int BS(ll x) {
        int pos = 0;
        for (int sz = (1 << __lg(tree.size())); sz > 0 && x; sz >>= 1) {
            if (pos + sz < tree.size() && tree[pos + sz] < x) {
                x -= tree[pos + sz];
                pos += sz;
            }
        }
        return pos + 1;
    }
};