#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
const int M = N*N;
int n, m;

int head[N], to[M], nxt[M], ne;
void init(int n) {
    memset(head, -1, n*sizeof head[0]);
    ne = 0;
}
void addedge(int u, int v) {
    to[ne] = v;
    nxt[ne] = head[u];
    head[u] = ne++;
}
void add2edge(int u, int v) {
    addedge(u, v);
    addedge(v, u);
}
//undirected graph
int vis[M], idx;
int ans[M], sz;
int deg[N];
void euler(int u) {
    for (int &e = head[u], v; ~e;) {
        int ee = e;
        e = nxt[e];
        if (vis[ee] == idx) continue;
        vis[ee] = vis[ee^1] = 1;
        v = to[ee];
        euler(v);
        ans[sz++] = ee; // edges reversed
    }
}
bool build(int &st) {
    int od = 0; st = -1;
    // deg is all even or except 2 -> od should be 0 or 2
    for (int i = 1; i <= n; ++i) {  // to check validation and get the start
        if (deg[i]&1) ++od, st = i;
        if (deg[i]>0 && st == -1) st = i;
    }
    if (!(od == 0 || od == 2)) return false; // no solution
    if (st == -1) {sz = 0; return true;}    // all are zero degree
    sz = 0, ++idx; // for multiple test cases
    euler(st);
    if (sz != m) return false;
    reverse(ans, ans+sz);
    return true;
}
void solve() {
    cin >> n >> m;
    init(n);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        add2edge(u, v);
        ++deg[u];
        ++deg[v];
    }
    int st;
    bool ok = build(st);
    if (!ok) return cout << -1,void();
    cout << st << " ";
    for (int i = 0; i < sz; ++i) cout << to[ans[i]] << " ";
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
