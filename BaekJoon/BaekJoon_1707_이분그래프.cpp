#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> v[20001];
int N, K;
int visit[20001];
string ch = "YES";

int dfs(int n, int cnt) {

	visit[n] = cnt;

	for (int i = 0; i < v[n].size(); i++) {
		if (visit[v[n][i]] == -1) {
			if (dfs(v[n][i], (cnt + 1) % 2 ) == 1) {
				return 1;
			}
		}
		if (visit[v[n][i]] == cnt) {
			ch = "NO";
			return 1;
		}
	}
	return 0;
}

int main() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		// 초기화
		for (int i = 0; i < 20001; i++) {
			v[i].clear();
			visit[i] = -1;
		}
		// 입력
		ch = "YES";
		cin >> N >> K;
		for (int i = 0; i < K; i++) {
			int num, num1;
			scanf("%d", &num);
			scanf("%d", &num1);
			v[num].push_back(num1);
			v[num1].push_back(num);
		}

		// 이분 그래프
		int flag = 0;
		for (int i = 1; i <= N; i++) {
			if (visit[i] != -1) continue;
			if (dfs(i, 1) == 1) {
				flag = 1;
				break;
			}
		}

		if (flag == 0) printf("YES\n");
		else printf("NO\n");

	}
	return 0;
}