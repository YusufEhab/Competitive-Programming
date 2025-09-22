#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

string ok(int val, int n, const vector<int> &v){
    int l = 0, r = n - 1;
    while(l <= r){
        int m = l + (r - l) / 2;
        if(v[m] == val)
            return "YES";
        else if(v[m] > val)
            r = m - 1;
        else
            l = m + 1;
    }
    return "NO";
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
        cout << ok(val, n, v) << endl;
    }
}
