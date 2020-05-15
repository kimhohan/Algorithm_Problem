import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main_15683 {
	static int Y, X;
	static int[][] map;
	static List<Point> list;
	static int ans = Integer.MAX_VALUE;

	static class Point {
		int y, x, cost;

		public Point(int y, int x, int cost) {
			this.x = x;
			this.y = y;
			this.cost = cost;
		}
	}

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		
		st = new StringTokenizer(br.readLine(), " ");
		Y = Integer.parseInt(st.nextToken());
		X = Integer.parseInt(st.nextToken());
		map = new int[Y][X];
		
		list = new ArrayList<Point>();
		

		for (int i = 0; i < Y; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			for (int k = 0; k < X; k++) {
				map[i][k] = Integer.parseInt(st.nextToken());
				if (map[i][k] != 0 && map[i][k] != 6)
					list.add(new Point(i, k, map[i][k]));
			}
		}

		// 최소 찾기
		dfs(0);
		
		System.out.println(ans);
	}

	static void mapCopy(int f, int[][] map, int [][]map_copy) {
		// 복원
		if(f == 1) {
			for(int i = 0; i < Y; i++) {
				for(int k = 0; k <X; k++) {
					map[i][k] = map_copy[i][k];
				}
			}
		}
		// 복사
		if(f == 2) {
			for(int i = 0; i < Y; i++) {
				for(int k = 0; k <X; k++) {
					map_copy[i][k] = map[i][k];
				}
			}
		}
	}
	
	static void spreed(int dir, int y, int x) {
		if(dir == 1) {
			map[y][x] = -1;
			int nx = x + 1;
			int ny = y;
			
			if(nx >= X || map[ny][nx] == 6) return;
			
			spreed(dir, ny, nx);
		} else if(dir == 3) {
			map[y][x] = -1;
			int nx = x - 1;
			int ny = y;
			
			if(nx < 0 || map[ny][nx] == 6) return;
			
			spreed(dir, ny, nx);
		} else if(dir == 2) {
			map[y][x] = -1;
			int nx = x;
			int ny = y + 1;
			
			if(ny >= Y || map[ny][nx] == 6) return;
			
			spreed(dir, ny, nx);
		} else if(dir == 0) {
			map[y][x] = -1;
			int nx = x;
			int ny = y - 1;
			
			if(ny < 0 || map[ny][nx] == 6) return;
			
			spreed(dir, ny, nx);
		}
	}	
	
	static void dfs(int cnt) {
		if (cnt == list.size()) {
			// 갯수세기
			int c = 0;
			for(int i = 0; i < Y; i++) {
				for(int k = 0; k <X; k++) {
					if(map[i][k]== 0)
						c++;
				}	
			}
			
			if(ans > c) {
				ans = c;
			}
			return;
		}

		// 칠하기
		int cctv = list.get(cnt).cost;
		int cx = list.get(cnt).x;
		int cy = list.get(cnt).y;
		

		int[][] map_copy = new int[Y][X];
		
		if (cctv == 1) {
			for (int i = 0; i < 4; i++) {
				// 복사
				mapCopy(2, map, map_copy);
				spreed(i, cy, cx);
				dfs(cnt+  1);
				// 복원
				mapCopy(1, map, map_copy);
			}
		} else if (cctv == 2) {
			for (int i = 0; i < 2; i++) {
				// 복사
				mapCopy(2, map, map_copy);
				spreed((i%4), cy, cx);
				spreed(((i+2)%4), cy, cx);
				dfs(cnt+  1);
				// 복원
				mapCopy(1, map, map_copy);
			}
		} else if (cctv == 3) {
			for (int i = 0; i < 4; i++) {
				// 복사
				mapCopy(2, map, map_copy);
				spreed((i%4), cy, cx);
				spreed(((i+1)%4), cy, cx);
				dfs(cnt+  1);
				// 복원
				mapCopy(1, map, map_copy);
			}
		} else if (cctv == 4) {
			for (int i = 0; i < 4; i++) {
				// 복사
				mapCopy(2, map, map_copy);
				spreed((i%4), cy, cx);
				spreed(((i+1)%4), cy, cx);
				spreed(((i+3)%4), cy, cx);
				dfs(cnt+  1);
				// 복원
				mapCopy(1, map, map_copy);
			}
		} else if (cctv == 5) {
			// 복사
			mapCopy(2, map, map_copy);
			spreed(0, cy, cx);
			spreed(1, cy, cx);
			spreed(2, cy, cx);
			spreed(3, cy, cx);
			dfs(cnt+  1);
			// 복원
			mapCopy(1, map, map_copy);
		}
	}
}
