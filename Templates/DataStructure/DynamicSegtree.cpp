#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int sum = 0;
    TreeNode *lnode = nullptr, *rnode = nullptr;
    void change(int x) {
        sum += x;
    }
};
struct DynamicSegtree {
#define md ((lx+rx)>>1)
#define Node TreeNode*
    int n;
    Node root;
    DynamicSegtree(int sz) {
        n = sz;
        root = new TreeNode;
    }
    void update(int idx, int val, Node &x, int lx, int rx) {
        if (rx-lx == 1) {
            x->change(val);
            return;
        }
        if (idx < md) {
            if (x->lnode == nullptr) x->lnode = new TreeNode;
            update(idx, val, x->lnode, lx, md);
        }
        else {
            if (x->rnode == nullptr) x->rnode = new TreeNode;
            update(idx, val, x->rnode, md, rx);
        }
        x->sum = (x->lnode == nullptr? 0 : x->lnode->sum) + (x->rnode == nullptr? 0 : x->rnode->sum);
    }
    void update(int idx, int val) {
        update(idx, val, root, 0, n);
    }
    int get(int l, int r, Node &x, int lx, int rx) {
        if (x == nullptr || rx <= l || lx >= r) return 0;
        if (l <= lx && rx <= r) return x->sum;
        int lf = get(l, r, x->lnode, lx, md);
        int rt = get(l, r, x->rnode, md, rx);
        return lf + rt;
    }
    int get(int l, int r) {
        return get(l, r, root, 0, n);
    }
#undef md
#undef Node
};

signed main() {
    ios::sync_with_stdio(0);cin.tie(0);

    DynamicSegtree tree(1e9+5);
    tree.update(5, 3);
    tree.update(7, 2);
    tree.update(1e8, 6);
    cout << tree.get(0, 1e9);
}
