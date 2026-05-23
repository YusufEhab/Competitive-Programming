struct ST {
    vector<vector<int>> data;
    vector<int> logs;
    ST(const vector<int> &v) {
        int n = v.size();
        logs.assign(n+1, 0);
        for (int i = 2; i <= n; ++i) {
            logs[i] = logs[i/2] + 1;
        }
        data.assign(logs[n]+1, vector<int>(n));
        data[0] = v;
        for (int i = 1; i <= logs[n]; ++i) {
            int l = 1 << i;
            for (int j = 0; j + l <= n; ++j) {
                data[i][j] = merge(data[i-1][j], data[i-1][j+(l >> 1)]);
            }
        }
    }
    int merge(int &lf, int &rt){
        return min(lf, rt);
    }
    int get(int l, int r) {
        int len = r - l + 1;
        int lvl = logs[len];
        return merge(data[lvl][l], data[lvl][r-(1<<lvl)+1]);
    }
};
