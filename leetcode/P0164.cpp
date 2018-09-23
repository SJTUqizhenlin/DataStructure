#include <iostream>
#include <vector>
#include <stdint.h>
#include <algorithm>

using namespace std;

//THIS IS THE SOLUTION
class bucket {
public:
	int floor, ceiling;
	vector<int> vals;
	bucket()
		:floor(0), ceiling(0) {
		vals.clear();
	}
	void Insert(int x) {
		vals.push_back(x);
		return;
	}
	void selfSort() {
		sort(vals.begin(), vals.end());
		return;
	}
	int getSize() {
		return vals.size();
	}
};

class Solution {
public:
	vector<int>& bucketSort(vector<int>& nums) {
		int N = nums.size();
		vector<int> *res = new vector<int>();
		res->clear();
		int maxval = INT32_MIN, minval = INT32_MAX;
		for (int i = 0; i < N; i++) {
			if (nums[i] > maxval) maxval = nums[i];
			if (nums[i] < minval) minval = nums[i];
		}
		bucket *bcarr = new bucket[N];
		int bcgap = ((maxval - minval) / (N - 1) + 1);
		for (int i = 0; i < N; i++) {
			bcarr[i].floor = minval + (bcgap * i);
			bcarr[i].ceiling = minval + (bcgap * (i + 1));
		}
		for (int i = 0; i < N; i++) {
			int bci = (nums[i] - minval) / bcgap;
			bcarr[bci].Insert(nums[i]);
		}
		int curSize = 0;
		for (int i = 0; i < N; i++) {
			bcarr[i].selfSort();
			curSize = bcarr[i].getSize();
			for (int j = 0; j < curSize; j++)
				res->push_back(bcarr[i].vals[j]);
		}
		return *res;
	}
	int maximumGap(vector<int>& nums) {
		int N = nums.size();
		if (N < 2) return 0;
		vector<int> snums = bucketSort(nums);
		int maxGap = 0;
		for (int i = 0; i < N - 1; i++)
			if (snums[i + 1] - snums[i] > maxGap)
				maxGap = snums[i + 1] - snums[i];
		return maxGap;
	}
};
//THE END

int main() {
	int N, tmp;
	cin >> N;
	vector<int> v;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		v.push_back(tmp);
	}
	Solution *sol = new Solution();
	cout << sol->maximumGap(v) << endl;
	return 0;
}