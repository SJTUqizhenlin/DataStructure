#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

//THIS IS THE SOLUTION
class Solution {
public:
	unordered_set<int> uoset_col;
	unordered_set<int> uoset_dgn1;
	unordered_set<int> uoset_dgn2;
	vector<int> v;
	int res;
	int totalNQueens(int n) {
		if (n == 1) return 1;
		if (n <= 3) return 0;
		uoset_col.clear();
		uoset_dgn1.clear();
		uoset_dgn2.clear();
		v.clear();
		res = 0;
		Try_At(0, n);
		return res;
	}
	bool isValid(int x, int row) {
		if (uoset_col.find(x) != uoset_col.end())
			return false;
		if (uoset_dgn1.find(x - row) != uoset_dgn1.end())
			return false;
		if (uoset_dgn2.find(x + row) != uoset_dgn2.end())
			return false;
		return true;
	}
	void Try_At(int row, int n) {
		if (row == n) {
			res += 1;
			return;
		}
		else {
			for (int i = 0; i < n; i++) {
				if (isValid(i, row)) {
					v.push_back(i);
					uoset_col.insert(i);
					uoset_dgn1.insert(i - row);
					uoset_dgn2.insert(i + row);
					Try_At(row + 1, n);
					v.pop_back();
					uoset_col.erase(i);
					uoset_dgn1.erase(i - row);
					uoset_dgn2.erase(i + row);
				}
			}
		}
		return;
	}
};
//THE END

int main() {
	int N;
	cin >> N;
	Solution *sol = new Solution();
	cout << sol->totalNQueens(N) << endl;
	return 0;
}