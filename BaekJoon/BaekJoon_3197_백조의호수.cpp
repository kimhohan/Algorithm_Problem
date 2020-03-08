#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point
{
	int y, x;
	Point(int y, int x) {
		this->y = y;
		this->x = x;
	}
};

vector<Point> baek;
queue<Point> melt;
queue<Point> ice;
int day;
int ans;
int flag;
int f;
int Y, X;
int map[1500][1500];
int visit[1500][1500];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

void init() {
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			visit[i][k] = 0;
		}
	}
}

void melt_bfs() {
	queue<Point> q;

	while (!melt.empty()) {
		int cx = melt.front().x;
		int cy = melt.front().y;

		visit[cy][cx] = 1;

		melt.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || ny < 0 || nx >= X || ny >= Y || visit[ny][nx] == 1)
				continue; 


			// 종료
			if (nx == baek[1].x && ny == baek[1].y) {
				flag = 1;
				return;
			}

			// 얼음을 만난경우
			if (map[ny][nx] == -1) {
				q.push(Point(ny, nx));
				visit[ny][nx] = 1;
			}
			else {
				melt.push(Point(ny, nx));
				visit[ny][nx] = 1;

			}
		}
	}

	// 옯기기
	while (!q.empty()) {
		melt.push(q.front());
		q.pop();
	}
}

void bfs() {
	queue<Point> q;

	while (!ice.empty()){
		int cx = ice.front().x;
		int cy = ice.front().y;

		ice.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];


			if (nx < 0 || ny < 0 || nx >= X || ny >= Y )
				continue;

			if (map[ny][nx] == 0) continue;
			
			// 얼음을 만난경우
			map[ny][nx] = 0;
			q.push(Point(ny, nx));
		}
	}

	// 옯기기
	while (!q.empty()) {
		ice.push(q.front());
		q.pop();
	}
}

int main(){

	cin >> Y >> X;
	// 입력
	for (int i = 0; i < Y; i++) {
		for (int k = 0; k < X; k++) {
			char ch;
			cin >> ch;
			if (ch == '.') {
				map[i][k] = 0;
				ice.push(Point(i, k));
			}
			if (ch == 'X') {
				map[i][k] = -1;
			}
			if (ch == 'L') {
				ice.push(Point(i, k));
				baek.push_back(Point(i, k));
			}
		}
	}

	melt.push(Point(baek[0].y, baek[0].x));

	while (1) {

		// 얼음 녹이기
		bfs();
	
		// 하루 증가
		day++;

		// 둘이 만나는지 확인
		melt_bfs();
		if (flag == 1) {
			ans = day;
			break;
		}
	}

	cout << ans << endl;

	return 0;
}