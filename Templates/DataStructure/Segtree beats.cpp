struct Node {
    int sum, mx;
    Node() {
        sum = mx = 0;
    }
    Node(int x) {
        sum = mx = x;
    }
};
struct Segtree {
#define md (lx+(rx-lx)/2)
#define lnode (2*x+1)
#define rnode (2*x+2)
    int n;
    vector<Node> node;
    Segtree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        node.assign(2*n, Node());
    }
    void update(int l, int r, int val, int x, int lx, int rx) {
        if (rx <= l || lx >= r || node[x].mx == 0) return; // here is the power of beats
        if (rx-lx==1) {
            node[x].sum /= val;
            node[x].mx /= val;
            return;
        }
        update(l, r, val, lnode, lx, md);
        update(l, r, val, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    void update(int l, int r, int val) {
        update(l, r, val, 0,0,n);
    }
    Node merge(Node &lf, Node &rt) {
        Node ans = Node();
        ans.sum = lf.sum + rt.sum;
        ans.mx = max(lf.mx, rt.mx);
        return ans;
    }
    Node get(int l, int r, int x, int lx, int rx) {
        if (rx <= l || lx >= r) return Node();
        if (l <= lx && rx <= r) return node[x];
        Node lf = get(l, r, lnode, lx, md);
        Node rt = get(l, r, rnode, md, rx);
        return merge(lf, rt);
    }
    int get(int l, int r) {
        return get(l, r, 0,0,n).sum;
    }
    void build(const vector<int> &v, int x, int lx, int rx) {
        if (rx-lx == 1) {
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
