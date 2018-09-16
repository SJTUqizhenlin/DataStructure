#include <iostream>
#include <string>
#include <stack>

using namespace std;

// THIS IS THE SOLUTION
class Solution {
public:
	int longestValidParentheses(string s) {
		int l = s.length();
		int *pre = new int[l + 1];
		for (int i = 0; i <= l; i++) pre[i] = i;
		stack<int> *stk = new stack<int>();
		for (int i = 0; i < l; i++) {
			if (s[i] == '(')
				stk->push(i + 1);
			else {
				if (!stk->empty()) {
					pre[i + 1] = pre[stk->top() - 1];
					stk->pop();
				}
			}
		}
		int MAXres = 0;
		for (int i = 0; i <= l; i++)
			MAXres = (MAXres < i - pre[i] ? i - pre[i] : MAXres);
		return MAXres;
	}
};

// THE END

int main() {
	string ins;
	cin >> ins;
	Solution *sol = new Solution();
	cout << sol->longestValidParentheses(ins) << endl;
	return 0;
}