#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

//THIS IS THE SOLUTION
class Solution {
public:
	int dx[4];
	int dy[4];
	int M; int N;
	void init_dxdy() {
		dx[0] = -1; dx[1] = 1; dx[2] = 0; dx[3] = 0;
		dy[0] = 0; dy[1] = 0; dy[2] = -1; dy[3] = 1;
	}
	int numIslands(vector<vector<char>>& grid) {
		M = grid.size();
		if (M == 0) return 0;
		N = grid[0].size();
		if (N == 0) return 0;
		int res = 0;
		init_dxdy();
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (grid[i][j] == '1') {
					res += 1;
					bfs(i, j, grid);
				}
			}
		}
		return res;
	}
	inline int getX(int n) { return (n / N); }
	inline int getY(int n) { return (n % N); }
	inline int getN(int x, int y) { return (x * N + y); }
	void bfs(int row, int col, vector<vector<char>>& grid) {
		queue<int> q;
		grid[row][col] = '0';
		q.push(getN(row, col));
		int curx, cury, nxtx, nxty;
		int d;
		while (!q.empty()) {
			curx = getX(q.front());
			cury = getY(q.front());
			for (d = 0; d < 4; d++) {
				nxtx = curx + dx[d];
				nxty = cury + dy[d];
				if ((nxtx >= 0 && nxty >= 0) && (nxtx < M && nxty < N)) {
					if (grid[nxtx][nxty] == '1') {
						grid[nxtx][nxty] = '0';
						q.push(getN(nxtx, nxty));
					}
				}
			}
			q.pop();
		}
		return;
	}
};
//THE END

int main() {
	int N, M;
	cin >> M >> N;
	vector<vector<char> >v(M);
	for (int i = 0; i < M; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < N; j++)
			v[i].push_back(s[j]);
	}
	Solution *sol = new Solution();
	cout << sol->numIslands(v) << endl;
	return 0;
}