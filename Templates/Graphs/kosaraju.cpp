#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
bool vis_out[N], vis_in[N];
vector<int> out[N], in[N];
vector<int> order, scc;
void dfs1(int u) {
    vis_out[u] = true;
    for (auto &v: out[u]) {
        if (!vis_out[v]) dfs1(v);
    }
    order.emplace_back(u);
}
void dfs2(int u, int c) {
    vis_in[u] = true;
    scc[u] = c;
    for (auto &v: in[u]) {
        if (!vis_in[v]) dfs2(v, c);
    }
}
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        out[u].emplace_back(v);
        in[v].emplace_back(u);
    }

    //get topological order
    for (int i = 1; i <= n; ++i) {
        if (!vis_out[i]) dfs1(i);
    }
    reverse(order.begin(), order.end());
    
  //color each component
    scc.assign(n+1, {});
    int id = 1;
    for (auto &u: order) {
        if (!vis_in[u]) dfs2(u, id++);
    }
    
  //get max component
    int mx = 0, c = 0;
    vector<int> cnt(n+1);
    for (int i = 1; i <= n; ++i) {
        ++cnt[scc[i]];
        if (cnt[scc[i]] > mx) {
            mx = cnt[scc[i]];
            c = scc[i];
        }
    }
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (scc[i] == c) ans.emplace_back(i);
    }
  
    cout << id-1 << '\n';
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
