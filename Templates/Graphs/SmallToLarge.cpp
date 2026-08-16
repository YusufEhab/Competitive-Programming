#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<vector<int>> adj;
vector<int> col;
vector<int> ans;
set<int> dfs(int u, int par = 1) {
    set<int> c;
    c.insert(col[u]);
    for (auto &v: adj[u]) {
        if (v == par) continue;
        auto ret = dfs(v, u);
        ans[u] = min(ans[u], ans[v]);
        if (ret.size() > c.size()) swap(ret, c);
        for (auto &i: ret) {
            auto it = c.upper_bound(i);
            if (it != c.end()) ans[u] = min(ans[u], *it-i);
            if (it != c.begin()) ans[u] = min(ans[u], i-*prev(it));
        }
        for (auto &a: ret) c.insert(a);
    }
    return c;
}
void solve() {
    int n; cin >> n;
    col.resize(n+1);
    adj.resize(n+1);
    ans.assign(n+1, 1e15);
    for (int i = 1; i <= n; ++i) cin >> col[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << (ans[x] == 1e15? -1 : ans[x]) << '\n';
    }
}
