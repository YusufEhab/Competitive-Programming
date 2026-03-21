//relative weight queries
const int N = 2e5+5;
struct DSU {
    vector<int> par;
    int w[N];
    DSU(int n) {
        par.assign(n+1, -1);
        memset(w, 0, n*sizeof w[0]);
    }
    pair<int,int> find(int u) {
        if (par[u] < 0) return {u,0};
        auto [r,wr] = find(par[u]);
        par[u] = r;
        w[u] += wr;
        return {r,w[u]};
    }
    bool merge(int s, int b, int f) {
        auto [rs, ws] = find(s);
        auto [rb, wb] = find(b);
        if (rs == rb) return (ws-wb) == f;
        if (par[rb] > par[rs]) swap(rs,rb);
        par[rs] = rb;
        w[rs] = wb-ws+f;
        return true;
    }
    int query(int u, int v) {
        auto [ru, wu] = find(u);
        auto [rv, wv] = find(v);
        if (ru != rv) return 1e16;
        return wv-wu;
    }
};
