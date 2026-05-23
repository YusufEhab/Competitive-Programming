struct BIT {
    int n;
    vector<int> b;
    BIT(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        b.assign(n+1, 0);
    }
    void add(int i, int val) {
        while (i <= n) {
            b[i] += val;
            i += i & -i;
        }
    }
    int get(int i) {
        int res{};
        while (i > 0) {
            res += b[i];
            i -= i & -i;
        }
        return res;
    }
    int lower_bound(int sum) {
        int idx = 0;
        for (int i = n; i > 0; i >>= 1) {
            if (b[idx+i] < sum) {
                sum -= b[idx+i];
                idx += i;
            }
        }
        return idx + 1;
    }
};
