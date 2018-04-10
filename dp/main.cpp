#include<iostream>
using namespace std;

#define N 3 // N件宝贝
#define V 5 // C是背包的总capacity

int main()
{
    int value[N + 1]  = {0, 60, 100, 120}; // 钱啊
    int weight[N + 1] = {0, 1,  2,  3};    // 重量
    int f[N + 1][V + 1] = {0}; // f[i][j]表示在背包容量为j的情况下， 前i件宝贝的最大价值

    for (int i=1; i<N+1; i++) {
        for (int j=1; j<V+1; j++) {
            if (j < weight[i])
                f[i][j] = f[i-1][j];
            else {
                int x = f[i-1][j];
                int y = value[i] + f[i-1][j-weight[i]];
                f[i][j] = x>y ? x : y;
            }
        }
    }
    for(int i=1; i<N+1; i++)
    {
        for(int j=1; j<V; j++)
            printf("%4d ", f[i][j]);
        cout << endl;
    }
    return 0;
}
