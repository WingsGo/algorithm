#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n) {
        vector<int> heights(n, 0);
        for (int i=0; i<n; ++i) {
            int tmp;
            cin >> tmp;
            heights[i] = tmp;
        }

        int max_area = 0;
        for (int i=0; i<n; ++i) {
            int min_height = heights[i];
            int current_area = min_height;
            for (int j=i; j<n; ++j) {
                min_height = min_height<heights[j] ? min_height : heights[j];
                current_area = min_height * (j - i + 1);
                max_area = max_area>current_area ? max_area : current_area;
            }
        }
        cout << max_area << endl;
    }
    return 0;
}
