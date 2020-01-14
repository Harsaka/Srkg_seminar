#include <iostream>
#include <cassert>
#include <map>

using namespace std;

bool carmichael[100000000];
bool prime[100000000];

#ifdef debug
map<long long, int> factorize(long long n) {
    map<long long, int> ret;
    
    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ++ret[i];
            n /= i;
        }
    }
    
    if (n != 1)
        ret[n] = 1;
    
    return ret;
}

void korseltCriterion(int x) {
    map<long long, int> fact = factorize(x);

    for (const auto &pr : fact) {
        assert(pr.second == 1);
        assert((x-1) % (pr.first-1) == 0);
    }
}
#endif

int main(int argc, char **argv) {
    fill(carmichael, carmichael+100000000, true);
    fill(prime, prime+100000000, true);

    carmichael[0] = carmichael[1] = false;
    prime[0] = prime[1] = false;

    for (int i = 2; i < 100000000; i++) {
        if (!prime[i])
            continue;

        carmichael[i] = false;   // i is a prime number

        long long sq = (long long)i * i;
        for (int j = 2 * i; j < 100000000; j += i) {
            prime[j] = false;
            if (j % sq == 0)
                carmichael[j] = false;  // j is not square-free
            if ((j - 1) % (i - 1))
                carmichael[j] = false;  // (i-1) | (j-1) does not hold
        }
    }
    
    for (int i = 0; i < 100000000; i++) {
        if (carmichael[i]) {
            cout << i << endl;
#ifdef debug
            korseltCriterion(i);
#endif
        }
    }

    return 0;
}