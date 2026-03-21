//offline edge add/delete
const int M = 2e5+5;
struct DSU {
    vector<int> par;
    int cmp;
    struct operation{int s, parS, b, parB;};
    stack<operation> ops;
    int cursz[M], cur; //cursz = ops.size - find ops
    DSU(int n) {
        par.assign(n+1, -1);
        cmp = n;
    }
    int find(int u) {
        if (par[u] < 0) return u;
        ops.emplace(u, par[u], -1, 0);
        return par[u] = find(par[u]);
    }
    bool merge(int s, int b) {
        cursz[cur++] = ops.size();
        s = find(s), b = find(b);
        if (s == b) return false;
        if (par[b] > par[s]) swap(s, b);
        ops.emplace(s, par[s], b, par[b]);
        par[b] += par[s];
        par[s] = b;
        return true;
    }
    void rollback() {
        auto [s, parS, b, parB] = ops.top(); ops.pop();
        par[s] = parS;
        if (~b) par[b] = parB; //if the edit source is find then no need
    }
    void rolluntil(int t) {
        while (ops.size() > cursz[t+1]) rollback();
        cur = t+1;
    }
};
