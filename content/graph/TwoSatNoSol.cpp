/**
 * Author: Tamer
 * Description: 2 Sat using Tarjan's Algorithm for SCC, does not generate the solution
 */
const ll inf = 1e18;
vector<int> adj[N];
int low[N], scc[N], comps, timer;
stack<int> st;
bool sat;
void dfs(int u) {
    low[u] = ++timer;
    st.push(u);
    int cur = low[u];
    for (int v: adj[u]) {
        if (!low[v]) dfs(v);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == cur) {
        comps++;
        while (1) {
            int v = st.top();
            st.pop();
            scc[v] = comps;
            low[v] = inf;
            if (scc[v] == scc[v ^ 1])
                sat = false;
            if (u == v) break;
        }
    }
}
void initSCC(int n) {
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        scc[i] = 0, low[i] = 0;
    }
    comps = 0, timer = 0;
    sat = true;
    while (!st.empty())st.pop();
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
        scc[2 * N] = low[2 * N + 1] = 0;
        return N++;
    }
    // x or y, edges will be refined in the end
    void either(int x, int y) {
        x = max(2 * x, -1 - 2 * x);
        y = max(2 * y, -1 - 2 * y);
        adj[x ^ 1].push_back(y);
        adj[y ^ 1].push_back(x);
    }
    void implies(int x, int y) {
        either(~x, y);
    }
    void must(int x) {
        x = max(2 * x, -1 - 2 * x);
        adj[x ^ 1].push_back(x);
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
    bool solve() {
        for (int i = 0; i < 2 * N; i++)
            if (!scc[i])
                dfs(i);
        return sat;
    }
};