//Make sure to apply the operation on all components 
//traverse on connected component
void dfs(int u) {
    vis[u] = 1;
    for (auto &v: adj[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}
//Size of component
int dfs(int u) {
    vis[u] = 1;
    int ans = 1;
    for (auto &v: adj[u]) {
        if (vis[v]) continue;
        ans += dfs(v);
    }
    return ans;
}
//Cycle detection undirected
bool cycle(int u, int par) {
    vis[u] = 1;
    for (auto &v: adj[u]) {
        if (v == par) continue;
        if (vis[v]) return true;
        if (dfs(v, u)) return true;
    }
    return false;
}
//Cycle detection directed
int col[N];
int cycle(int u) {
    col[u] = 1;
    for (auto &v: adj[u]) {
        if (col[u] == 0) {
            if (dfs(v)) return true;
        }
        else if (col[u] == 1) return true;
    }
    col[u] = 2;
    return false;
}
//Bipartite component
int col[N];
bool bi(int u, int par) {
    for (auto &v: adj[u]) {
        if (v == par) continue;
        if (col[u] == 0) {
            col[v] = 3 - col[u];
            if(!bi(v, u)) return false;
        }else if (col[v] == col[u]) return false;
    }
    return true;
}

// topological sort (reversed)
int col[N], ans[N], sz;
bool topsort(int u) {
    col[u] = 1;
    for (auto &v: adj[u]) {
        if (col[u] == 0) {
            if (dfs(v)) return true;
        }
        else if (col[u] == 1) return true;
    }
    col[u] = 2;
    ans[sz++] = u;
    return false;
}
