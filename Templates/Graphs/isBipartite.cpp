vector<vector<int>> adj;
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
