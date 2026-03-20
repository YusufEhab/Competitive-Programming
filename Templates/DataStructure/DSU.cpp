#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
struct DSU {
    vector<int> par;
    int cmp;
    // int sets[N], pos[N], tail[N], nxt[N];
    DSU(int n) {
        par.assign(n+1, -1);
        cmp = n;
      /*
        iota(sets, sets+n, 0); //root list
        iota(pos,pos+n, 0); //position of root in list
        iota(tail, tail+n, 0); //last node in u's
        memset(nxt, -1, n* sizeof nxt[0]);
      */
    }
    int find(int u) {
        return par[u] < 0? u : par[u] = find(par[u]);
    }
    bool merge(int b, int s) {
        b = find(b), s = find(s);
        if (b == s) return false;
        if (par[b] > par[s]) swap(b,s); // reversed condition since neg par
        par[b] += par[s];
        par[s] = b;
        /*
        int &t = tail[b];
        nxt[t] = s;
        tail[b] = tail[s];
        int idx = pos[s]; //remove s from roots
        sets[idx] = sets[--cmp]; //garpage val
        pos[sets[idx]] = idx;
        */
        return true;
    }
/*
    vector<int> getcmp(int u) {
        vector<int> ret;
        u = find(u);
        ret.reserve(-par[u]);
        for (int v = u; ~v; v = nxt[v])
            ret.emplace_back(v);
        return ret;
    }
    vector<vector<int>> getall() {
        vector<vector<int>> ret;
        ret.reserve(cmp);
        for (int i = 0; i < cmp; ++i) {
            ret.emplace_back(getcmp(sets[i]));
        }
        return ret;
    }
*/
    int size(int x) {
        return -par[find(x)];
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
};
