/**
 * Author: Hagry
 * Description: Dynamic Connectivity Offline
 */
struct Query {
    char t;
    int u, v;
};
struct Elem {
    int u, v, szU, cnt;
};
struct DSURollback {
    int cnt, n;
    stack <Elem> st;
    vector<bool> ans;
    vector<int> sz, par;
    vector <vector<pair < int, int>>>g;
    DSURollback(int _n) {
        cnt = _n;
        n = 1;
        while (n < _n)n *= 2;
        g.resize(2 * n + 5);
        par.resize(_n + 1);
        sz.resize(_n + 1, 1);
        iota(all(par), 0);
    }
    void rollback(int x) {
        while (st.size() > x) {
            auto e = st.top();
            st.pop();
            cnt = e.cnt;
            sz[e.u] = e.szU;
            par[e.v] = e.v;
        }
    }
    int findSet(int u) {
        return par[u] == u ? u : findSet(par[u]);
    }
    void update(int u, int v) {
        st.push({u, v, sz[u], cnt});
        cnt--;
        par[v] = u;
        sz[u] += sz[v];
    }
    void unionSet(int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (u != v) {
            if (sz[u] < sz[v])
                swap(u, v);
            update(u, v);
        }
    }
    void solve(int x, int l, int r) {
        int cur = st.size();
        for (auto i: g[x])
            unionSet(i.first, i.second);
        if (l == r) {
            if (ans[l])
                cout << cnt << endl;
            rollback(cur);
            return;
        }
        int m = (l + r) >> 1;
        solve(x * 2, l, m);
        solve(x * 2 + 1, m + 1, r);
        rollback(cur);
    }
    void traverse(int x, int lX, int rX, int l, int r, int u, int v) {
        if (rX < l || lX > r)
            return;
        if (lX >= l && rX <= r) {
            g[x].emplace_back(u, v);
            return;
        }
        int m = (lX + rX) >> 1;
        traverse(x * 2, lX, m, l, r, u, v);
        traverse(x * 2 + 1, m + 1, rX, l, r, u, v);
    }
    void update(int u, int v, int l, int r) {
        traverse(1, 0, n - 1, l, r, u, v);
    }
};
