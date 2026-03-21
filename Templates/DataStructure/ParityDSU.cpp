//Bipartite checking
const int N = 2e5+5;
struct DSU {
    vector<int> par;
    int col[N];
    DSU(int n) {
        par.assign(n+1, -1);
        memset(col, 0, n*sizeof col[0]);
    }
    pair<int,int> find(int u) {
        if (par[u] < 0) return {u,0};
        auto [r,d] = find(par[u]);
        col[u] ^= col[par[u]];
        par[u] = r;
        return {r,col[u]};
    }
    int merge(int s, int b, bool f) {
        auto [rs, ds] = find(s);
        auto [rb, db] = find(b);
        if (rs == rb) return (ds^db) == f? 1 : -1;
        if (par[rb] > par[rs]) swap(rs,rb);
        par[rs] = b;
        col[rs] = ds^db^f;
        return 0;
    }
};
