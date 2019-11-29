#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i = 0; i < n; i++)

#define InputIterator typename
#define Semiring typename
#define Polynomial typename
#define MatrixType typename

template <MatrixType T>
using matrix = vector<vector<T>>;

using ll = long long;
using vd = vector<double>;
using vvd = vector<vector<double>>;
using P = pair<ll, ll>;

const int inf = 1e9;
const double eps = 0.00001;

const vector<vector<bool>> matrix_8_7 = {
    {1, 1, 0, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 1}
};
const vector<vector<int>> matrix_8_8 = {
    {0, 6, inf, 3, inf, inf, inf},
    {inf, 0, inf, inf, 2, 10, inf},
    {7, inf, 0, inf, inf, inf, inf},
    {inf, inf, 5, 0, inf, 4, inf},
    {inf, inf, inf, inf, 0, inf, 3},
    {inf, inf, 6, inf, 7, 0, 8},
    {inf, 9, inf, inf, inf , inf, 0}
};

// 6章の復習
template <typename T>
matrix<T> matrix_mul(const matrix<T> &l, const matrix<T> &r) {
    matrix<T> ret(l.size(), std::vector<T>(r[0].size()));
    for (int i = 0; i < (int)l.size(); i++) {
        for (int k = 0; k < (int)r.size(); k++) {
            for (int j = 0; j < (int)r[0].size(); j++) {
                ret[i][j] = ret[i][j] + l[i][k] * r[k][j];
            }
        }
    }
    return ret;
}

// 単位元
template <typename T>
matrix<T> eye(const int n) {
    matrix<T> ret(n, vector<T>(n));
    for (int i = 0; i < n; i++) ret[i][i] = 1;
    return ret;
}

// 行列累乗
// return X ^ n
// 累乗自体は対数時間だが行列乗算でO(n^3)かかるので全体でO(n^3logn)
template <typename T>
matrix<T> matrix_pow(matrix<T> x, int n) {
    auto ret = eye<T>(x.size());
    while (n) {
        if (n & 1) ret = matrix_mul(ret, x);
        x = matrix_mul(x, x);
        n /= 2;
    }
    return ret;
}

// 7章

// 多項式の計算 (Σa_i × x*x*...*x)
template <InputIterator I, Semiring R>
R polynomial_value(I first, I last, R x) {
    if (first == last) return R(0);
    R sum(*first);
    while (++first != last) {
        sum *= x;
        sum += *first;
    }
    return sum;
}

void test_polynomial_value() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int res = polynomial_value(a.begin(), a.end(), 3);
    cout << res << endl;
    return;
}

vd remainder(vd &a, vd &b) {
    int alen = a.size(), blen = b.size();
    double q = a[0] / b[0];
    vd r;
    int flg = 1;
    for (int i = 0; i < blen; i++) {
        if (abs(a[i] - b[i] * q) < eps) {
            if (flg) continue;
        }
        else flg = 0;
        r.push_back(a[i] - b[i] * q);
    }
    for (int i = blen; i < alen; i++) {
        r.push_back(a[i]);
    }
    if (r.size() == 0) r.push_back(0);
    return r;
}

vd gcd(vd &a, vd &b) {
    while (abs(b[0]) > eps) {
        a = remainder(a, b);
        swap(a, b);
    }
    return a;
}

void print_polynomial_gcd() {
    cout << "input the size of polynomial A:";
    int n, m;
    cin >> n;
    vd a(n), b(m);
    cout << "input polynomial A:";
    REP(i, n) cin >> a[i];
    cout << "input the size of polynomial B:";
    cin >> m;
    cout << "input polynomial B:";
    REP(i, m) cin >> b[i];

    vd res = gcd(a, b);

    cout << endl;
    for (auto x : res) {
        cout << x << " ";
    }
    cout << endl;
}

// 8.6 応用:ソーシャルネットワークと最短経路
// a : n * n 行列 ... 隣接行列

template <typename T>
matrix<T> bool_mul(const matrix<T> &l, const matrix<T> &r) {
    matrix<T> ret(l.size(), std::vector<T>(r[0].size()));
    for (int i = 0; i < (int)l.size(); i++) {
        for (int k = 0; k < (int)r.size(); k++) {
            for (int j = 0; j < (int)r[0].size(); j++) {
                ret[i][j] = ret[i][j] | (l[i][k] & r[k][j]); // ここ代入演算子 |= 使ったら error になるの謎
            }
        }
    }
    return ret;
}

