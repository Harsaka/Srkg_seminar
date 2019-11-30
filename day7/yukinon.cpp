#include <bits/stdc++.h>
using namespace std;

// power
template<typename T, typename Op>
T natural_pow(T x, int n) {
    // 自然数乗ならeye は必要ない
    assert(n > 0);
    while (!(n & 1)) { n >>= 1; x = Op::mul(x, x); }

    T ret{x};
    while (n >>= 1) {
        x = Op::mul(x, x);
        if (n & 1) ret = Op::mul(ret, x);
    }

    return ret;
}

// Matrix
template<typename T>
using matrix = vector<vector<T>>;

template<typename T, typename Op>
struct MatrixOperator {
    static matrix<T> mul(const matrix<T>& a, const matrix<T>& b) {
        assert(a[0].size() == b.size());
        int l = a[0].size(),
            m = a.size(),
            n = b[0].size();
        matrix<T> ret(m, vector<T>(n, Op::zero()));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < l; ++k) {
                    ret[i][j] = Op::plus(ret[i][j],
                            Op::mul(a[i][k], b[k][j]));
                }
            }
        }
        return ret;
    }
};


struct BooleanOperator {
    static int zero() { return 0; }
    static int plus(int a, int b) { return a | b; }
    static int mul(int a, int b) { return a & b; }
};

template<typename T>
struct TropicalOperator {
    static T zero() { return numeric_limits<T>::max(); }
    static T plus(T a, T b) { return min(a, b); }
    static T mul(T a, T b) {
        if (a == zero() || b == zero()) {
            return zero();
        } else {
            return a + b;
        }
    }
};


void test_transitive_closure() {
    const int n = 7;
    const matrix<int> a = {
        {1, 1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1},
    };

    matrix<int> ret = natural_pow<matrix<int>,MatrixOperator<int,BooleanOperator>>(a, n);

    for (int i = 0; i < n; i++) {
        vector<int> friends;
        for (int j = 0; j < n; j++) if (i != j) {
            if (ret[i][j]) friends.push_back(j);
        }
        if (friends.size()) {
            cout << char('A' + i) << " gets along with: ";
            for (auto x : friends) cout << char('A' + x) << " ";
            cout << endl;
        }
        else {
            cout << char('A' + i) << " has no friend... :(" << endl;
        }
    }
}

void test_shortest_distance() {
    const int inf = TropicalOperator<int>::zero();
    const int n = 7;
    const matrix<int> a = {
        {0, 6, inf, 3, inf, inf, inf},
        {inf, 0, inf, inf, 2, 10, inf},
        {7, inf, 0, inf, inf, inf, inf},
        {inf, inf, 5, 0, inf, 4, inf},
        {inf, inf, inf, inf, 0, inf, 3},
        {inf, inf, 6, inf, 7, 0, 8},
        {inf, 9, inf, inf, inf , inf, 0}
    };

    matrix<int> ret = natural_pow<matrix<int>,MatrixOperator<int,TropicalOperator<int>>>(a, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) putchar(' ');
            if (ret[i][j] == inf) ret[i][j] = -1;
            cout << std::setw(2) << ret[i][j];
        }
        putchar('\n');
    }
}

// 経路復元
void test_restore_path() {
    const int inf = TropicalOperator<int>::zero();
    const int n = 7;
    const matrix<int> a = {
        {0, 6, inf, 3, inf, inf, inf},
        {inf, 0, inf, inf, 2, 10, inf},
        {7, inf, 0, inf, inf, inf, inf},
        {inf, inf, 5, 0, inf, 4, inf},
        {inf, inf, inf, inf, 0, inf, 3},
        {inf, inf, 6, inf, 7, 0, 8},
        {inf, 9, inf, inf, inf , inf, 0}
    };

    matrix<int> ret = natural_pow<matrix<int>,MatrixOperator<int,TropicalOperator<int>>>(a, n);

    matrix<int> pivot(n, vector<int>(n,-1));
    // pivot[i][j]: (i,j)最短経路間に存在するi,j以外の頂点

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) if (i != k && j != k) {
                if (ret[i][j] == TropicalOperator<int>::mul(
                            ret[i][k], ret[k][j])) {
                    pivot[i][j] = k;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            vector<int> path{i};

            // (u,v) -> (u, pivot[u][v])
            // (u,v) -> (pivot[u][v], v)
            // のようなグラフを考え, 経路を深さ優先探索

            stack<pair<int,int>> stk;
            stk.emplace(i, j);
            while (!stk.empty()) {
                pair<int,int> p;
                int u, v;
                tie(u, v) = p = stk.top(); stk.pop();
                if (pivot[u][v] == -1) {
                    path.push_back(v);
                    continue;
                }
                stk.emplace(pivot[u][v], v);
                stk.emplace(u, pivot[u][v]);
            }

            for (int k = 0; k < path.size(); ++k) {
                if (k > 0) printf("->");
                cout << (char)('A'+path[k]);
            }
            putchar('\n');
        }
    }

}


int main() {
    test_transitive_closure();
    putchar('\n');
    test_shortest_distance();
    putchar('\n');
    test_restore_path();
    putchar('\n');
}
