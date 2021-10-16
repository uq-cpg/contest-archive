#include <bits/stdc++.h>

using namespace std;

struct Solver {
    Solver() {
        int R, C, k;
        cin >> R >> C >> k;
        vector<vector<int>> g(R + 1, vector<int>(C + 1));

        for (int r = 1; r <= R; r++) {
            for (int c = 1; c <= C; c++) {
                cin >> g[r][c];
            }
        }

        vector<vector<int64_t>> score(R + 1, vector<int64_t>(C + 1, 0));

        for (int r = 1; r <= R; r++) {
            for (int c = 1; c + k - 1 <= C; c++) {
                for (int i = 0; i < k; i++) {
                    score[r][c] += g[r][c + i];
                }
            }
        }

        vector<vector<int64_t>> dp(R + 1, vector<int64_t>(C + 1, 0));
        vector<vector<int>> trace(R + 1, vector<int>(C + 1));

        for (int r = 1; r <= R; r++) {
            for (int c = 1; c + k - 1 <= C; c++) {
                dp[r][c] = score[r][c];
                int st = max(c - k + 1, 0);
                int en = min(c + k - 1, C - k + 1);
                int best_pc = -1;
                int64_t best_pscore = -1;
                assert(st <= en);
                for (int pc = st; pc <= en; pc++) {
                    if (dp[r - 1][pc] > best_pscore) {
                        best_pc = pc;
                        best_pscore = dp[r - 1][pc];
                    }
                }
                assert(best_pc != -1);
                dp[r][c] += best_pscore;
                trace[r][c] = best_pc;
            }
        }

        int final = -1;
        int64_t best_score = 0;
        vector<int> path;

        for (int c = 1; c + k - 1 <= C; c++) {
            if (best_score < dp[R][c]) {
                best_score = dp[R][c];
                final = c;
            }
        }

        {
            int c = final;

            for (int r = R; r > 0; r--) {
                path.push_back(c);
                c = trace[r][c];
            }
        }

        reverse(path.begin(), path.end());

        for (int r = 0; r <= R - 1; r++) {
            for (int c = 1; c <= C; c++) {
                if (c < path[r] || c > path[r] + k - 1) {
                    cout << '.';
                } else {
                    cout << 'X';
                }
            }
            cout << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Solver s;

    return 0;
}
