struct mono {
    int n;
    vector<int> a; // 0-based
    vector<int> lf_greater, rt_greater; // i is the greatest (lf, rt) exclusive
    stack<int> stk;
    mono(const vector<int> &v) {
        a = v;
        n = v.size();
        lf_greater.assign(n, -1);
        rt_greater.assign(n, n);
        build();
    }
    void build(){
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && a[i] > a[stk.top()]) {
                rt_greater[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        stk = stack<int>();
        for (int i = n-1; i >= 0; --i) {
            while (!stk.empty() && a[i] > a[stk.top()]) {
                lf_greater[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
    }
};
