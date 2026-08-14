const int mod = 1e7+19;
const int N = 1e5+5;
int fact[N], inv[N];
int pw(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void gen() {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) {
        fact[i] = fact[i-1]*i % mod;
    }
    inv[N-1] = pw(fact[N-1], mod-2);
    for (int i = N-2; i >= 0; --i) {
        inv[i] = inv[i+1]*(i+1) % mod;
    }
}
int nCr(int n, int r) {
  if (n < 0 || r > n) return 0;
  return fact[n] * inv[n-r] % mod * inv[r] % mod;
}
int nPr(int n, int r) {
  if (n < 0 || r > n) return 0;
  return fact[n] * inv[n-r] % mod;
}
