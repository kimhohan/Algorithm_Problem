import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	static int[] parent;
	static int[] visit;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		ArrayList<Integer> list = new ArrayList<>();
		int N, M;
		N = sc.nextInt();
		M = sc.nextInt();

		parent = new int[N + 1];
		visit = new int[N + 1];
		
		makeSet();

		for (int k = 0; k < M; k++) {
			int x = sc.nextInt();
			int y = sc.nextInt();

			union(x, y, 1);
		}
		
		int ans = 0;
		
		for(int i=1; i<parent.length; i++) {
			if(parent[i]==i) ans++;
		}
		System.out.println(ans);
	}

	static void makeSet() {
		for (int i = 0; i < parent.length; i++) {
			parent[i] = i;
		}
	}

	static int find(int x, int f) {
		if(f == 1) {
			visit[x] = 1;
		}
		if (x == parent[x]) {
			return x;
		}

		return parent[x] = find(parent[x], f);
	}

	static void union(int x, int y, int f) {
		x = find(x, f);
		y = find(y, f);
		
		parent[y] = x;
	}
}
