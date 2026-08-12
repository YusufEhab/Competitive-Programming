#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5+5;
struct Query {
    int l, r, idx;
};
struct Mo {
    int n, sq, ans;
    vector<int> arr;
    int freq[N]{};
    Mo(const vector<int>& v) {
        arr = v;
        n = v.size();
        sq = sqrt(n)+1;
        ans = 0;
    }
    void add(int idx) {  //edit this
        if (arr[idx] > n) return;
        ans -= freq[arr[idx]] == arr[idx];
        ++freq[arr[idx]];
        ans += freq[arr[idx]] == arr[idx];
    }
    void del(int idx) { //edit this
        if (arr[idx] > n) return;
        ans -= freq[arr[idx]] == arr[idx];
        --freq[arr[idx]];
        ans += freq[arr[idx]] == arr[idx];
    }
    vector<int> solve(vector<Query>& q) {
        sort(q.begin(), q.end(), [&](auto &lf, auto &rt) {
            if (lf.l/sq == rt.l/sq) return (lf.l/sq) & 1? lf.r > rt.r : lf.r < rt.r;
            return lf.l/sq < rt.l/sq;
        });
        int l = q[0].l, r = q[0].l;
        add(l);
        vector<int> res(q.size());
        for (auto &[lq, rq, idx]: q) {
            while (r < rq) add(++r);
            while (l > lq) add(--l);
            while (l < lq) del(l++);
            while (r > rq) del(r--);
            res[idx] = ans;
        }
        return res;
    }
};
void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    vector<Query> Q(q);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        Q[i] = {l-1, r-1, i};
    }
    Mo mo(a);
    auto res = mo.solve(Q);
    for (auto &i: res) cout << i << "\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC = 1;
    // cin >> TC;
    while (TC--) {
        solve();
        cout << '\n';
    }
}
