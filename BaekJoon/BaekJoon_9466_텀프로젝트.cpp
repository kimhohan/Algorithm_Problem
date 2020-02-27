#include <iostream>

using namespace std;
int N;
int map[100001];
int visit[100001];
int cycle[100001];
int flag = 0;
int sum;
int c1;

int dfs(int n, int g) {
	// 싸이클이 생기는 구간을 모두 -1로 표시하고 후에 1로 바꿔줌으로써 싸이클인 곳을 체크해준다.
	if (visit[g] == 0 || (visit[g] == -1 && cycle[g] == 1)) {
		visit[g] = 1;
		if (n == g) return 1;

		if (!dfs(n, map[g])) {
			visit[g] = -1;
			return 0;
		}
		else return 1;
	}
	cycle[g] = 1;
	return 0;
}

int main() {
	int t;

	cin >> t;

	for (int T = 1; T <= t; T++) {
		cin >> N;

		// 입력
		for (int i = 1; i <= N; i++) {
			cin >> map[i];
		}

		for (int i = 1; i <= N; i++) {
			dfs(i, map[i]);
		}

		int ans = 0;
		for (int i = 1; i <= N; i++) {
			if (visit[i] <= 0) ans++;
			map[i] = 0;
			visit[i] = 0;
		}
		cout << ans << endl;


		sum = 0;
	}

	return 0;
}