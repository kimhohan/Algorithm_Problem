import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main_2933{
	static int Y, X;
	static int N;
	static char map[][];
	static int visit[][];
	static int[] thw;
	static List<Integer> list;

	static int dx[] = { 0, 0, 1, -1 };
	static int dy[] = { 1, -1, 0, 0 };

	static class Point {
		int y, x;

		public Point(int y, int x) {
			this.x = x;
			this.y = y;
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;

		st = new StringTokenizer(br.readLine(), " ");
		Y = Integer.parseInt(st.nextToken());
		X = Integer.parseInt(st.nextToken());

		map = new char[Y][X];

		for (int i = 0; i < Y; i++) {
			String line = br.readLine();
			char[] lines = line.toCharArray();
			for (int k = 0; k < X; k++) {
				map[i][k] = lines[k];
			}
		}

		N = Integer.parseInt(br.readLine());
		thw = new int[N];
		st = new StringTokenizer(br.readLine(), " ");
		for (int i = 0; i < N; i++) {
			thw[i] = Integer.parseInt(st.nextToken());
		}

		// 쏘기 시작
		for (int i = 0; i < N; i++) {
			int gun = thw[i];

			// 짝수면 왼쪽
			if ((i % 2) == 0) {
				// 미네랄 지우기
				removeMi(Y - gun, 0, 0);

				// 크러스트 구별해내기 및 떨어 뜨릴거 찾기
				list = new ArrayList<Integer>();
				visit = new int[Y][X];
				find();

				// 떨어 뜨리기
				if (list.size() != 0) {
					int dis = droping();
					// 진짜 떨어뜨리기
					drop(dis);
				}

			}
			// 홀수면 오른쪽
			else if ((i % 2) == 1) {
				removeMi(Y - gun, X - 1, 1);

				// 크러스트 구별해내기 및 떨어 뜨릴거 찾기
				list = new ArrayList<Integer>();
				visit = new int[Y][X];
				find();

				// 떨어 뜨리기
				if (list.size() != 0) {
					int dis = droping();
					// 진짜 떨어뜨리기
					drop(dis);
				}
			}
		}

		// 출력
		for (int i = 0; i < Y; i++) {
			for (int k = 0; k < X; k++) {
				System.out.print(map[i][k]);
			}
			System.out.println();
		}
	}

	static void drop(int d) {

		for (int j = 0; j < X; j++) {
			for (int k = Y - 1; k >= 0; k--) {
				if (visit[k][j] == list.get(0)) {
					char temp = map[k][j];
					map[k][j] = map[k + d][j];
					map[k + d][j] = temp;
				}
			}
		}
	}

	static int droping() {

		int min_d = 987654321;

		for (int i = 0; i < X; i++) {
			int b_y = Y;
			int e_y = 0;

//			for (int k = 0; k < Y; k++) {
//				if (visit[k][i] == list.get(0)) {
//					b_y = k;
//					for (int j = k + 1; j < Y; j++) {
//						k = j;
//						if (visit[j][i] != 0 && visit[j][i] != list.get(0)) {
//							e_y = j;
//							int d = e_y - b_y - 1;
//							if (min_d > d && d > 0) {
//								min_d = d;
//							}
//						} else if (visit[j][i] == list.get(0)) {
//							k--;
//							break;
//						}
//					}
//				}
//			}
//
//			e_y = Y;
//			// 길이가 가장 짧을 곳 찾기
//			int d = e_y - b_y - 1;
//			if (min_d > d && d > 0) {
//				min_d = d;
//			}

			// 길이가 가장 짧을 곳 찾기

			for (int k = 0; k < Y; k++) {
				if (visit[k][i] == list.get(0)) {
					b_y = k;
				} else if (visit[k][i] != 0 && visit[k][i] != list.get(0)) {
					e_y = k;
					// 길이가 가장 짧을 곳 찾기
					int d = e_y - b_y - 1;
					if (min_d > d && d > 0) {
						min_d = d;
					}

				}
			}
			e_y = Y;

			// 길이가 가장 짧을 곳 찾기
			int d = e_y - b_y - 1;
			if (min_d > d && d > 0) {
				min_d = d;
			}
		}

		return min_d;
	}

	static void removeMi(int y, int x, int flag) {
		Queue<Point> q = new LinkedList<Point>();
		q.offer(new Point(y, x));

		while (!q.isEmpty()) {
			Point p = q.poll();
			int cx = p.x;
			int cy = p.y;

			if (flag == 0) {

				if (cx >= X)
					break;

				if (map[cy][cx] == 'x') {
					map[cy][cx] = '.';
					break;
				}

				if (map[cy][cx] == '.') {
					q.offer(new Point(cy, cx + 1));
				}
			} else if (flag == 1) {

				if (cx < 0)
					break;

				if (map[cy][cx] == 'x') {
					map[cy][cx] = '.';
					break;
				}

				if (map[cy][cx] == '.') {
					q.offer(new Point(cy, cx - 1));
				}
			}
		}
	}

	static void find() {
		int cnt = 1;
		for (int i = 0; i < Y; i++) {
			for (int k = 0; k < X; k++) {
				if (visit[i][k] == 0 && map[i][k] == 'x') {
					bfs(i, k, cnt);
					cnt++;
				}
			}
		}
	}

	static void bfs(int y, int x, int cnt) {
		Queue<Point> q = new LinkedList<Point>();
		q.offer(new Point(y, x));
		visit[y][x] = cnt;
		int flag = 0;

		while (!q.isEmpty()) {
			Point p = q.poll();

			int cx = p.x;
			int cy = p.y;

			for (int i = 0; i < 4; i++) {
				int nx = cx + dx[i];
				int ny = cy + dy[i];

				if (ny < 0 || nx < 0 || nx >= X || ny >= Y || visit[ny][nx] > 0 || map[ny][nx] == '.')
					continue;
				if (ny == Y - 1) {
					// 바닥에 붙어있다
					flag = 1;
				}

				visit[ny][nx] = cnt;
				q.offer(new Point(ny, nx));
			}
		}

		if (flag == 0) {
			// 바닥으로 떨구기
			list.add(cnt);
		}
	}
}
