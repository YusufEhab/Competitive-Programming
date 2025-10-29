// be careful that visited array is started with all is true!!!!!!!
void topo() {
    cin >> n >> m;
    for (int i = 0, u , v; i < m; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        vis[v] = false;
    }
    queue<int> q;
    //push unconnected components
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) q.emplace(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topsort.emplace_back(u);
        for (auto &v: adj[u]) {
            if (!vis[v]) {q.emplace(v); vis[v] = true;}
        }
    }
}
