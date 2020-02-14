import java.util.ArrayList;
import java.util.Scanner;

public class Solution {
	static int[] parent;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int T = sc.nextInt();
		for(int i = 0; i < T; i++) {
			int N, M;
			N = sc.nextInt();
			M = sc.nextInt();
			
			ArrayList<Integer> list = new ArrayList<>();
			
			parent = new int[N + 1];
			makeSet();
			
			for(int k = 0; k < M ;k++) {
				int f = sc.nextInt();
				int x = sc.nextInt();
				int y = sc.nextInt();
				
				if( f== 0 ) {
					union(x, y);
				} else if (f == 1) {
					if(check(x, y) == 1) list.add(1);
					else list.add(0);
				}
			}
			
			System.out.print("#" + (i + 1) + " ");
			for(int k = 0; k < list.size(); k++) {
				System.out.print(list.get(k));
			}
			System.out.println();
			list.clear();
		}
		
	}
	
	static int check(int x, int y) {
		x = find(x);
		y = find(y);
		
		if(x == y) return 1;
		else return 0;
	}
	
	static void makeSet() {
		for(int i = 0; i < parent.length; i++) {
			parent[i] = i;
		}
	}
	
	static int find(int x) {
		if(x == parent[x] ) {
			return x;
		}
		
		int nx = find(parent[x]);
		parent[x] = nx;
		return nx;
	}
	
	static void union(int x, int y) {
		x = find(x);
		y = find(y);
		
		parent[y] = x;
	}
}
