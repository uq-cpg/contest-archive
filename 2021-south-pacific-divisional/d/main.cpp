#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(n, -1));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        if (g[u][v] != -1 && g[u][v] != w) {
            cout << "wake up\n";
            return 0;
        }
        g[u][v] = w;
    }

    vector<vector<int>> s(n, vector<int>(n, INF));
    vector<vector<int>> l(n, vector<int>(n, -INF));

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (g[u][v] != -1) {
                s[u][v] = g[u][v];
                l[u][v] = g[u][v];
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (s[u][k] == INF || s[k][v] == INF) continue;
                s[u][v] = min(s[u][v], s[u][k] + s[k][v]);
            }
        }
    }


    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (l[u][k] == -INF || l[k][v] == -INF) continue;
                l[u][v] = max(l[u][v], l[u][k] + l[k][v]);
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (s[u][v] != INF && l[u][v] != -INF && s[u][v] != l[u][v]) {
                cout << "wake up\n";
                return 0;
            }
        }
    }

    cout << "we live in a society\n";

    return 0;
}
