#include <bits/stdc++.h>
using namespace std;

#define RandomAccessIterator typename
#define Integer typename

template <RandomAccessIterator I , Integer N>
void mark_sieve(I first, I last, N factor) {
    // assert(first != last)
    *first = false;
    while (last - first > factor) {
        first = first + factor;
        *first = false;
    }
}

template <RandomAccessIterator I , Integer N>
void sift0(I first, N n) {
    fill(first, first + n, true);
    N i = 0;
    N index_square = 3;
    while (index_square < n) {
        // 不変条件: index_square = 2i^2 + 6i + 3
        if (first[i]) {
            // iterator i の値 : 2 * i + 3
            mark_sieve(first + index_square, first + n, 2 * i + 3);
        }
        i++;
        index_square = 2 * i * (i + 3) + 3;
    }
}

template <RandomAccessIterator I , Integer N>
void sift1(I first, N n) {
    I last = first + n;
    fill(first, last, true);
    N i = 0;
    N index_square = 3;
    N factor = 3;
    while (index_square < n) {
        // 不変条件: index_square = 2i^2 + 6i + 3
        if (first[i]) {
            // iterator i の値 : 2 * i + 3
            mark_sieve(first + index_square, last, factor);
        }
        i++;
        factor = 2 * i + 3;
        index_square = 2 * i * (i + 3) + 3;
    }
}

template <RandomAccessIterator I , Integer N>
void sift(I first, N n) {
    I last = first + n;
    fill(first, last, true);
    N i = 0;
    N index_square = 3;
    N factor = 3;
    while (index_square < n) {
        // 不変条件: index_square = 2i^2 + 6i + 3
        if (first[i]) {
            // iterator i の値 : 2 * i + 3
            mark_sieve(first + index_square, last, factor);
        }
        i++;
        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}

void time_measure(){
    int mode;
    cin >> mode;
    /*
    select mode...
    1 : vector<bool> a(N);
    2 : vector<uint8_t> b(N);
    3 : vector<uint16_t> c(N);
    4 : vector<uint32_t> d(N);
    5 : vector<uint64_t> e(N);
    */
    const int N = 1e7;
    vector<bool> a(N);
    vector<uint8_t> b(N);
    vector<uint16_t> c(N);
    vector<uint32_t> d(N);
    vector<uint64_t> e(N);
    clock_t start = clock();    // スタート時間
    if (mode == 1) {
        sift(a.begin(), N);
    }
    else if (mode == 2) {
        sift(b.begin(), N);
    }
    else if (mode == 3) {
        sift(c.begin(), N);
    }
    else if (mode == 4) {
        sift(d.begin(), N);
    }
    else {
        sift(e.begin(), N);
    }
    clock_t end = clock();     // 終了時間
    std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";
}



int main(){
    time_measure();
    return 0;
}
