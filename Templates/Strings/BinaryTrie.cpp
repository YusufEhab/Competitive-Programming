#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+5;
struct BinTrie {
    int n;
    int nxt[N][2];
    int cnt[N];
    void clear() {
        n = 0;
        memset(nxt[0], -1, sizeof nxt[0]);
        cnt[0] = 0;
    }
    void insert(int val, int t) { // t 1 insert, t 2 erase
        int cur = 0;
        for (int i = 30; i >= 0; --i) {
            int b = (val >> i) & 1;
            if(nxt[cur][b] == -1) {
                nxt[cur][b] = ++n;
                memset(nxt[n], -1, sizeof nxt[n]);
                cnt[n] = 0;
            }
            cur = nxt[cur][b];
            cnt[cur] += t;
        }
    }
    int get(int val) { // max xor
        int cur = 0, ans = 0;
        for (int i = 30; i >= 0; --i) {
            int b = ((val >> i) & 1) ^ 1;
            if (nxt[cur][b] != -1 && cnt[nxt[cur][b]] > 0) {
                cur = nxt[cur][b];
                ans |= (1 << i);
            }else if (nxt[cur][b^1] != -1 && cnt[nxt[cur][b^1]] > 0) {
                cur = nxt[cur][b^1];
            } else {
                return ans;
            }
        }
        return ans;
    }
} trie;
// trie.clear();