// 単位元
template <typename T>
matrix<T> bool_eye(const int n) {
    matrix<T> ret(n, vector<T>(n, false));
    for (int i = 0; i < n; i++) ret[i][i] = true;
    return ret;
}

// 行列累乗
// return X ^ n ... O(n^3logn)
template <typename T>
matrix<T> bool_pow(matrix<T> x, int n) {
    auto ret = bool_eye<T>(x.size());
    while (n) {
        if (n & 1) ret = bool_mul(ret, x);
        x = bool_mul(x, x);
        n /= 2;
    }
    return ret;
}
template <typename T>
matrix<T> transitive_closure(matrix<T> a, int n) {
    matrix<T> res = bool_pow(a, n);
    return res;
}

void print_transitive_closure() {
    auto a = matrix_8_7;
    int n = a.size();
    auto res = transitive_closure(a, n - 1);
    for (int i = 0; i < n; i++) {
        vector<int> friends;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            if (res[i][j]) friends.push_back(j);
        }
        if (friends.size() == 0) {
            cout << char('A' + i) << " has no friend... :(" << endl;
        }
        else {
            cout << char('A' + i) << " gets along with :";
            for (auto x : friends) cout << char('A' + x) << " ";
            cout << endl;
        }
    }
}

// 最短経路

template <typename T>
matrix<T> tropical_mul(const matrix<T> &l, const matrix<T> &r) {
    int len = l[0].size();
    matrix<T> ret(len, vector<T>(len, inf));
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len; k++) {
                ret[i][j] = min(ret[i][j], l[i][k] + r[k][j]);
            }
        }
    }
    return ret;
}

// 行列累乗 for tropical
// return X ^ n ... O(n^3logn)
template <typename T>
matrix<T> tropical_pow(matrix<T> x, int n) {
    int len = x.size();
    matrix<T> ret(len, vector<T>(len, inf));
    for (int i = 0; i < len; i++) ret[i][i] = 0;
    while (n) {
        if (n & 1) ret = tropical_mul(ret, x);
        x = tropical_mul(x, x);
        n /= 2;
    }
    return ret;
}

// 全頂点対最短距離, O(n^3logn)
template <typename T>
matrix<T> shortest_distance(matrix<T> a, int n) {
    matrix<T> res = tropical_pow(a, n);
    return res;
}

void print_shortest_distance() {
    auto a = matrix_8_8;
    int n = a.size();
    auto res = shortest_distance(a, n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (res[i][j] == inf) res[i][j] = -1;
            cout << std::setw(2) << res[i][j] << " ";
        }
        cout << endl;
    }
}

// 全頂点対最短距離 O(n^3)
void print_Warshall_Floyd() {
    auto d = matrix_8_8;
    int n = d.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] == inf) d[i][j] = -1;
            cout << std::setw(2) << d[i][j] << " ";
        }
        cout << endl;
    }
}

// 経路復元
vector<int> restore_path(int from, int to) {
    auto d = matrix_8_8;
    int n = d.size();
    auto g = shortest_distance(d, n - 1);
    vector<int> p;
    int cur = from;
    while (cur != to) {
        // nは頂点数
        for (int i = 0; i < n; i++) {
            // 辺cur -- i が最短経路に用いられたかどうかを調べる
            // cur -- i -- to の距離を計算すればいい
            if (i != cur && d[cur][i] + g[i][to] == g[cur][to]) {
                cur = i;
                p.push_back(i);
                break;
            }
        }
    }
    return p;
}

void print_restore_path() {
    cout << "input Start point s:";
    int s, t;
    cin >> s;
    cout << "input Goal point t:";
    cin >> t;
    auto xxx = restore_path(s, t);
    cout << char('A' + s) << "->";
    for (auto x : xxx) {
        cout << char('A' + x);
        if (x != t) cout << "->";
    }
    cout << endl;
}

int main(){
    //print_polynomial_gcd();
    //print_transitive_closure();
    //print_shortest_distance();
    //print_Warshall_Floyd();
    return 0;
}
