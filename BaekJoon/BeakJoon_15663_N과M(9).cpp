#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;
int N, M;
int map[8];
int visit[8];
int val[8];

void dfs(int cnt, int g) {
	if (cnt == g) {

		for (int i = 0; i < M; i++) {
			cout << val[i] << " ";
		}
		cout << endl;
		return;
	}
	// 중복을 피하기 위한 배열
	int used[10002] = {0,};

	for (int i = 0; i < v.size(); i++) {
		if (used[v[i]] == 1 || visit[i] == 1)continue;
		visit[i] = 1;
		used[v[i]] = 1;
		val[cnt] = v[i];
		dfs(cnt + 1, g);
		visit[i] = 0;
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}

	// 오름차순 정렬
	sort(v.begin(), v.end());

	dfs(0,M);

	return 0;
}