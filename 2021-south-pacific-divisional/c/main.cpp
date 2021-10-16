#include <bits/stdc++.h>

using namespace std;

bool check(char c) {
    return ('A' <= c && c <= 'Z') ||
           ('a' <= c && c <= 'z');
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, limit;
    cin >> n >> limit;

    const int INF = 1e9;
    const int C = 256;
    vector<vector<int>> by_year(n, vector<int>(C, INF));

    for (int i = 0; i < n; i++) {
        string r;
        cin >> r;
        for (int j = 0; j < (int) r.size(); j++) {
            int t = r[j];
            if (by_year[i][t] == INF) by_year[i][t] = j + 1;
        }
    }

    vector<vector<int>> conse(n, vector<int>(C));
    vector<int> max_conse(C, 0);

    for (int t = 0; t < C; t++) {
        if (by_year[0][t] <= limit) {
            conse[0][t] = 1;
        } else {
            conse[0][t] = 0;
        }
        max_conse[t] = conse[0][t];
    }

    for (int i = 1; i < n; i++) {
        for (int t = 0; t < C; t++) {
            if (by_year[i][t] <= limit) {
                conse[i][t] = conse[i - 1][t] + 1;
            } else {
                conse[i][t] = 0;
            }
            max_conse[t] = max(max_conse[t], conse[i][t]);
        }
    }

    int longest_run = 0;
    for (int t = 0; t < C; t++) {
        if (!check(t)) continue;
        longest_run = max(longest_run, max_conse[t]);
    }

    int teams = 0;

    for (int t = 0; t < C; t++) {
        if (!check(t)) continue;
        if (max_conse[t] == longest_run) teams++;
    }

    cout << longest_run << ' ' << teams << '\n';

    return 0;
}
