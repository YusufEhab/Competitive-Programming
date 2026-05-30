const int N = 1e5+5;
vector<int> adj[N];
struct tarjan {
    int n, timer, col;
    vector<int> id, low, cmp;
    vector<bool> in_stk;
    stack<int> stk;
    tarjan(int sz) {
        timer = col = 0;
        n = sz;
        id.assign(n+1, -1);
        low.assign(n+1, {});
        cmp.assign(n+1, {});
        in_stk.assign(n+1, {});
    }
    void get() {
        for (int i = 1; i <= n; ++i) {
            if (id[i] == -1) dfs(i);
        }
    }
    void dfs(int u) {
        stk.push(u); in_stk[u] = true;
        id[u] = low[u] = timer++;
        for (auto &v: adj[u]) {
            if (id[v] == -1) dfs(v);
            if (in_stk[v]) low[u] = min(low[u], low[v]);
        }
        if (id[u] == low[u]) {
            while (true) {
                int t = stk.top(); stk.pop();
                in_stk[t] = false;
                cmp[t] = col;
                if (t == u) break;
            }
            ++col;
        }
    }
};
