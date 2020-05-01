import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution{
	static int N, K;
	static int ans;
	static int[][] map;
	static int[][] visit;
	static List<point> list;
	static int[] dx = { 0, 0, 1, -1 };
	static int[] dy = { 1, -1, 0, 0 };

	static class point {
		int y, x;
		int v;

		public point(int y, int x, int v) {
			this.x = x;
			this.y = y;
			this.v = v;
		}
	}

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int t = Integer.parseInt(br.readLine());

		for (int tc = 1; tc <= t; tc++) {
			ans = 0;

			st = new StringTokenizer(br.readLine(), " ");
			N = Integer.parseInt(st.nextToken());
			K = Integer.parseInt(st.nextToken());

			map = new int[N][N];
			visit = new int[N][N];
			list = new ArrayList<point>();

			// 입력
			int max_v = 0;
			for (int i = 0; i < N; i++) {
				st = new StringTokenizer(br.readLine(), " ");
				int k = 0;
				while (st.hasMoreTokens()) {
					map[i][k] = Integer.parseInt(st.nextToken());
					if (map[i][k] > max_v) {
						max_v = map[i][k];
					}
					k++;
				}
			}

			// 최고점찾기
			for (int i = 0; i < N; i++) {
				for (int k = 0; k < N; k++) {
					if (map[i][k] == max_v) {
						list.add(new point(i, k, map[i][k]));
					}
				}
			}

			// 모든 점에 대해서 돌리기
			for (int i = 0; i < list.size(); i++) {
				point c = list.get(i);

				visit[c.y][c.x] = 1;
				dfs(c.y, c.x, c.v, 1, 1);
				visit[c.y][c.x] = 0;
			}

			System.out.println("#" + tc + " " + ans);
		}

	}

	static void dfs(int y, int x, int v, int cnt, int k_cnt) {
		if (cnt > ans) {
			ans = cnt;
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N || visit[ny][nx] == 1)
				continue;
			if (map[ny][nx] >= v) {
				if ((map[ny][nx] - K) < v && k_cnt != 0) {
					visit[ny][nx] = 1;
					cnt++;
					k_cnt--;
                    int t = map[ny][nx]; 
					map[ny][nx] = map[y][x] - 1; 
					dfs(ny, nx, map[ny][nx], cnt, k_cnt);
					visit[ny][nx] = 0;
					cnt--;
					k_cnt++;
					map[ny][nx] = t; 
				}
			} else {
				visit[ny][nx] = 1;
				cnt++;
				dfs(ny, nx, map[ny][nx], cnt, k_cnt);
				visit[ny][nx] = 0;
				cnt--;
			}
		}
	}
}
