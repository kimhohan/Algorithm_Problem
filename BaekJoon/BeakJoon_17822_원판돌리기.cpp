#include <iostream>
#include <deque>

using namespace std;

int N; // 원판 개수
int M; // 적힌 수
int T; // 몇번

int number[51] = { 0, };
int dir[51] = { 0, };
int rotate_[51] = { 0, };

deque<int> cir[51];
int map[51][51] = { 0, };
int copy_map[51][51] = { 0, };

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void dfs(int y, int x, int num) {

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (ny < 0 || ny >= N) continue;

		if (nx < 0) nx = M - 1;
		if (nx >= M) nx = 0;
		
		if (map[ny][nx] == num) {
			map[y][x] = 0;
            cir[y][x] = 0;
			dfs(ny, nx, num);
			map[ny][nx] = 0;
            cir[ny][nx] = 0;
		}
	}
    return;
}

void Rota(int num, int ro, int who) {
	// 반시계
	if (num == 1) {
		ro %= M;
		int flag = who;
		while (1) {
			if (who > N) break;
			for (int k = 0; k < ro; k++) {
				int val = cir[who - 1].front();
				cir[who - 1].pop_front();
				cir[who - 1].push_back(val);
			}
			who += flag;
		}
	}
	// 시계
	if (num == 0) {
		ro %= M;
		int flag = who;
		while (1) {
			if (who > N) break;
			for (int k = 0; k < ro; k++) {
				int val = cir[who - 1].back();
				cir[who - 1].pop_back();
				cir[who - 1].push_front(val);
			}
			who += flag;
		}
	}
}

int check() {
	for (int k = 0; k < N; k++) {
		for (int r = 0; r < M; r++) {
			if (copy_map[k][r] != map[k][r]) return 1;
		}
	}
	return 0;
}

int main() {

	cin >> N >> M >> T;

	// 입력 받기 맵초기화
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < M; k++) {
			int num;
			cin >> num;
			cir[i].push_back(num);
			map[i][k] = num;
		}
	}

	// 몇번째 , 방향 ,횟수 입력
	for (int i = 0; i < T; i++) {
		int nn;
		cin >> nn;
		number[i] = nn;
		cin >> dir[i];
		cin >> rotate_[i];
	}

	// 시뮬 시작
	for (int i = 0; i < T; i++) {
		int n = number[i];
		int d = dir[i];
		int r = rotate_[i];

		//// 이동 시키기
		// 회전
		// 시계방향
		if (d == 0) {
			Rota(d, r, n);
		}
		// 반시계
		if (d == 1) {
			Rota(d, r, n);
		}

		// map 에 적용
		for (int k = 0; k < N; k++) {
			for (int r = 0; r < M; r++) {
				map[k][r] = cir[k][r];
			}
		}

		// copy
		for (int k = 0; k < N; k++) {
			for (int r = 0; r < M; r++) {
				copy_map[k][r] = map[k][r];
			}
		}

		// 지우기
		for (int k = 0; k < N; k++) {
			for (int r = 0; r < M; r++) {
				if (map[k][r] == 0) continue;
				dfs(k, r, map[k][r]);
			}
		}

		// 변홧화가 업는지 확인
		if (check() == 0) {
			int s = 0;
			int count = 0;
			for (int k = 0; k < N; k++) {
				for (int r = 0; r < M; r++) {
					if (map[k][r] != 0) {
						s += map[k][r];
						count++;
					}
				}
			}
			double aver = (double)s / (double)count;
			for (int k = 0; k < N; k++) {
				for (int r = 0; r < M; r++) {
					if (map[k][r] == 0) continue;
					if (map[k][r] > aver)
						map[k][r] = map[k][r] - 1;
					else if (map[k][r] < aver)
						map[k][r] = map[k][r] + 1;
				}
			}

			for (int k = 0; k < N; k++) {
				for (int r = 0; r < M; r++) {
					cir[k][r] = map[k][r];
				}
			}
		}
		// 변화가 없으면 그다음
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < M; k++) {
			ans += map[i][k];
		}
	}

	cout << ans << endl;
}