import java.util.Scanner;

public class Main_19236 {

	static point[][] map = new point[4][4];

	static int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
	static int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

	static point sh;
	
	static int ans = 0;

	static class point {
		int num, dir;

		public point(int num, int dir) {
			this.num = num;
			this.dir = dir;
		}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		// 맵 구성
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				int n = sc.nextInt();
				int dir = sc.nextInt() - 1;

				map[i][k] = new point(n, dir);
			}
		}

		sh = new point(map[0][0].num, map[0][0].dir);
		map[0][0] = new point(0,0);
		
		dfs(0, 0, sh);
		
		System.out.println(ans);
	}

	static void dfs(int y, int x, point sh) {

		if(ans < sh.num) {
			ans = sh.num;
		}
		
		// 물고기 이동
		move(map, y, x);

		for (int i = 0; i < 3; i++) {
			
			int nx = x;
			int ny = y;
			for(int k = 0; k <=i; k++) {
				nx += dx[sh.dir];
				ny += dy[sh.dir];
			}
			
			if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4)
				continue;
			if(map[ny][nx].num == 0)
				continue;
			
			int n = map[ny][nx].num;
			int d = map[ny][nx].dir;
			
			map[ny][nx] = new point(0,0);
			
			point[][] m_c = new point[4][4];
			for(int q = 0; q < 4; q++) {
				for(int w = 0; w< 4; w++) {
					m_c[q][w] = map[q][w];
				}
			}
			
			dfs(ny, nx, new point(sh.num + n, d));
			
			for(int q = 0; q < 4; q++) {
				for(int w = 0; w< 4; w++) {
					map[q][w] = m_c[q][w];
				}
			}
			map[ny][nx] = new point(n,d);
			
		}
	}

	static void move(point[][] m, int sy, int sx) {
		int cnt = 1;
		while (true) {
			end : for (int i = 0; i < 4; i++) {
				for (int k = 0; k < 4; k++) {
					if (m[i][k].num == cnt) {
						// move
						for (int q = 0; q < 8; q++) {
							int nx = k + dx[(m[i][k].dir + q) % 8];
							int ny = i + dy[(m[i][k].dir + q) % 8];

							if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4)
								continue;
							if (nx == sx && ny == sy)
								continue;

							point nw = m[ny][nx];
							point c = new point(m[i][k].num, (m[i][k].dir + q) % 8);

							// 교체
							m[i][k] = nw;
							m[ny][nx] = c;
							break;
						}

						break end;
					}
				}
			}
		
			if(cnt == 16) break;
			cnt++;
		}
	}
}
