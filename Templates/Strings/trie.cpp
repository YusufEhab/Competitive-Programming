#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+5;
struct Trie {
    int n;
    int nxt[N][26];
    int cnt[N];
    void clear() { // clear root
        n = 0;
        memset(nxt[0], -1, sizeof nxt[0]);
        cnt[0] = 0;
    }
    void insert(const string &s) {
        int cur = 0;
        for (auto &c: s) {
            if (nxt[cur][c-'a'] == -1) {
                nxt[cur][c-'a'] = ++n;
                memset(nxt[n], -1, sizeof nxt[n]);
                cnt[n] = 0;
            }
            cur = nxt[cur][c-'a'];
            ++cnt[cur];
        }
    }
    int get(const string &s) {
        int cur = 0;
        for (auto &c: s) {
            if (nxt[cur][c-'a'] == -1) return 0;
            cur = nxt[cur][c-'a'];
        }
        return cnt[cur];
    }
} trie;
// use trie.clear();
