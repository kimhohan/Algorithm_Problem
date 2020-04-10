package 크루스칼;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class Solution_1251 {
	static int n;
	static double w;
	static double edges[][];
	static int []x;
	static int []y;
	
	static double []p;
	static double []r;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		
		for(int tc = 1; tc <= t; tc++) {
			n = sc.nextInt();
			int E = (n*(n-1))/2;
			p = new double[n];
			r = new double[n];
			x = new int[n];
			y = new int[n];
			edges = new double[E][3];
			
			// x입력
			for(int i = 0; i < n; i++) {
				x[i]  =sc.nextInt();
			}
			// y입력
			for (int i = 0; i < n; i++) {
				y[i] = sc.nextInt();
			}
			w =sc.nextDouble();
			
			// 크루스칼시작
			int cnt = 0;
			for(int i = 0; i < n; i++) {
				for(int k = i + 1; k < n; k++) {
					edges[cnt][0] = i;
					edges[cnt][1] = k;
					edges[cnt][2] = Math.pow(x[i] - x[k],2) + Math.pow(y[i] -y[k], 2);
					cnt++;
				}
			}
			
			// 정렬
			Arrays.sort(edges, new Comparator<double []>() {
				@Override
				public int compare(double[] o1, double[] o2) {
					// TODO Auto-generated method stub
					return Double.compare(o1[2], o2[2]);
				}
			});
			
			for(int i = 0; i < n; i++)
				makeSet(i);
			
			int cnt1 = 0;
			double res = 0;
			for(int i = 0; i< E; i++) {
				int a = (int) findSet((int)edges[i][0]);
				int b = (int) findSet((int)edges[i][1]);
				
				if(a == b)
					continue;
				
				union(a, b);
				
				res += edges[i][2];
				cnt1 ++;
				if(cnt1 == n-1)
					break;
			}
			
			res = res*w;
			
			System.out.println("#" + tc + " " + Math.round(res));
			
		}
	}
	
	static void makeSet(int x) {
		p[x] =x;
	}
	
	static double findSet(int x) {
		if(x == p[x]) {
			return x;
		}
		else {
			p[x] = findSet((int)p[x]);
			return p[x];
		}
	}
	
	static void union(int x, int y) {
		int px = (int) findSet(x);
		int py = (int) findSet(y);
		
		if(r[px] > r[py]) {
			p[py] = px;
		}
		else {
			p[px] = py;
			if(r[px] == r[py]) {
				r[py]++;
			}
		}
	}
	
}
