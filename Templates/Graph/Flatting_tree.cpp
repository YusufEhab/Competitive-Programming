const int N = 3e5+5;
int timer = 1;
vector<vector<int>> adj(N);
int in[N], out[N];
void dfs(int u, int par) {
    in[u] = timer++;
    for (auto &v: adj[u]) {
        if (v == par) continue;
        dfs(v, u);
    }
    out[u] = timer-1;
}
