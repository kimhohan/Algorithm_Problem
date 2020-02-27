#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;
int map[100001];
int visit[100001];
int flag = 0;
int sum;
int c1;
vector<int> v;
vector<int> c_v;

void dfs(int n, int g) {
	if (g == map[n]) {
		visit[n] = 1;
		c_v.push_back(n);
		for (int i = 0; i < c_v.size(); i++) {
			v.push_back(c_v[i]);
		}
		flag = 1;
		sum += c1;
		c_v.clear();
		return;
	}
	if (visit[n] == 1) return;
	if (visit[n] != 1 && n == map[n]) {
		visit[n] = 1;
		sum += 1;
		flag = 1;
		v.push_back(n);
		return;
	}
	visit[n] = 1;
	c1++;
	c_v.push_back(n);
	dfs(map[n], g);
	if (flag == 0){
		c_v.clear();
		if (g != n)
			visit[n] = 0;
	}
}

int main() {
	int t;

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

	sort(v.begin(), v.end());

	cout << v.size() << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}

	return 0;
}