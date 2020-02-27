#include <iostream>

using namespace std;
int N;
int map[100001];
int visit[100001];
int flag = 0;
int sum;
int c1;

void dfs(int n, int g) {
	if (g == map[n]) {
		visit[n] = 1;
		flag = 1;
		sum += c1;
		return;
	}
	if (visit[n] == 1) return;
	if (visit[n] != 1 && n == map[n]) {
		visit[n] = 1;
		sum += 1;
		flag = 1;
		return;
	}
	visit[n] = 1;
	c1++;
	dfs(map[n], g);
	if (flag == 0){
		if (g != n)
			visit[n] = 0;
	}
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
			if (visit[i] == 1) continue;
			flag = 0;
			c1 = 1;
			dfs(i, i);
		}

		int ans = 0;
		for (int i = 1; i <= N; i++) {
			visit[i] = 0;
			map[i] = 0;
		}

		cout << N - sum << endl;
		sum = 0;
	}

	return 0;
}