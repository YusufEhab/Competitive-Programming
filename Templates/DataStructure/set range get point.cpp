#include<bits/stdc++.h>
#define int long long
using namespace std;

struct Node {
    int sum, ne;
    Node() {
        sum = ne = 0;
    }
    Node(int x) {
        sum = 0;
    }
};
struct Segtree {
#define md (lx + (rx-lx)/2)
#define lnode (2*x+1)
#define rnode (2*x+2)
    int n;
    vector<Node> node;
    Segtree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        node.assign(2*n, Node());
    }
    int get_idx(int idx, int x, int lx, int rx) {
        if (rx-lx == 1) {
            return node[x].ne + node[x].sum;
        }
        if (idx < md)
            return node[x].ne + get_idx(idx, lnode, lx, md);
        else
            return node[x].ne + get_idx(idx, rnode, md, rx);
    }
    int get(int idx) {
        return get_idx(idx, 0,0,n);
    }
    void set_range(int l, int r, int val, int x, int lx, int rx) {
        if (rx <= l || lx >= r) return;
        if (l <= lx && rx <= r) {node[x].ne += val; return;}
        set_range(l, r, val, lnode, lx, md);
        set_range(l, r, val, rnode, md, rx);
    }
    void set(int l, int r, int val) {
        set_range(l, r, val, 0,0,n);
    }
    void build(const vector<int> &v, int x, int lx, int rx) {
        if (rx-lx == 1) {
            if (lx < v.size()) node[x] = Node(v[lx]);
            return;
        }
        build(v, lnode, lx, md);
        build(v,rnode, md, rx);
    }
    void build(const vector<int> &v) {
        build(v, 0,0,n);
    }
};
void solve() {
    
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
