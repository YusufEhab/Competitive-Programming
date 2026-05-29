#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
vector<int> adj[N];
struct tarjan {
    int n, c = 1, cmp = 0;
    vector<int> id, low;
    vector<bool> in_stk;
    stack<int> stk;
    tarjan(int sz) {
        n = sz;
        id.assign(n+1, -1);
        low.assign(n+1, {});
        in_stk.assign(n+1, {});
    }
    void get() {
        for (int i = 1; i <= n; ++i) {
            if (id[i] == -1) dfs(i);
        }
    }
    void dfs(int u) {
        stk.push(u); in_stk[u] = true;
        id[u] = low[u] = c++;
        for (auto &v: adj[u]) {
            if (id[v] == -1) {dfs(v); low[u] = min(low[u], low[v]);}
            else if (in_stk[v]) low[u] = min(low[u], id[v]);
        }
        if (id[u] == low[u]) {
            while (true) {
                int t = stk.top(); stk.pop();
                in_stk[t] = false;
                low[t] = id[u];
                if (t == u) break;
            }
            ++cmp;
        }
    }
};
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    tarjan scc(n);
    scc.get();
    cout << scc.cmp << '\n';
    int mx = 0, c = 0;
    vector<int> cnt(n+1);
    for (int i = 1; i <= n; ++i) {
        if (++cnt[scc.low[i]] > mx) {
            mx = cnt[scc.low[i]];
            c = scc.low[i];
        }
    }
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (scc.low[i] == c) ans.emplace_back(i);
    }
    for (auto &i: ans) cout << i << " ";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC = 1;
    // cin >> TC;
    while (TC--) {
        solve();
        cout << '\n';
    }
}
