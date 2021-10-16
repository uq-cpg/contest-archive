#include <bits/stdc++.h>

using namespace std;

struct Solver {
    Solver() {
        int n, m;
        cin >> n >> m;

        vector<int> has(n, 0);

        for (int i = 0; i < n; i++) {
            int k = 0; cin >> k;
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                x--;
                has[i] |= (1 << x);
            }
        }

        const int INF = 1e9;
        int ans = INF;

        for (int who = 0; who < (1 << n); who++) {
            int get = 0;
            for (int i = 0; i < n; i++) {
                if (who & (1 << i)) {
                    get |= has[i];
                }
            }
            if (get == (1 << m) - 1) {
                ans = min(ans, __builtin_popcount(who));
            }
        }

        if (ans == INF) cout << "-1\n";
        else cout << ans << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Solver s;

    return 0;
}
