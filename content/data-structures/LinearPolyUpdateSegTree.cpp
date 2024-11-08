/**
 * Author: Hagry
 * Description: Allows updates of the form $a x + b$ on an arbitrary range
 */
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
int add(ll a, ll b) {
    a %= MOD, b %= MOD;
    a += b;
    if (a >= MOD) a -= MOD;
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
void normalize(ll &a) {
    while (a < 0)
        a += MOD;
}
struct Node {
    ll a, b;
    Node() {}
    Node(ll _a, ll _b) : a(_a), b(_b) { normalize(); }
    void normalize() {
        ::normalize(a);
        ::normalize(b);
    }
    bool operator==(const Node &other) {
        return a == other.a && b == other.b;
    }
    bool operator!=(const Node &other) {
        return a != other.a || b != other.b;
    }
};
ll sumTerms[N];
void pre(){
    for(int i =1; i <N; ++i){
        sumTerms[i] = i + sumTerms[i-1];
        if(sumTerms[i] >= MOD)
            sumTerms[i] -= MOD;
    }
}
struct SegTree {
    vector<ll> tree;
    vector<Node> lazy;
    int n;
    const ll IDN = 0;
    const Node LAZY_IDN = Node(0, 0);
    ll combine(ll a, ll b) {
        return add(a, b);
    }
    Node combineNodes(Node lt, Node rt) {
        return Node(add(lt.a, rt.a), add(lt.b, rt.b));
    }
    Node shiftNode(Node node, ll shift) {
        normalize(shift);
        node.b = add(node.b, mul(shift, node.a));
        node.normalize();
        return node;
    }
    void build(int inputN) {
        n = inputN;
        if (__builtin_popcount(n) != 1)
            n = 1 << (__lg(n) + 1);
        tree.resize(n << 1, IDN);
        lazy.resize(n << 1, LAZY_IDN);
    }
    void propagate(int k, int sl, int sr) {
        if (lazy[k] != LAZY_IDN) {
            tree[k] = add(tree[k], mul(lazy[k].a, sumTerms[sr - sl]));
            tree[k] = add(tree[k], mul(lazy[k].b, (sr - sl + 1)));
            if (sl != sr) {
                int mid = (sl + sr) / 2;
                lazy[k << 1] = combineNodes(lazy[k << 1], lazy[k]);
                lazy[k << 1 | 1] = combineNodes(lazy[k << 1 | 1],
                                                shiftNode(lazy[k], mid + 1 - sl));
            }
        }
        lazy[k].a = lazy[k].b = 0;
    }
    void update(int ql, int qr, Node v, int k, int sl, int sr) {
        propagate(k, sl, sr);
        if (qr < sl || sr < ql || ql > qr) return;
        if (ql <= sl && qr >= sr) {
            lazy[k] = v;
            propagate(k, sl, sr);
            return;
        }
        int mid = (sl + sr) / 2;
        update(ql, qr, v, k << 1, sl, mid);
        Node shiftedNode = shiftNode(v, mid + 1 - sl);
        update(ql, qr, shiftedNode, (k << 1) | 1, mid + 1, sr);
        tree[k] = combine(tree[k << 1], tree[k << 1 | 1]);
    }
    ll query(int ql, int qr, int k, int sl, int sr) {
        propagate(k, sl, sr);
        if (qr < sl || sr < ql || ql > qr) return IDN;
        if (ql <= sl && qr >= sr) return tree[k];
        int mid = (sl + sr) / 2;
        ll left = query(ql, qr, k << 1, sl, mid);
        ll right = query(ql, qr, k << 1 | 1, mid + 1, sr);
        return combine(left, right);
    }
    void update(int ql, int qr, Node node) {
        node = shiftNode(node, -ql);
        update(ql, qr, node, 1, 0, n - 1);
    }
    ll query(int ql, int qr) {
        return query(ql, qr, 1, 0, n - 1);
    }
};