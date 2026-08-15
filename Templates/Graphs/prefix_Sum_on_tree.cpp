int n; cin >> n;
    vector<int> k(n+1);
    for (int i = 1; i <= n; i++) cin >> k[i];
    adj.assign(n + 1, {});
    for (int i = 2; i <= n; i++) {
        int u, c;
        cin >> u >> c;
        adj[u].emplace_back(i, c);
        adj[i].emplace_back(u, c);
    }
    const int INF = 1e9 + 5;
    LCA min_tree(n, INF, [](int a, int b) {
        return min(a,b);
    });
    LCA max_tree(n, -INF, [](int a, int b) {
        return max(a,b);
    });
    vector<int> diff(n+1);
    for (int v = 1; v <= n; v++) {
        int cur = v, curMin = INF, curMax = -INF;
        for (int j = min_tree.LG; j >= 0; j--) {
            int jump = 1 << j;
            if (jump >= min_tree.dep[cur]) continue;
            int mn = min_tree.get_cost(cur, jump);
            int mx = max_tree.get_cost(cur, jump);
            int newMin = min(curMin, mn);
            int newMax = max(curMax, mx);
            if (newMax - newMin <= k[v]) { // condition 
                curMin = newMin;
                curMax = newMax;
                cur = min_tree.par[cur][j];
            }
        }
        diff[v]++;
        if (cur != 1) diff[min_tree.par[cur][0]]--;
    }

    //bottom-up order.
    vector<int> order;
    order.reserve(n);
    order.push_back(1);
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (auto [v, w] : adj[u]) {
            if (v == min_tree.par[u][0]) continue;
            order.push_back(v);
        }
    }
    for (int i = n - 1; i > 0; i--) {
        int u = order[i];
        diff[min_tree.par[u][0]] += diff[u];
    }
    for (int u = 1; u <= n; u++) cout << diff[u] << " ";
