#include <iostream>
#include <vector>

using namespace std;

// THIS IS THE SOLUTION
class Solution {
public:
	int maxProfit(int k, vector<int>& prices) {
		int n = prices.size();
		if (n <= 1) return 0;
		if (k * 2 >= n) {
			int res = 0;
			for (int i = 1; i < n; i++)
				if (prices[i] > prices[i - 1]) 
					res += (prices[i] - prices[i - 1]);
			return res;
		}
		int **dp = new int*[k + 1];
		for (int i = 0; i <= k; i++) {
			dp[i] = new int[n];
			for (int j = 0; j < n; j++)
				dp[i][j] = 0;
		}
		int tmpmax = 0;
		for (int i = 1; i <= k; i++) {
			tmpmax = -prices[0];
			for (int j = 1; j < n; j++) {
				dp[i][j] = (dp[i][j - 1] > tmpmax + prices[j] ? dp[i][j - 1] : tmpmax + prices[j]);
				tmpmax = (tmpmax > dp[i - 1][j - 1] - prices[j] ? tmpmax : dp[i - 1][j - 1] - prices[j]);
			}
		}
		int res = dp[k][n - 1];
		for (int i = 0; i <= k; i++) delete[] dp[i];
		delete[] dp;
		return res;
	}
};
// THE END

int main() {
	int N, K;
	cin >> N >> K;
	vector<int> v(N);
	for (int i = 0; i < N; i++) cin >> v[i];
	cout << (new Solution)->maxProfit(K, v);
	return 0;
}