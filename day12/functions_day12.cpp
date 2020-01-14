#include <bits/stdc++.h>
using namespace std;
#define MultiplicativeSemigroup typename
#define MultiplicativeMonoid typename
#define MultiplicativeGroup typename
#define Integer typename
#define Regular typename
#define InputIterator typename
#define Semiring typename
#define SemigroupOperation typename
#define MonoidOperation typename
#define GroupOperation typename
#define NoncommutativeAdditiveMonoid typename
#define MultiplicativeMonoid typename
#define AdditiveGroup typename
#define MultiplicativeGroup typename

using ll = long long;


template <Integer N>
bool odd(N n) { 
    return n & 0x1;
}

template <Integer N>
bool even(N n) {
    return !odd(n);
}

template <Integer N>
N half(N n){
    return n >> 1;
}

template <Integer I>
bool divides_(const I& i, const I& n) {
    return n % i == I(0);
}

template <Integer I>
I smallest_divisor(I n){
    // 事前条件: n > 0
    if (even(n)) return I(2);
    for (I i(3); i * i <= n; i += I(2)) {
        if (divides_(i, n)) return i;
    }
    return n;
}

template <Integer I>
bool is_prime(const I& n) {
    return n > I(1) && smallest_divisor(n) == n;
}

/*

template <Integer I>
struct modulo_multiply {
    I modulus;
    modulo_multiply(const I& i) : modulus(i) {}

    I operator()(const I& n, const I& m) const {
        return (n * m) % modulus;
    }
};



// 単位元
template <Integer I>
I identity_element(const modulo_multiply<I> k) {
    return I(1);
}

*/

template <Integer I>
I power_integer(I a, I n, I mod) {
    I res = I(1);
    // 事前条件:n >= 0
    if (n == 0) return res;
    while (true) {
        if (odd(n)) {
            res *= a;
            res %= mod;
            if (n == 1) return res;
        }
        a *= a;
        a %= mod;
        n = half(n);
    }
}

template <Integer I>
I multiplicative_inverse_fermat(I a, I p, I mod) {
    // 事前条件: p は素数かつ a > 0
    return power_integer(a, p - 2, mod);
}

template <Integer I>
I gcd(I a, I b){
  	if (b == I(0)) return a;
  	return gcd(b, a % b);
}

template <Integer I>
bool is_coprime (I a, I b) {
    return (gcd(a, b) == I(1));
}

// fermat test
template <Integer I>
bool fermat_test(I n, I witness) {
    // 事前条件: 0 < witness < n
    if (!is_coprime(n, witness)) return false; // 互いに素でない証拠がとれるなら n は合成数
    I remainder(power_integer(witness, n - I(1), n));
    return remainder == I(1);
}

void print_fermat_test() {
    cout << "Input number n:" << endl;
    ll n;
    cin >> n;
    bool flg = true;
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<ll> dist(1, n - 1);
    for (int i = 0; i < 1e6; i++) {
        ll wit = dist(mt);
        if (!fermat_test(n, wit)) {
            flg = false;
            break;
        }
    }
    if (flg) cout << "probably prime." << endl;
    else cout << "not prime." << endl;
}

// retun n の約数の集合, O(sqrt(n))
template <Integer I>
vector<I> divisors_set(I n){
  	vector<I> res;
	for(I i = 2; i * i <= n; i++){
		if(divides_(i, n)) res.push_back(i);
	}
  	for (auto p : res) {
		if(p >= n / p) break;
		res.push_back(n / p);
	}
    sort(res.begin(), res.end());
	return res;
}

// 問題13.1 : n がカーマイケル数かどうかを返す. 
// カーマイケル数 : n と互いに素な任意の証拠 b(0 < b < n) に対して b^(n - 1) = 1 (mod n)
// 定義通り実装すると O(n^2logn)
// 枝刈り的に動作し, n = 1e6くらいまでは後述の korsert の判別法より高速に動く.
template <Integer I>
bool is_carmichael(I n) {
    // 事前条件: n は合成数
    if (is_prime(n)) return false;
    for (I b = I(1); b < n; b++) {
        if (!is_coprime(b, n)) continue;
        if (power_integer(b, n - I(1), n) - I(1) != I(0)) return false;
    }
    return true;
}

// カーマイケル数は Korselt の判定法で判別すると O(N√n)
template <Integer I>
bool korselt(I n) {
    // 事前条件: n は合成数
    if (is_prime(n)) return false;
    vector<I> divisors = divisors_set(n);
    for (auto p : divisors) {
        if (!is_prime(p)) continue;
        if (divides_(p * p, n)) return false; // n は square-free(平方数で割り切れない).
        if (!divides_(p - I(1), n - I(1))) return false; // 任意の素因数 p について p - 1 | n - 1
    }
    return true;
}



void print_carmichael_numbers() {
    ll n = 2, cnt = 0, type;
    cout << "Choose type : {1:simple, 2:Korselt}" << endl;
    cin >> type;
    auto start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
    while (1) {
        if (type == 1) {
            if (is_carmichael(n)) {
                cout << n << endl;;
                cnt++;
            }
        }
        else {
            if (korselt(n)) {
                cout << n << endl;
                cnt++;
            }
        }
        if (cnt == 30) {
            auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
            auto dur = end - start;        // 要した時間を計算
            auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
            // 要した時間をミリ秒（1/1000秒）に変換して表示
            cout << msec << " milli sec" << endl;
            break;
        }
        n++;
    }
}

// n が証拠 witness を用いて合成数と断定されるとき false を返しそうでないとき true を返す.
template <Integer I>
bool miller_rabin_test(I n, I witness) {
    // 事前条件: n - 1 = 2^k * q
    I k(0), tmp = n - I(1);
    while (tmp) {
        if (!divides_(I(2), tmp)) break;
        k += I(1);
        tmp >>= 1;
    }
    I q = (n - I(1)) / (I(1) << k);

    I x = power_integer(witness, q, n);
    if (x == I(1) || x == n - I(1)) return true;
    for (I i(1); i < k; i++) {
        // 不変条件: x = witness^{2^i-1 * q}
        x *= x;
        x %= n;
        if (x == n - I(1)) return true; // witness^{2^i * q} = 1 (mod n) が確定
        if (x == I(1)) return false; // 定理A4の対偶より n が合成数であることが確定
    }
    return false; // witness^{2^k * q} != 1 (mod n) 
}

void print_miller_rabin_test() {
    cout << "Input number n:" << endl;
    ll n;
    cin >> n;
    bool flg = true;
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<ll> dist(1, n - 1);
    for (int i = 0; i < 1e6; i++) {
        ll wit = dist(mt);
        if (!miller_rabin_test(n, wit)) {
            cout << wit << endl;
            flg = false;
            break;
        }
    }
    if (flg) cout << "probably prime." << endl;
    else cout << "not prime." << endl;
}

int main(){
     print_fermat_test();
    // print_carmichael_numbers();
    // print_miller_rabin_test();
    return 0;
}