#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 9, LG = 18;

vector<int> adj[N]; //adj
int par[N][LG + 1], dep[N], sz[N]; // anc, level, subtree size
int in[N], out[N], timer = 1;

void dfs(int u, int p = 0) {
    in[u] = timer++;
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    for (int i = 1; i <= LG; i++)
        par[u][i] = par[par[u][i - 1]][i - 1];
    for (auto v: adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    out[u] = timer-1;
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}
int dist(int u, int v) {
    int l = lca(u, v);
    return dep[u] + dep[v] - (dep[l] << 1); // dep[u] - dep[l] + dep[v] - dep[l]
}
int kth(int u, int k) {
    for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
    return u;
}
//kth node from u to v, 0th node is u
int go(int u, int v, int k) {
    int l = lca(u, v);
    if (dep[l] + k <= dep[u]) return kth(u, k);
    k -= dep[u] - dep[l];
    return kth(v, dep[v] - dep[l] - k);
}
// prefix sum on tree
int ans[N];
int dfs1(int u, int p = 0) {
    for (auto &v: adj[u]) {
        if (v == p) continue;
        ans[u] += dfs1(v, u);
    }
    return ans[u];
}
// give u v x and x on path from u to v
void solve() {
    int n, q; cin >> n >> q;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    while (q--) {
        int u, v, x; cin >> u >> v >> x;
        ans[u] += x;
        ans[v] += x;
        int l = lca(u, v);
        ans[l] -= x;
        ans[par[l][0]] -= x;
    }
    dfs1(1);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
}
signed main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int TC = 1;
    //cin >> TC;
    while (TC--) {
        solve();
        cout << '\n';
    }
}
