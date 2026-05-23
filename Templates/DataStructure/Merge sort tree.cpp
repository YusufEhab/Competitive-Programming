typedef tree<int , null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> OrderedSet;
// find_by_order : element at index i
// order_of_key  : how many elements < A

void erase(OrderedSet &t, int v){
    int rank = t.order_of_key(v);
    auto it = t.find_by_order(rank);
    t.erase(it);
}

struct SegTree {
    int tree_size;
    vector<OrderedSet> SegData;
    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size <<= 1;
        SegData.assign(2 * tree_size, {});
    }

    OrderedSet merge(const OrderedSet & lf, const OrderedSet & ri) {
        OrderedSet ans;
        for(auto &ele : lf) ans.insert(ele);
        for(auto &ele : ri) ans.insert(ele);
        return ans;
    }

    void build(const vector<int> & arr, int node, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < arr.size())
                SegData[node].insert(arr[lx]);
            return;
        }

        int mid = (lx + rx) / 2;
        build(arr, 2 * node + 1, lx, mid);
        build(arr, 2 * node + 2, mid, rx);

        SegData[node] = merge(SegData[2 * node + 1], SegData[2 * node + 2]);
    }
    void build(const vector<int> & arr) {
        build(arr, 0, 0, tree_size);
    }

    void set(int idx, int old_val, int new_val, int node, int lx, int rx) {
        erase(SegData[node], old_val);
        SegData[node].insert(new_val);
        if(rx - lx == 1)
            return;

        int mid = (lx + rx) / 2;
        if(idx < mid)
            set(idx, old_val, new_val, 2 * node + 1, lx, mid);
        else
            set(idx, old_val, new_val, 2 * node + 2, mid, rx);
    }
    void set(int idx, int old_val, int new_val) {
        set(idx, old_val, new_val, 0, 0, tree_size);
    }

    int less(int l, int r, int x, int node, int lx, int rx) {
        if(lx >= r || rx <= l)
            return 0;
        if(lx >= l && rx <= r) {
            return SegData[node].order_of_key(x);
        }

        int mid = (lx + rx) / 2;
        int lf = less(l, r, x, 2 * node + 1, lx, mid);
        int ri = less(l, r, x, 2 * node + 2, mid, rx);
        return lf + ri;
    }

    int less(int l, int r, int x) {
        return less(l, r, x, 0, 0, tree_size);
    }
};
