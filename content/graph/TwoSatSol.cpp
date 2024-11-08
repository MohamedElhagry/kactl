/**
 * Author: Tamer
 * Description: 2 Sat using Kosaraju's Algorithm for SCC, does generate the solution
 */
const int N = 2e5 + 5;
vector<int> adj[N], adjR[N], revOut;
int compOf[N], sz, comp;
bool vis[N];
void dfs1(int u) {
    vis[u] = true;
    for (auto v: adj[u])
        if (!vis[v])
            dfs1(v);
    revOut.push_back(u);
}
void dfs2(int u) {
    vis[u] = true;
    compOf[u] = comp;
    for (auto v: adjR[u])
        if (!vis[v])dfs2(v);
}
void initSCC(int n) {
    sz = n;
    revOut.clear();
    comp = 0;
    for (int i = 0; i < sz; i++) {
        adj[i].clear();
        adjR[i].clear();
        vis[i] = 0;
    }
}
void gen() {
    for (int i = 0; i < sz; ++i) {
        if (!vis[i])
            dfs1(i);
    }
    reverse(all(revOut));
    for (int i = 0; i < sz; i++)
        vis[i] = false;
    for (auto node: revOut) {
        if (vis[node])continue;
        comp++;
        dfs2(node);
    }
}
struct TwoSat {
    int N;
    TwoSat(int n) {
        N = n;
        initSCC(2 * N);
    }
    int addVar() { // only if you will use in atMostOne
        adj[2 * N].clear();
        adj[2 * N + 1].clear();
        adjR[2 * N].clear();
        adjR[2 * N + 1].clear();
        vis[2 * N] = vis[2 * N + 1] = 0;
        sz += 2;
        return N++;
    }
    // x or y, edges will be refined in the end
    void either(int x, int y) {
        x = max(2 * x, -1 - 2 * x);
        y = max(2 * y, -1 - 2 * y);
        adj[x ^ 1].push_back(y);
        adj[y ^ 1].push_back(x);
        adjR[y].push_back(x ^ 1);
        adjR[x].push_back(y ^ 1);
    }
    void implies(int x, int y) {
        either(~x, y);
    }
    void must(int x) {
        x = max(2 * x, -1 - 2 * x);
        adj[x ^ 1].push_back(x);
        adjR[x].push_back(x ^ 1);
    }
    void XOR(int x, int y) {
        either(x, y);
        either(~x, ~y);
    }
    void atMostOne(const vector<int> &li) {
        if (li.size() <= 1) return;
        int last = ~li[1];
        for (int i = 2; i < li.size(); i++) {
            int next = addVar();
            implies(li[i], last);
            either(last, next);
            implies(li[i], next);
            last = ~next;
        }
        implies(li[0], last);
    }
    vector<bool> solve() {
        gen();
        for (int i = 0; i < 2 * N; ++i)
            if (compOf[i] == compOf[i ^ 1])return {};
        vector<bool> ans(N);
        for (int i = 0; i < 2 * N; i += 2)
            ans[i / 2] = compOf[i] > compOf[i + 1];
        return ans;
    }
};
