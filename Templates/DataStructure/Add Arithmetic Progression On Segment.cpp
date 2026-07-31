struct Node {
    int sum, a, d;
    bool is_lazy;
    Node() {
        sum = a = d = 0;
        is_lazy = 0;
    }
    Node(int x) {
        sum = x;
        a = d = 0;
        is_lazy = 0;
    }
    void update(int a1, int d1, int lx, int rx) {
        int t = (rx-lx-1)*(rx-lx)/2;
        sum = sum + a1*(rx-lx) + d1 * t;
        a += a1;
        d += d1;
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
    void build(vector<int> &v, int x, int lx, int rx) {
        if (rx-lx == 1) {
            if (lx < v.size()) node[x] = Node(v[lx]);
            return;
        }
        build(v, lnode, lx, md);
        build(v, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    void build(vector<int> &v) {
        build(v, 0,0,n);
    }
    Node merge(Node &lf, Node &rt) {
        Node ans = Node();
        ans.sum = lf.sum + rt.sum;
        return ans;
    }
    void propagate(int x, int lx, int rx) {
        if (rx-lx == 1 || node[x].is_lazy == 0) return;
        node[lnode].update(node[x].a, node[x].d, lx, md);
        node[rnode].update(node[x].a + node[x].d*(md-lx), node[x].d, md, rx);
        node[x].a = node[x].d = node[x].is_lazy = 0;
    }
    void update(int l, int r, int a, int d, int x, int lx, int rx) {
        if (l <= lx && rx <= r) {
            node[x].update(a+d*(lx-l), d, lx, rx);
            return;
        }
        if (rx <= l || lx >= r) return;
        propagate(x, lx, rx);
        update(l, r, a, d, lnode, lx, md);
        update(l, r, a, d, rnode, md, rx);
        node[x] = merge(node[lnode], node[rnode]);
    }
    void update(int l, int r, int a, int d) {
        update(l, r, a, d, 0,0,n);
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
