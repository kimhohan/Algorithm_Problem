import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class Point {
	int a, b, c;

	public Point(int a, int b, int c) {
		this.a = a;
		this.b = b;
		this.c = c;
	}
}

public class Main {
	static int A, B, C;
	static int visit[][][];

	static ArrayList<Integer> ans = new ArrayList<>();

	public static void main(String[] args) {
		// TODO Auto-generated constructor stub
		Scanner sc = new Scanner(System.in);
		A = sc.nextInt();
		B = sc.nextInt();
		C = sc.nextInt();
		visit = new int[A + 1][B + 1][C + 1];
		bfs();
		
		Collections.sort(ans);
		
		for (int i : ans) {
			System.out.print(i + " ");
		}
	}

	public static void bfs() {
		Queue<Point> q = new LinkedList<>();

		q.offer(new Point(0, 0, C));

		while (!q.isEmpty()) {
			Point p = q.poll();
			int ca = p.a;
			int cb = p.b;
			int cc = p.c;

			if (visit[ca][cb][cc] == 1) 
				continue;
			
			visit[ca][cb][cc] = 1;
			
			if (ca == 0)
				ans.add(cc);

			if (ca != 0) {
				if (cb < B) {
					int na = 0;
					int nb = cb + ca;
					if (nb > B) {
						na = nb - B;
						nb = B;
					}

					q.offer(new Point(na, nb, cc));
				}
				if (cc < C) {
					int na = 0;
					int nc = cc + ca;
					if (nc > C) {
						na = nc - C;
						nc = C;
					}
					
					q.offer(new Point(na, cb, nc));
					
				}
			}

			if (cb != 0) {
				if (ca < A) {
					int nb = 0;
					int na = cb + ca;
					if (na > A) {
						nb = na - A;
						na = A;
					}

					q.offer(new Point(na, nb, cc));
					
				}
				if (cc < C) {
					int nb = 0;
					int nc = cc + cb;
					if (nc > C) {
						nb = nc - C;
						nc = C;
					}

					q.offer(new Point(ca, nb, nc));
				}
			}

			if (cc != 0) {
				if (ca < A) {
					int nc = 0;
					int na = cc + ca;
					if (na > A) {
						nc = na - A;
						na = A;
					}

					q.offer(new Point(na, cb, nc));
					
				}
				if (cb < B) {
					int nc = 0;
					int nb = cc + cb;
					if (nb > B) {
						nc = nb - B;
						nb = B;
					}

					q.offer(new Point(ca, nb, nc));
					
				}
			}
		}
	}
}
