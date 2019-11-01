#include <bits/stdc++.h>
using namespace std;

//functions computing n * a

//O(n)
int multiply0(int n, int a){
    if (n == 1) return a;
    return multiply0(n - 1, a) + a;
}

//非再帰, O(n)
int non_rec_multiply0(int n, int a){
    int result = a;
    for (int i = 0; i < n - 1; i++){
        result += a;
    }
    return result;
}

bool odd(int n){ 
    return n & 0x1;
}
int half(int n){
    return n >> 1;
}

// O(log(n))
int multiply1(int n, int a){
    if (n == 1) return a;
    int result = multiply1(half(n), a + a);
    if (odd(n)) result = result + a;
    return result;
}

// 非再帰 O(log(n))
int non_rec_multiply1(int n, int a){
    int res = 0;
    while (n){
        if (odd(n)) res = res + a; // v(n)
        n = half(n);
        a = a + a; //floor(log(n))
    }
    return res;
}

// a ^ n
int pow(int n, int a){
  	int res = 1;
  	while (n > 0){
    	if(odd(n)) res = res * a;
        n = half(n);
    	a = a * a;
  	}
  	return res;
}

// 15 * a の加法連鎖
int multiply_by_15(int a){
    int b = (a + a) + a;
    int c = b + b;
    return (c + c) + b;
}

// return r + n * a
int multi_acc0(int r, int n, int a){
    if (n == 1) return r + a;
    if (odd(n)){
        return multi_acc0(r + a, half(n), a + a);
    }else{
        return multi_acc0(r, half(n), a + a);
    }
}

// tail-recursive
int multi_acc1(int r, int n, int a){
    if (n == 1) return r + a;
    
    if (odd(n)) r = r + a;
    return multi_acc1(r, half(n), a + a);
}

// 初めに偶奇判定することで計算回数を半減させられる
int multi_acc2(int r, int n, int a){
    if (odd(n)){
        r = r + a;
        if (n == 1) return r;
    }
    return multi_acc2(r, half(n), a + a);
}

// 正確な tail-recursive
// 再帰呼び出しの引数の形が一緒
int multi_acc3(int r, int n, int a){
    if (odd(n)){
        r = r + a;
        if(n ==1)return r;
    }
    
    n = half(n);
    a = a + a;
    
    return multi_acc3(r, n, a);
}

// 非再帰化
int multi_acc4(int r, int n, int a){
    while (true){
        if (odd(n)){
            r = r + a;
            if(n == 1) return r;
        }
        n = half(n);
        a = a + a;
    }
}

int multiply2(int n, int a){
    if (n == 1) return a;
    return multi_acc4(a, n - 1, a);
}

int multiply3(int n, int a){
    while (!odd(n)){
        a = a + a;
        n = half(n);
    }
    return multiply2(n, a);
}

int multiply4(int n, int a){
    while (!odd(n)){
        a = a + a;
        n = half(n);
    }
    if (n == 1) return a;
    return multi_acc4(a, half(n - 1), a + a);
}

int main(){
    int r, n, a;
    cin >> r >> n >> a;
    int res = non_rec_multiply1(n, a);
    cout << res << endl;
    return 0;
}
