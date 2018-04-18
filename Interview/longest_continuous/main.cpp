#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string a, b;
    getline(cin, a);
    getline(cin, b);
    const int h = a.size();
    const int w = b.size();

    vector<vector<int>> matrix(h+1, vector<int>(w+1, 0));

    int max_length = 0;
    for (int i=1; i<h+1; ++i) {
        for (int j=1; j<w+1; ++j) {
            if (a[i - 1] == b[j - 1]) {
                matrix[i][j] = matrix[i-1][j-1] + 1;
                max_length = max_length>matrix[i][j] ? max_length : matrix[i][j];
            }
        }
    }
    cout << max_length << endl;
    return 0;
}
