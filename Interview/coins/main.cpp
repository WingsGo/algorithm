#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n) {
        int coins[6] = {1, 5, 10, 20, 50, 100};
        vector<vector<long long>> matrix(6, vector<long long>(n+1, 0));
        for (int i=0; i<=n; ++i)
            matrix[0][i] = 1;

        for (int i=1; i<6; ++i) {
            for (int j=0; j<=n; ++j) {
                int m = j / coins[i];
                for (int k=0; k<=m; ++k)
                    matrix[i][j] += matrix[i-1][j - k*coins[i]];
            }
        }

        cout << matrix[5][n] << endl;
    }
    return 0;
}
