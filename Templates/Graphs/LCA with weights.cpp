#include<bits/stdc++.h>
// #define int long long
using namespace std;

vector<vector<pair<int,int>>> adj;
struct LCA{
    using fun = function<int(int,int)>;
    int n, LG, IGN;
    fun merge;
    vector<vector<int>> par, cost;
    vector<int> dep, sz;
    LCA(int N, int ign, fun f) {
        n = N, LG = __lg(n)+1; IGN = ign;
        merge = f;
        par.assign(N+1, vector<int>(LG+1));
        cost.assign(N+1, vector<int>(LG+1));
        dep.assign(N+1, 0);
        sz.assign(N+1, 0);
        dfs(1,0,IGN);
    }
    void dfs(int u, int p, int w) {
        par[u][0] = p;
        cost[u][0] = w;
        dep[u] = dep[p] + 1;
        sz[u] = 1;
        for (int i = 1; i <= LG; i++) {
            par[u][i] = par[par[u][i-1]][i-1];
            cost[u][i] = merge(cost[u][i-1], cost[par[u][i-1]][i-1]);
        }
        for (auto &[v,c]: adj[u]) {
            if (v == p) continue;
            dfs(v, u, c);
            sz[u] += sz[v];
        }
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
    int kth(int u, int k) { //kth ancestor to the root
        for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
        return u;
    }
    int get_cost(int u, int k) {
        if (dep[u] < k) return IGN;
        int ret = IGN;
        for (int i = 0; i <= LG; i++) {
            if (k & (1 << i)) {
                ret = merge(ret, cost[u][i]);
                u = par[u][i];
            }
        }
        return ret;
    }
    //kth node from u to v, 0th node is u
    int kth_on_path(int u, int v, int k) {
        int l = lca(u, v);
        if (dep[l] + k <= dep[u]) return kth(u, k);
        k -= dep[u] - dep[l];
        return kth(v, dep[v] - dep[l] - k);
    }
    int query(int u, int v) {
        int l = lca(u, v);
        return merge(get_cost(u, dep[u]-dep[l]), get_cost(v, dep[v]-dep[l]));
    }
};
// LCA min_tree(n, 1e8, [](int a, int b) {
//         return min(a,b);
//     });
