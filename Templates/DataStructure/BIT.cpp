struct BIT {
    int n;
    vector<int> b;
    BIT(int _n) {
        n = _n;
        b.assign(n+1, 0);
    }
    int get(int i) {
        int res{};
        while (i > 0) {
            res += b[i];
            i -= (i & -i);
        }
        return res;
    }
    int add(int i, int val) {
        while (i <= n) {
            b[i] += val;
            i += (i & -i);
        }
    }
    //helper functions
    int get(int l, int r) {
        return get(r) - get(l-1);
    }
    int getIdx(int i) {
        return get(i) - get(i-1);
    }
    void set(int i, int val) {
        int old = getIdx(i);
        add(i, -old+val);
    }
};
