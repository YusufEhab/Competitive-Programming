#include<bits/stdc++.h>
using namespace std;

struct Node {
    int sum;
    Node() {
        sum = 0;
    }
    Node(int x) {
        sum = x;
    }
    void change(int x) {
        sum += x; 
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
    void update(int idx, int val, int x, int lx, int rx) {
        if (rx-lx == 1) {
            node[x].change(val);
            return;
        }
        if (idx < md)
            update(idx, val, lnode, lx, md);
        else
            update(idx, val, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    Node merge(Node &lf, Node rt) {
        Node ans = Node();
        ans.sum = lf.sum + rt.sum;
        return ans; 
    }
    void update(int idx, int val) {
        update(idx, val, 0, 0, n);
    }
    Node get(int l, int r, int x, int lx, int rx) {
        if (rx <= l || lx >= r) return Node();
        if (l <= lx && rx <= r) return node[x];
        Node lf = get(l, r, lnode, lx, md);
        Node rt = get(l, r, rnode, md, rx);
        return merge(lf, rt);
    }
    Node get(int l, int r) {
        return get(l, r, 0, 0, n);
    }
    void build(const vector<int> &v, int x, int lx, int rx) {
        if (rx-lx==1) {
            if (lx < v.size()) node[x] = Node(v[lx]);
            return;
        }
        build(v, lnode, lx, md);
        build(v, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    void build(const vector<int> &v) {
        build(v, 0,0,n);
    }
#undef md
#undef lnode
#undef rnode
};

signed main() {
    ios::sync_with_stdio(0);cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    Segtree tree(n);
    tree.build(a);
    //ready to get used
}
