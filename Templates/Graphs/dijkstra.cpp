
auto dijkstra = [&](int s){ // shortest path from source to every node
    vector<int> dis(n, 1e15);
    priority_queue<pair<int,int>> pq;
    pq.emplace(dis[s] = 0,s);
    while(!pq.empty()){
        auto [c, u] = pq.top(); pq.pop();
        c *= -1; if(dis[u] < c) continue; //choose lowest not visited node
        for(auto &[v,w]: adj[u]) { //relaxation: update estimates
            if (dis[u]+w < dis[v]) {
                dis[v] = dis[u]+w;
                pq.emplace(-dis[v], v);
            }
        }
    }
};
