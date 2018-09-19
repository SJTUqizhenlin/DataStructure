#include <iostream>
#include <vector>

using namespace std;

//THIS IS THE SOLUTION
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int vsize = nums.size();
		return maxProduct_1(nums, 0, vsize);
	}
	int maxProduct_1(vector<int> &v, int beg, int end) {
		if (end - beg == 1) return v[beg];
		int mid = (beg + end) / 2;
		int res_left = maxProduct_1(v, beg, mid);
		int res_right = maxProduct_1(v, mid, end);
		int max_left, min_left, max_right, min_right;
		max_left = min_left = v[mid - 1];
		max_right = min_right = v[mid];
		int product = 1;
		for (int i = mid - 1; i >= beg; i--) {
			product *= v[i];
			if (product > max_left) max_left = product;
			if (product < min_left) min_left = product;
		}
		product = 1;
		for (int i = mid; i < end; i++) {
			product *= v[i];
			if (product > max_right) max_right = product;
			if (product < min_right) min_right = product;
		}
		int res1 = max_left * max_right;
		if (min_left * min_right > res1) res1 = min_left * min_right;
		if (max_left * min_right > res1) res1 = max_left * min_right;
		if (min_left * max_right > res1) res1 = min_left * max_right;
		int res2 = (res_left > res_right ? res_left : res_right);
		return (res1 > res2 ? res1 : res2);
	}
};
//THE END

int main() {
	vector<int> v;
	int N; cin >> N;
	int tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}
	Solution *sol = new Solution();
	cout << sol->maxProduct(v) << endl;
	return 0;
}