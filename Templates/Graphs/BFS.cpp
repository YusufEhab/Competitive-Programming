//Most applications like component traversal, cycle detection, topsort, bipartite is also applicable using BFS
// Multisource BFS is to push all starts into the queue then run normal BFS
// Shortest path
    //Unweighted -> Single-source shortest path, multi-source shortest path
        //Positive weighted -> Dijkstra, 0/1 BFS
        //negative weighted -> Bellman-ford
    // All pairs shortest path -> Floyd-Warshall
    // multiple sources and single destination -> Run sssp from the destination :D
//BFS traversal level by level
void bfs(int s) {
    queue<int> q;
    q.emplace(s);
    vis[s] = 1;
    int lvl = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto u = q.front(); q.pop();
            if (u == goal) {
                // process the goal
            }
            //add neighbors
            for (auto &v: adj[u]) {
                if (vis[v]) continue;
                q.emplace(v);
                vis[v] = 1;
            }
        }
    }
}
//bipartite
vector<int> col(n+1, -1);
bool isBipartite() {
    bool isbipartite = 1;
    for (int i = 1; i <= n; ++i) {
        if (col[i] == -1) { //if not colored
            col[i] = 0; // color it with 0
            queue<int> q;
            q.push(i);
            while (!q.empty()) { // traverse all its path
                int p = q.front();
                q.pop();
                for (auto j: adj[p]) { // check the neighbours
                    if (col[j] == -1) { // if not colored make it inverse color and push
                        col[j] = col[p] ^ 1;
                        q.push(j);
                    } else {
                        isbipartite &= (col[j] != col[p]);
                    }
                }
            }
        }
    }
    return isbipartite;
}
//topological sort (indegree is calculated and no cycle is detected already)
vector<int> topsort() {
    queue<int> q;
    vector<int> topsort;
    for(int i = 1; i <= n; ++i){
        if(in[i] == 0){
            q.emplace(i);
        }
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        topsort.emplace_back(u);
        for(auto &v : adj[u]){
            in[v]--;
            if(in[v] == 0){
                q.emplace(v);
            }
        }
    }
    return topsort;
}
