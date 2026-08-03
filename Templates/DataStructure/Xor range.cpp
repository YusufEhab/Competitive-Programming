#include<bits/stdc++.h>
#define int long long
using namespace std;

const int B = 30;
struct Node {
    int sum, freq[B]{};
    int lazy;
    bool is_lazy;
    Node() {
        sum = lazy = is_lazy = 0;
    }
    Node(int x) {
        sum = x;
        for (int i = 0; i < B; ++i) {
            if (x >> i & 1) ++freq[i];
        }
        lazy = is_lazy = 0;
    }
    void update(int val, int lx, int rx) {
        int sz = rx-lx;
        for (int i = 0; i < B; ++i) {
            if (val >> i & 1) {
                sum -= freq[i]*(1<<i);
                sum += (sz-freq[i])*(1<<i);
                freq[i] = sz-freq[i];
            }
        }
        lazy ^= val;
        is_lazy = 1;
    }
};
struct Segtree {
#define lnode (2*x+1)
#define rnode (2*x+2)
#define md ((lx+rx)/2)
    int n;
    vector<Node> node;
    Segtree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        node.assign(2*n, Node());
    }
    void build(const vector<int>&v, int x, int lx, int rx) {
        if (rx-lx == 1) {
            if (lx < v.size()) node[x] = Node(v[lx]);
            return;
        }
        build(v, lnode, lx, md);
        build(v, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    void build(const vector<int>&v) {
        build(v, 0,0,n);
    }
    Node merge(Node &lf, Node &rt) {
        Node ans = Node();
        ans.sum = lf.sum + rt.sum;
        for (int i = 0; i < B; ++i) {
            ans.freq[i] = lf.freq[i] + rt.freq[i];
        }
        return ans;
    }
    void propagate(int x, int lx, int rx) {
        if (rx-lx == 1 || node[x].is_lazy == 0) return;
        node[lnode].update(node[x].lazy, lx, md);
        node[rnode].update(node[x].lazy, md, rx);
        node[x].lazy = node[x].is_lazy = 0;
    }
    void update(int l, int r, int val, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l <= lx && rx <= r) {
            node[x].update(val, lx, rx);
            return;
        }
        if (rx <= l || lx >= r) return;
        update(l, r, val, lnode, lx, md);
        update(l, r, val, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    void update(int l, int r, int val) {
        update(l, r, val, 0,0,n);
    }
    Node get(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (l <= lx && rx <= r) return node[x];
        if (rx <= l || lx >= r) return Node();
        Node lf = get(l, r, lnode, lx, md);
        Node rt = get(l, r, rnode, md, rx);
        return merge(lf, rt);
    }
    int get(int l, int r) {
        return get(l, r, 0,0,n).sum;
    }
#undef lnode
#undef rnode
#undef md
};
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    Segtree tree(n);
    tree.build(a);
    int q; cin >> q;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) {
            cout << tree.get(l-1, r) << '\n';
        }else {
            int x; cin >> x;
            tree.update(l-1, r, x);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC = 1;
    // cin >> TC;
    while (TC--) {
        solve();
        cout << '\n';
    }
}
