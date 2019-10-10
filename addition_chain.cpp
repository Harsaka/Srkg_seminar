#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> chain(10); // chain[i] : 長さ i で初めて加法連鎖が可能となる数の集合
    chain[0].push_back(1);
    vector<vector<int>> ancestor(515); // ancestor : chain[i + 1] を作るときに使える加法の元
    ancestor[1].push_back(1);
    vector<int> used(515);
    for(int i = 0; i < 9; i++){
        for(auto cur : chain[i]){
            for(auto a1 : ancestor[cur]){
                for(auto a2 : ancestor[cur]){
                    int next = a1 + a2;
                    if(next > cur && !used[next]){
                        used[next] = 1;
                        chain[i + 1].push_back(next);
                        ancestor[next].push_back(next);
                        for(auto x : ancestor[cur]){
                            ancestor[next].push_back(x);
                        }
                    }
                }
            }
        }
    }
    cout << "1 : Print Chain List, 2 : Print Chain of N" << endl;
    int q;
    cin >> q;
    if(q == 1){
        for(int i = 0; i <= 9; i++){
            sort(chain[i].begin(), chain[i].end());
            for(auto c : chain[i]){
                cout << c << " ";
            }
            cout << endl;
        }
    }
    else if(q == 2){
        cout << "Input N" << endl;
        int n;
        cin >> n;
        sort(ancestor[n].begin(), ancestor[n].end());
        for(auto x : ancestor[n]){
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}