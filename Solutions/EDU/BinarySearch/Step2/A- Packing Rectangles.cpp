#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

bool ok(int w, int h, int m, int n){
    int x = m / h;
    int y = m / w;
    if(x > 1e18 / y || x * y >= n)
        return true;
    return false;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    int w, h, n;
    cin >> w >> h >> n;
    int l = 0, r = 1e18, ans = 0;
    while(l <= r){
        int m = l + (r - l) / 2;
        if(ok(w, h, m, n)){
            ans = m;
            r = m - 1;
        }
        else
            l = m + 1;
    }
    cout << ans;
}
