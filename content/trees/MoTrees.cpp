/**
 * Author: Gondozu
 * Description: MoTrees
 */
const int B = 350;
const int LG = 19;
struct Query {
    int l, r, ind, lca;
    Query(int _l, int _r, int _ind, int _lca = -1) : l(_l), r(_r), ind(_ind), lca(_lca) {}
    bool operator<(const Query &q2) {
        return (l / B < q2.l / B) || (l / B == q2.l / B && r < q2.r);
    }
};
struct MoTree {
    vi in, out, flat, dep, freqV;
    vvi anc;
    int n;
    MoTree(vvi &adj, int n, vi &col, int r = 1) : n(n), in(n + 1), out(n + 1), flat((n + 1) * 2), dep(n + 1),
                                                  freqV(n + 1), anc(n + 1, vi(LG)) {
        int x = 0;
        flatten(r, r, x, adj);
        preLCA();
    }
    void flatten(int v, int p, int &timer, const vvi &adj) {
        anc[v][0] = p;
        dep[v] = dep[p] + 1;
        in[v] = timer, flat[timer] = v, ++timer;
        for (auto u: adj[v])
            if (u != p) {
                flatten(u, v, timer, adj);
            }
        out[v] = timer, flat[timer] = v, ++timer;
    }
    void preLCA() {
        for (int k = 1; k < LG; k++)
            for (int i = 1; i <= n; i++)
                anc[i][k] = anc[anc[i][k - 1]][k - 1];
    }
    int binaryLift(int x, int jump) {
        for (int b = 0; b < LG; b++) {
            if (jump & (1 << b))
                x = anc[x][b];
        }
        return x;
    }
    int LCA(int a, int b) {
        if (dep[a] > dep[b])
            swap(a, b);
        int diff = dep[b] - dep[a];
        b = binaryLift(b, diff);
        if (a == b)
            return a;
        for (int bit = LG - 1; bit >= 0; bit--) {
            if (anc[a][bit] == anc[b][bit])
                continue;
            a = anc[a][bit];
            b = anc[b][bit];
        }
        return anc[a][0];
    }
    void upd(int ind, int inc) {
        int v = flat[ind];
        freqV[v] += inc;
        if (freqV[v] == 1) {
            // add()
        } else {
            // remove()
        }
    }
    vi takeQueries(int q) {
        vi ans(q);
        vector<Query> queries;
        int x, y;
        for (int i = 0; i < q; i++) {
            cin >> x >> y;
            if (in[x] > in[y])
                swap(x, y);
            int lca = LCA(x, y);
            if (lca == x)
                queries.emplace_back(in[x], in[y], i);
            else
                queries.emplace_back(out[x], in[y], i, lca);
        }
        sort(all(queries));
        int l = 0, r = 0;
        upd(0, 1);
        for (auto query: queries) {
            while (r < query.r)
                upd(++r, 1);
            while (l > query.l)
                upd(--l, 1);
            while (l < query.l)
                upd(l++, -1);
            while (r > query.r)
                upd(r--, -1);
            if (~query.lca);//addLCA
            //ans[query.ind] = ;
            if (~query.lca);//removeLCA
        }
        return ans;
    }
};