  // for (int x = l; x <= r; ++x) {
  //     for (int d = 1; d <= x; ++d) {
  //         ans += (n-x)%d == 0;
  //     }
  // }

/*
(n-x)%d == 0
n%d == x%d
(n%d)+kd = x 
to get first x not less than L
  F = L + ((n%d) - L % d + d) % d
to count number x not greater than R 
  (R - F)/d+1
*/
  for (int d = 1; d <= r; ++d) {
      int lf = max(l, d);
      int f = lf+((n%d)-lf%d+d)%d;
      int cnt = (r-f)/d+1;
      if (f <= r) ans += cnt;
  }
  cout << ans;
