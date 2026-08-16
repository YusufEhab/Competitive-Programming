#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5+5;
vector<int> adj[N];
vector<pair<int,int>> Q[N]; // col, idx;
int col[N];

int sz[N], big[N], freq[N], ans[N];
void pre(int u, int par) {
    sz[u] = 1;
    for (auto &v: adj[u]) {
        if (v == par) continue;
        pre(v, u);
        sz[u] += sz[v];
        if (!big[u] || sz[v] > sz[big[u]]) big[u] = v;
    }
}
void add(int u, int par, int d) {
    freq[col[u]] += d;
    for (auto &v: adj[u]) {
        if (v != par) {
            add(v, u, d);
        }
    }
}
void dfs(int u, int par, bool keep) {
    for (auto &v: adj[u]) {
        if (v != par && v != big[u]) {
            dfs(v, u, false);
        }
    }
    //add
    if (big[u]) dfs(big[u], u, true); //heavy subtrees
    ++freq[col[u]];
    for (auto &v: adj[u]) {
        if (v != par && v != big[u]) {
            add(v, u, 1); //light subtrees
        }
    }
    //ans
    for (auto &[c, idx]: Q[u]) {
        ans[idx] = freq[c];
    }
    //remove
    if (!keep) add(u, par, -1);
}

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> col[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int q; cin >> q;
    for (int i = 1, u, c; i <= q; ++i) {
        cin >> u >> c;
        Q[u].emplace_back(c, i);
    }
    pre(1,1);
    dfs(1,1,true);
    for (int i = 1; i <= q; ++i) cout << ans[i] << " ";
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
