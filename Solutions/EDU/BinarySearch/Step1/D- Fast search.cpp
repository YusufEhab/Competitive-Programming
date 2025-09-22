#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

int ok(int n, int val1, int val2, const vector<int> &v){
    int l = 0, r = n - 1, idxl = -1, idxr = -1;
    while(l <= r){
        int m = l + (r - l) / 2;
        if(v[m] >= val1) {
            idxl = m;
            r = m - 1;
        }
        else
            l = m + 1;
    }
    l = 0, r = n - 1;
    while(l <= r){
        int m = l + (r - l) / 2;
        if(v[m] <= val2) {
            idxr = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    if(idxl == -1 || idxr == -1)
        return 0;
    int ans = idxr - idxl + 1;
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for(auto &i : v)
        cin >> i;
    sort(v.begin(), v.end());
    int q;
    cin >> q;
    while(q--){
        int val1, val2;
        cin >> val1 >> val2;
        cout << ok(n, val1, val2, v) << " ";
    }
}
