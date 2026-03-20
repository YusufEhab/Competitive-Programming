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
//directed graph
int ans[M*2], sz;
int in[N], out[N];
void euler(int u) {
    for (int &e = head[u], v; ~e;) {
        int ee = e;
        e = nxt[e];
        v = to[ee];
        euler(v);
        ans[sz++] = ee; // edges reversed
    }
}
bool build(int &st) {
    int pos = 0, neg = 0; st = -1;
    // diff is all 0 except 2 +1, -1
    for (int i = 1; i <= n; ++i) {
        int d = out[i]-in[i];
        if (d == 1) ++pos, st = i;
        else if (d == -1) ++neg;
        else if (d != 0) return false;
        if (out[i] > 0 && st == -1) st = i;
    }
    if (!((pos == 0 && neg == 0)||(pos == 1 && neg == 1))) return false; // no solution
    if (st == -1) {sz = 0; return true;}    // all are zero degree
    sz = 0; // for multiple test cases
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
        addedge(u, v);
        ++out[u];
        ++in[v];
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
