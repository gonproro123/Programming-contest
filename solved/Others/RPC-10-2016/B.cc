// TLE
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define debug(x) cout << #x " = " << (x) << endl

const long long mod = 1e9 + 7;
const int MN = 5 * 100000 + 100;
const int SN = 717;

int a[MN];
long long p[MN];
long long pinv[MN];

long long mod_pow(long long b, long long e, long long m) {
  long long ans = 1;
  while (e > 0) {
    if (e & 1) ans = (ans * b) % m;
    b = (b * b) % m;
    e >>= 1;
  }
  return ans;
}

struct query {
  int a, b, id;
  query() {}
  query(int x, int y, int i) : a(x), b(y), id(i) {}

  bool operator < (const query &o) const {
    return b < o.b;
  }
};

long long add(long long ant, int id) {
  long long x = (ant * p[id] + ant + p[id]) % mod;
  return x;
}

long long rem(long long ant, int id) {
  long long y = ant - p[id];
  long long den = pinv[id];
  return (y * den) % mod;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  int n, P;
  vector<query> s[SN];
  while (cin >> n >> P) {
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      p[i] = mod_pow(P, a[i], mod);
      pinv[i] = mod_pow(p[i] + 1, mod - 2, mod);
    }
    for (int i = 0; i < SN; ++i) s[i].clear();

    int q; cin >> q;
    int a, b;
    for (int i = 0; i < q; ++i) {
      cin >> a >> b;
      a--;b--;
      s[a / SN].push_back(query(a, b, i));
    }

    for (int i = 0; i < SN; ++i) {
      sort(s[i].begin(), s[i].end());
    }

    vector<long long> ans(q);
    for (int b = 0; b < SN; ++b) {
      if (s[b].size() == 0) continue;
      int i = s[b][0].a;
      int j = s[b][0].a;
      long long cur = p[i];
      for (int k = 0; k < s[b].size(); ++k) {
        int L = s[b][k].a;
        int R = s[b][k].b;

        while (j + 1 <= R && j + 1 < n) {
          cur = add(cur, j + 1);
          j++;
        }

        while (j > R) {
          if (i <= j) cur = rem(cur, j);
          j--;
        }

        while (i < L) {
          if (i <= j) cur = rem(cur, i);
          i++;
        }

        while (i - 1 >= L && i >= 1) {
          cur = add(cur, i - 1);
          i--;
        }
        ans[s[b][k].id] = cur;
      }
    }

    for (int i = 0; i < q; ++i) {
      cout << ans[i] << endl;
    }

  }
  return 0;
}
