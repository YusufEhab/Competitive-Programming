struct mono {
    int n;
    vector<int> a;
    vector<int> lf_greater, rt_greater; // i is the greatest (lf, rt) open interval exclusive 
    stack<int> stk;
    mono(const vector<int> &v) {
        a = v;
        n = v.size();
        lf_greater.assign(n, 0);
        rt_greater.assign(n, n+1);
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
        while (!stk.empty()) stk.pop();
        for (int i = n; i > 0; --i) {
            while (!stk.empty() && a[i] > a[stk.top()]) {
                lf_greater[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
    }
};
