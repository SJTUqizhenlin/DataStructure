#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

// SOLUTION
class Solution {
public:
	class trie {
	public:
		int val;
		trie *son[26], *p;
		bool isWord;
		trie() {
			val = -1;
			for (int i = 0; i < 26; i++) son[i] = nullptr;
			p = nullptr;
			isWord = false;
		}
	};
	trie *Root;
	trie *cur;
	vector<vector<char> > bd;
	vector<string> wd;
	vector<string> ret;
	unordered_set<string> uoset;
	vector<vector<int> > visited;
	int N; int M;
	int w_size;
	Solution() {
		Root = new trie();
		cur = Root;
		this->ret.clear();
		uoset.clear();
	}
	void trie_insert(string s) {
		cur = Root;
		int slen = s.length();
		for (int i = 0; i < slen; i++) {
			if (cur->son[s[i] - 'a'] == nullptr) {
				cur->son[s[i] - 'a'] = new trie();
				cur->son[s[i] - 'a']->val = s[i] - 'a';
				cur->son[s[i] - 'a']->p = cur;
			}
			cur = cur->son[s[i] - 'a'];
		}
		cur->isWord = true;
		cur = Root;
	}
	string makestr(trie* t) {
		stack<char> stk;
		while (t != Root) {
			stk.push(char('a' + t->val));
			t = t->p;
		}
		string res = "";
		while (!stk.empty()) {
			res.append(1, stk.top());
			stk.pop();
		}
		return res;
	}
	void search(int x, int y) {
		visited[x][y] = 1;
		if (cur->son[bd[x][y] - 'a'] == nullptr) {
			visited[x][y] = 0;
			return;
		}
		cur = cur->son[bd[x][y] - 'a'];
		if (cur->isWord) {
			string tmp = makestr(cur);
			if (uoset.find(tmp) == uoset.end()) {
				uoset.insert(tmp);
				ret.push_back(tmp);
			}
		}
		if (x - 1 >= 0) if (visited[x - 1][y] == 0) search(x - 1, y);
		if (x + 1 < N) if (visited[x + 1][y] == 0) search(x + 1, y);
		if (y - 1 >= 0) if (visited[x][y - 1] == 0) search(x, y - 1);
		if (y + 1 < M) if (visited[x][y + 1] == 0) search(x, y + 1);
		cur = cur->p;
		visited[x][y] = 0;
		return;
	}
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		this->bd = board;
		this->wd = words;
		N = bd.size();
		if (N == 0) return ret;
		M = bd[0].size();
		w_size = words.size();
		for (int i = 0; i < N; i++) {
			vector<int> v(M, 0);
			visited.push_back(v);
		}
		for (int i = 0; i < w_size; i++)
			trie_insert(wd[i]);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++)
				search(i, j);
		}
		sort(ret.begin(), ret.end());
		return this->ret;
	}
};
// THE END

int main() {
	int N, M, K;
	cin >> N >> M >> K;
	cin.get();
	string tempstr;
	vector<string> str_v;
	vector<vector<char> > board;
	for (int i = 0; i < K; i++) {
		getline(cin, tempstr);
		str_v.push_back(tempstr);
	}
	for (int i = 0; i < N; i++) {
		getline(cin, tempstr);
		vector<char> v;
		for (int j = 0; j < M; j++)
			v.push_back(tempstr[j]);
		board.push_back(v);
	}
	Solution *sol = new Solution();
	vector<string> res = sol->findWords(board, str_v);
	int res_size = res.size();
	for (int i = 0; i < res_size; i++)
		cout << res[i] << " ";
	cout << endl;
	return 0;
}