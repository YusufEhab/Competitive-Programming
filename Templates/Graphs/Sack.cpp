#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5+5;
vector<int> adj[N];
int col[N];

int sz[N], big[N], freq[N], ans[N], sum[N], mx_freq;
void pre(int u, int par) {
    sz[u] = 1;
    for (auto &v: adj[u]) {
        if (v == par) continue;
        pre(v, u);
        sz[u] += sz[v];
        if (!big[u] || sz[v] > sz[big[u]]) big[u] = v;
    }
}
void update(int c, int d) { //update subtree <-----------
    if (freq[c]+d > mx_freq) ++mx_freq;
    else if (freq[c] == mx_freq && sum[freq[c]] == c) --mx_freq;

    sum[freq[c]] -= c;
    freq[c] += d;
    sum[freq[c]] += c;
}
void add(int u, int par, int d) {
    update(col[u], d);
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
    if (big[u]) dfs(big[u], u, true); //heavy subtree
    update(col[u], 1);
    for (auto &v: adj[u]) {
        if (v != par && v != big[u]) {
            add(v, u, 1); //light subtrees
        }
    }
    //ans queries <-----------
    ans[u] = sum[mx_freq];
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
    pre(1,1);
    dfs(1,1,true);
    for (int i = 1; i <= n; ++i) cout << ans[i] << " ";
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
