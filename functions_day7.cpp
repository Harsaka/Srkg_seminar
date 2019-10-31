#include <bits/stdc++.h>
using namespace std;

#define InputIterator typename
#define Semiring typename

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
int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int res = polynomial_value(a.begin(), a.end(), 3);
    cout << res << endl;
    cout << "" << endl;
    return 0;
}