#include <bits/stdc++.h>
using namespace std;

#define InputIterator typename
#define Semiring typename


// 多項式の計算 (Σa_i × x*x*...*x)
// x にはどんな構造を乗せられるか
// 加算(+) が定義されている(c = b1 + b2)
// 定数倍(×) が可能
// 乗算(*) が定義されている
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

polynomial<real> gcd(polynomial<real> a, polynomial<real> b) {
    while (b != polynomial<real>(0)) {
        a = remainder(a, b);
        swap(a, b);
    }
    return a;
}
int main(){
    return 0;
}
