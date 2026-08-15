const int N = 1e7+5;
int freq[N];
int lp[N];
vector<int> p;
void gen() {
    lp[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!lp[i]) {
            p.emplace_back(i);
            for (int j = i; j < N; j += i) {
                if (!lp[j]) {
                    lp[j] = i;
                }
            }
        }
    }
    for (int i = 2; i < N; ++i) {
        int x = i;
        while (x > 1) {
            ++freq[i];
            int l = lp[x];
            while (x%l ==0) x/=l;
        }
    }
}
