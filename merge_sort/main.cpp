#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void merge_array(vector<int>& input, int left, int mid, int right)
{
    if (input.empty())
        return;

    vector<int> tmp(right - left + 1, 0);
    int i = left;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= right) {
        if (input[i] <= input[j])
            tmp[k++] = input[i++];
        else
            tmp[k++] = input[j++];
    }
    while (i <= mid) tmp[k++] = input[i++];
    while (j <= right) tmp[k++] = input[j++];
    for (int i=0; i<k; ++i)
        input[left+i] = tmp[i];
}

void merge_sort(vector<int>& input, int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(input, left, mid);
        merge_sort(input, mid+1, right);
        merge_array(input, left, mid, right);
    }
}

int main(int argc, char *argv[])
{
    vector<int> a = {12,31,51,526,1,6,1,231,31,5,1,65,151,94,2,13,21,56,16,16,1};
    merge_sort(a, 0, a.size()-1);
    return 0;
}
