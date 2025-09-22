#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

int ok(int n, int val, const vector<int> &v){
    bool flag = true;
    int l = 0, r = n - 1, ans = n + 1;
    while(l <= r){
        int m = l + (r - l) / 2;
        if(v[m] >= val) {
            flag = false;
            ans = m;
            r = m - 1;
        }
        else
            l = m + 1;
    }
    if(flag)
        return ans;
    return ans + 1;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(auto &i : v)
        cin >> i;
    while(k--){
        int val;
        cin >> val;
        cout << ok(n, val, v) << endl;
    }
}
