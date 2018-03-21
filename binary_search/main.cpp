#include <iostream>
#include <vector>

using namespace std;

// 非递归版本
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size();
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target)
                right = mid;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                return mid;
        }
        return left;
    }
};


// 递归版本
class Solution {
public:
    int searchInsert(vector<int>& nums, int target, int left, int right) {
        int mid = left + (right - left) / 2;
        if (left >= right)
            return left;
        if (target == nums[mid])
            return mid;
        else if (target < nums[mid])
            searchInsert(nums, target, left, mid);
        else
            searchInsert(nums, target, mid+1, right);
    }
};

int main(int argc, char *argv[])
{
    vector<int> a = {1, 3, 5, 6};
    Solution s;
    s.searchInsert(a, 2, 0, 3);
    cout << "Hello World!" << endl;
    return 0;
}
