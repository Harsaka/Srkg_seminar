#include <bits/stdc++.h>
using namespace std;

/*
    長さ9以下の加法連鎖 / 100以下の任意の数の加法連鎖を出力するプログラムです.
    実行すると入力を求められます. '1'または'2'を入力してください.

    1を選択すると長さ9以下の加法連鎖をなす数字が出力されます.
    i 行目には長さ i で加法連鎖が可能となる数が並びます.
    
    2を選択するとさらに入力を求められます.
    100以下の正の整数 N を入力すると, N の加法連鎖の元となる数列が出力されます.
*/

void solve(int mode){
    vector<vector<int>> chain(10); // chain[i] : 長さ i で初めて加法連鎖が可能となる数の集合
    chain[0].push_back(1);
    vector<vector<int>> ancestor(515); // ancestor : chain[i + 1] を作るときに使える加法の元
    ancestor[1].push_back(1);
    vector<int> used(515); // 探索中に発見した数字のフラグ. 加法連鎖の長さもこれに格納する.
    used[1] = 1;
    for(int i = 0; i < 9; i++){
        for(auto cur : chain[i]){
            for(auto a1 : ancestor[cur]){
                for(auto a2 : ancestor[cur]){
                    // 長さ i + 1 で初めて発見される数字 next が満たすべき条件は以下の2つ.
                    // 1:長さ i の各元から根(1)まで辿ることで構成される数列(ancestor[cur])の要素の和で表現される ⇔ next == a1 + a2
                    // 2:長さ i 以下の探索で未発見である ⇔ used[next] == 0
                    int next = a1 + a2;
                    if(!used[next]){
                        used[next] = i + 1; // 発見済のフラグをつける.
                        chain[i + 1].push_back(next); // next は長さ i + 1 の加法連鎖をなす.
                        for(auto x : ancestor[cur]){
                            ancestor[next].push_back(x);
                        }
                        ancestor[next].push_back(next);
                    }
                }
            }
        }
    }
    if(mode == 1){
        for(int i = 0; i <= 9; i++){
            for(auto c : chain[i]){
                cout << c << " ";
            }
            cout << endl;
        }
    }
    else if(mode == 2){
        cout << "Input N" << endl;
        int n;
        cin >> n;
        for(auto x : ancestor[n]){
            cout << x << " ";
        }
        cout << endl << "The minimum length is ";
        int len = ancestor[n].size();
        cout << len << endl;
    }
}

int main(){
    cout << "1 : Print Chain List, 2 : Print Chain of N" << endl;
    int mode;
    cin >> mode;
    solve(mode);
    return 0;
}