#include <bits/stdc++.h>

using namespace std;

inline int log2Floor(int x) {
    return x ? 32 - 1 - __builtin_clz(x) : -1;
}

inline int leastPow2Geq(int x) {
    assert(x > 0);
    return 1 << log2Floor(2 * x - 1);
}

template <typename T, T empty=T()>
struct SegmentTree {
    struct Node {
        T val;
        T lazy;
        bool is_lazy;

        Node(T val_, T lazy_ = empty, bool is_lazy_ = false) :
            val(val_), lazy(lazy_), is_lazy(is_lazy_) {}
    };

    using Merge = function<T(const T&, const T&)>;
    using Apply = function<void(T&, const T&)>;

    int n;
    vector<Node> t;
    Merge merge;
    Apply apply;

    inline int left(int i) { return i << 1; }
    inline int right(int i) { return (i << 1) + 1; }

    void pushDown(int node) {
        if (t[node].is_lazy) {
            apply(t[left(node)].val, t[node].lazy);
            apply(t[left(node)].lazy, t[node].lazy);
            apply(t[right(node)].val, t[node].lazy);
            apply(t[right(node)].lazy, t[node].lazy);
            t[node].lazy = empty;
            t[node].is_lazy = false;
            t[left(node)].is_lazy = t[right(node)].is_lazy = true;
        }
    }

    T query(int from, int to, int node, int node_from, int node_to) {
        if (from <= node_from && node_to <= to) {
            return t[node].val;
        }
        if (to < node_from || node_to < from) {
            return 0;
        }
        pushDown(node);
        int mid = (node_from + node_to) / 2;
        return merge(
                query(from, to, left(node), node_from, mid),
                query(from, to, right(node), mid + 1, node_to)
        );
    }

    void update(int from, int to, T d, int node, int node_from, int node_to) {
        if (from <= node_from && node_to <= to) {
            apply(t[node].val, d);
            apply(t[node].lazy, d);
            t[node].is_lazy = true;
            return;
        }
        if (to < node_from || node_to < from) {
            return;
        }
        pushDown(node);
        int mid = (node_from + node_to) / 2;
        update(from, to, d, left(node), node_from, mid);
        update(from, to, d, right(node), mid + 1, node_to);
        t[node].val = merge(t[left(node)].val, t[right(node)].val);
    }

    SegmentTree(vector<T>& a, Merge merge_, Apply apply_) :
        merge(merge_), apply(apply_) {
        n = leastPow2Geq(a.size());
        t.resize(n << 1, Node(empty));
        for (int i = 0; i < (int) a.size(); i++) {
            t[n + 1].val = a[i];
        }
        for (int i = n - 1; i > 0; i--) {
            t[i].val = merge(t[left(i)].val, t[right(i)].val);
        }
    }

    T query(int from, int to) { return query(from, to, 1, 0, n - 1); }
    void update(int from, int to, T d) {
        return update(from, to, d, 1, 0, n - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    auto apply = [](int64_t& val, const int64_t& d) {
        val += d;
    };
    auto merge = [](const int64_t& a, const int64_t& b) {
        return a + b;
    };

    int n;
    cin >> n;
    vector<int> order(n);

    for (int i = 0; i < n; i++) {
        cin >> order[i];
    }

    vector<int64_t> cnt(n + 1, 0);
    SegmentTree<int64_t> st(cnt, merge, apply);

    int64_t ans = 0;

    for (int i = 0; i < n; i++) {
        ans += st.query(0, order[i]);
        st.update(order[i], order[i], 1);
    }

    cout << ans << '\n';

    return 0;
}
