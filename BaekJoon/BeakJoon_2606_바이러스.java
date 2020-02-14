import java.util.Scanner;

public class Main {
	static int[] parent;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int N, M;
		N = sc.nextInt();
		M = sc.nextInt();

		parent = new int[N + 1];
		makeSet();

		for (int k = 0; k < M; k++) {
			int x = sc.nextInt();
			int y = sc.nextInt();

			union(x, y);
		}
		
		int ans = 0;
		int f = find(1);
		for(int i = 2; i < parent.length; i++) {
			if(find(i) == f) ans++;
		}
		
		System.out.println(ans);
	}


	static void makeSet() {
		for (int i = 0; i < parent.length; i++) {
			parent[i] = i;
		}
	}

	static int find(int x) {
		if (x == parent[x]) {
			return x;
		}

		return parent[x] = find(parent[x]);
	}

	static void union(int x, int y) {
		x = find(x);
		y = find(y);

		parent[y] = x;
	}
}