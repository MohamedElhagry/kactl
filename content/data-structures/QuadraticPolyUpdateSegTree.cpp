/**
 * Author: Hagry
 * Description: Allows updates of the form $a x^2 + b x + c$ on an arbitrary range
 */
const ll MOD = 1e9 + 7;
void normalize(ll &a) {
    while (a < 0)
        a += MOD;
}
struct Node {
    ll a, b, c;
    Node() {}
    Node(ll _a, ll _b, ll _c) : a(_a), b(_b), c(_c) {
        normalize();
    }
    void normalize() {
        ::normalize(a);
        ::normalize(b);
        ::normalize(c);
    }
    bool operator==(const Node &other) {
        return a == other.a && b == other.b && c == other.c;
    }
    bool operator!=(const Node &other) {
        return a != other.a || b != other.b || c != other.c;
    }
};
int add(ll a, ll b) {
    assert(a >= 0);
    assert(b >= 0);
    a %= MOD, b %= MOD;
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
int mul(ll a, ll b) {
    assert(a >= 0);
    assert(b >= 0);
    return (a % MOD) * (b % MOD) % MOD;
}
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
ll sumTerms(ll x) {
    return x * (x + 1) / 2 % MOD;
}
ll sumSquares(ll x) {
    return x * (x + 1) * (2 * x + 1) / 6 % MOD;
}
struct SegTree {
    vector<ll> tree;
    vector<Node> lazy;
    int n;
    const ll IDN = 0;
    const Node LAZY_IDN = Node(0, 0, 0);
    ll combine(ll a, ll b) {
        return add(a, b);
    }
    Node combineNodes(Node lt, Node rt) {
        return Node(add(lt.a, rt.a), add(lt.b, rt.b), add(lt.c, rt.c));
    }
    Node shiftNode(Node node, ll shift) {
        // = a * (x + s)^2 + b * (x + s) + c
        // = a * (x^2 + 2*x*s + s^2) + b * x + b * s + c
        // = a * x^2 + a*2*x*s + a*s^2 + b * x + b * s + c
        // = a* x^2 + (2*a*s + b) * x + ( a * s^2 + b * s + c)
        normalize(shift);
        Node newNode;
        newNode.a = node.a;
        newNode.b = add(node.b, mul(node.a, shift * 2));
        newNode.c = add(node.c, add(mul(node.b, shift), mul(node.a, mul(shift, shift))));
        newNode.normalize();
        return newNode;
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
            tree[k] = add(tree[k], mul(lazy[k].a, sumSquares(sr - sl)));
            tree[k] = add(tree[k], mul(lazy[k].b, sumTerms(sr - sl)));
            tree[k] = add(tree[k], mul(lazy[k].c, (sr - sl + 1)));
            if (sl != sr) {
                int mid = (sl + sr) / 2;
                lazy[k << 1] = combineNodes(lazy[k << 1], lazy[k]);
                lazy[k << 1 | 1] = combineNodes(lazy[k << 1 | 1],
                                                shiftNode(lazy[k], mid + 1 - sl));
            }
        }
        lazy[k].a = lazy[k].b = lazy[k].c = 0;
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
