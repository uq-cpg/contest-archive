#include <bits/stdc++.h>

using namespace std;

struct Solver {
    int nr, nc, n, m;
    vector<vector<int>> park;

    Solver() {
        cin >> nr >> nc >> n >> m;
        park.resize(nr + 1, vector<int>(nc + 1, 0));

        for (int i = 0; i < nr; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < nc; j++) {
                if (s[j] == 'A') park[i + 1][j + 1] = 1;
            }
        }

        for (int i = 1; i <= nr; i++) {
            for (int j = 1; j <= nc; j++) {
                park[i][j] += park[i][j - 1];
                park[i][j] += park[i - 1][j];
                park[i][j] -= park[i - 1][j - 1];
            }
        }
        int ans = solve(n, m);
        if (n != m) {
            ans += solve(m, n);
        }
        cout << ans << '\n';
    }

    int solve(int w, int h) {
        int res = 0;
        for (int i = 1; i + w - 1 <= nr; i++) {
            for (int j = 1; j + h - 1 <= nc; j++) {
                int ants = park[i + w - 1][j + h - 1];
                ants -= park[i + w - 1][j - 1];
                ants -= park[i - 1][j + h - 1];
                ants += park[i - 1][j - 1];
                if (ants == 0) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Solver s;

    return 0;
}
