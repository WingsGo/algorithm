#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void swap(int &lhs, int &rhs)
    {
        int tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }

    int partion(vector<int> &input, int left, int right)
    {
        while (left < right)
        {
            int base = input[left];
            while (left < right && input[right] >= base)
                right--;
            if (left < right)
                swap(input[left++], input[right]);
            while (left < right && input[left] < base)
                left++;
            if (left < right)
                swap(input[left], input[right--]);
        }
        return left;
    }

    void qSort(vector<int> &input, int left, int right)
    {
        if (left < right)
        {
            int base = partion(input, left, right);
            qSort(input, left, base - 1);
            qSort(input, base + 1, right);
        }
    }
};

int main(int argc, char *argv[])
{
    vector<int> a = {0};
    vector<int> b = {9,8,7,6,5,4,3,2,1};
    vector<int> c = {123,1,51,6,16,1,3,13,156,4,84,1521,46,4,31,3,156,4,48,18,1,5,162,1,51,1,1,65,985,8,48,94,5,648,48,4,54,1,321,56,48,4,94};
    Solution s;
    s.qSort(a, 0, a.size()-1);
    s.qSort(b, 0, b.size()-1);
    s.qSort(c, 0, c.size()-1);

    for (size_t i=0; i<a.size(); i++)
        cout << a[i] << " ";
    cout << endl;

    for (size_t i=0; i<b.size(); i++)
        cout << b[i] << " ";
    cout << endl;

    for (size_t i=0; i<c.size(); i++)
        cout << c[i] << " ";
    cout << endl;
    return 0;
}
