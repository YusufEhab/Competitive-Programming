#include<bits/stdc++.h>
#define int long long
using namespace std;
int N;
struct Segtree {
#define lnode (2*x+1)
#define rnode (2*x+2)
#define md ((lx+rx)/2)
    int n;
    vector<vector<int>> node;
    Segtree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        node.assign(2*n+1, {});
    }
    void build(const vector<vector<int>> &v, int x, int lx, int rx) {
        if (rx-lx == 1) {
            if (lx < v.size()) node[x] = v[lx];
            return;
        }
        build(v, lnode, lx, md);
        build(v, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    void build(const vector<vector<int>> &v) {
        build(v, 0,0,n);
    }
    vector<int> merge(vector<int>&lf, vector<int> &rt) {
        int a = lf.size(), b = rt.size();
        vector<int> ret(a+b);
        int i = 0, j = 0, k = 0;
        while (i < a || j < b) {
            if (j >= b || (i < a && lf[i] <= rt[j])) {
                ret[k++] = lf[i++];
            }else {
                ret[k++] = rt[j++];
            }
        }
        return ret;
    }
    int left(int l, int r, int val, int x, int lx, int rx) {
        if (l <= lx && rx <= r) {
            auto it = lower_bound(node[x].begin(), node[x].end(), val);
            if (it == node[x].begin()) return -1;
            --it;
            return *it;
        }
        if (rx <= l || lx >= r) return -1;
        int lf = left(l, r, val, lnode, lx, md);
        int rt = left(l, r, val, rnode, md, rx);
        return max(lf, rt);
    }
    int left(int l, int r, int val) {
        return left(l, r, val, 0,0,n);
    }
    int right(int l, int r, int val, int x, int lx, int rx) {
        if (l <= lx && rx <= r) {
            auto it = upper_bound(node[x].begin(), node[x].end(), val);
            if (it == node[x].end()) return N;
            return *it;
        }
        if (rx <= l || lx >= r) return N;
        int lf = right(l, r, val, lnode, lx, md);
        int rt = right(l, r, val, rnode, md, rx);
        return min(lf, rt);
    }
    int right(int l, int r, int val) {
        return right(l, r, val, 0,0,n);
    }
#undef lnode
#undef rnode
#undef md
};
void solve() {
    int n; cin >> n;
    N = n;
    vector<int> a(n), comp, rank(n);
    int sub = 0;
    for (auto &i: a) {
        cin >> i;
        sub += i;
        comp.emplace_back(i);
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    auto id = [&](int i) -> int {
        return lower_bound(comp.begin(), comp.end(), i) - comp.begin();
    };
    // 1. compress a[i] values to rank[i]
    for (int i = 0; i < n; ++i) {
        rank[i] = id(a[i]);
    }
    // 2. get occurrance for each val
    int m = comp.size();
    vector<vector<int>> occ(m);
    for (int i = 0; i < n; ++i) {
        occ[rank[i]].emplace_back(i);
    }
    // 3. make a segtree of occurrance
    Segtree tree(m);
    tree.build(occ);
    /* 4. for each rank[i] get -> p
     * nearest left l, l2 (rank[l2] > rank[l] > rank[i]) rank range -> [p+1, m) lower_bound(i, l)-1;
     * nearest right r, r2 (rank[i] <= rank[r] <= rank[r2]) rank range -> [p, m) upper_bound(i, r);
     * cnt = (i-l)*(r-i)+(l-l2)*(r-i)+(i-l)*(r2-r);
     * sum = a[i] * cnt;
    */
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int p = rank[i];
        int l = tree.left(p+1, m, i);
        int l2 = (l != -1) ? tree.left(p+1, m, l) : -1;
        int r = tree.right(p, m, i);
        int r2 = (r != N )? tree.right(p, m, r) : N;
        int cnt = (i-l)*(r-i)+(l-l2)*(r-i)+(i-l)*(r2-r);
        sum += a[i] * cnt;
    }
    cout << sum-sub;
}

signed main() {
    freopen("max.in", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC = 1;
    cin >> TC;
    while (TC--) {
        solve();
        cout << '\n';
    }
}
