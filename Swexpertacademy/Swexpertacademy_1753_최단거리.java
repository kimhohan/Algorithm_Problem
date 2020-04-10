package dijkstra;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Solution_1753 {
	
	static class Edge implements Comparable<Edge>{
		int v, w;
		public Edge(int v, int w) {
			this.v = v;
			this.w = w;
		}
		@Override
		public int compareTo(Edge arg0) {
			// TODO Auto-generated method stub
			return Integer.compare(this.w, arg0.w);
		}
		
	}
	
	static int V, E, start;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		//Scanner sc = new Scanner(System.in);
		StringTokenizer st;
		st = new StringTokenizer(br.readLine(), " ");
		
//		V = sc.nextInt();
//		V = V + 1;
//		E = sc.nextInt();
//		E = E + 1;
//		start = sc.nextInt();
		V= Integer.parseInt(st.nextToken());
		V =V + 1;
		E = Integer.parseInt(st.nextToken());
		E = E+1;
		start = Integer.parseInt(br.readLine());
		
		List<Edge> [] adj = new ArrayList[V];
		for(int i = 1; i < V; i++) {
			adj[i] = new ArrayList<>();
		}
		
		for(int i = 1; i < E; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			//adj[sc.nextInt()].add(new Edge(sc.nextInt(), sc.nextInt()));
			adj[ Integer.parseInt(st.nextToken())].add(new Edge( Integer.parseInt(st.nextToken()),  Integer.parseInt(st.nextToken())));
		}
		
		//다익스트라
		PriorityQueue<Edge> pq = new PriorityQueue<>();
		boolean[] check = new boolean[V];
		Edge[] D = new Edge[V];
		
		for(int i = 1; i < V; i++) {
			if(i == start) {
				D[i] = new Edge(i, 0);
			}
			else {
				D[i] = new Edge(i, Integer.MAX_VALUE);
			}
			// 이문제의 경우 다넣을려면  if(edge.w == Integer.MAX_VALUE) break; 가 필요
			// 시작점으로 돌아오지못하는 형태의 그래프가 존재할수있다(선분이 두개로 나누어져서 생기는 경우)
			pq.add(D[i]);
		}
		
		// if(edge.w == Integer.MAX_VALUE) break; 가없으면
		//check[start] = true;
		//pq.add(D[start]);
		
		while(!pq.isEmpty()) {
			Edge edge = pq.poll();
			
			// 중요!
			// 이것을 넣으면 모든 점을 다넣을 경우 - 두개로 나누어지는 형태의 그래프가 된다면 
			// 떨어지는 순간 모두 INF로 해야한다.
			// 즉 시작점만 넣어준다면  if(edge.w == Integer.MAX_VALUE) break; 는 의미 없다.
			if(edge.w == Integer.MAX_VALUE) break;
			
			for(Edge n : adj[edge.v]) {
				if(!check[n.v] && D[n.v].w > D[edge.v].w + n.w) {
					D[n.v].w = D[edge.v].w + n.w;
					
					pq.remove(D[n.v]);
					pq.add(D[n.v]);
				}
			}
			check[edge.v] = true;
		}
		
		for(int i = 1; i < V; i++) {
			if(i == start) {
				System.out.println("0");
			}else if(D[i].w == Integer.MAX_VALUE){
				System.out.println("INF");
			}else {
				System.out.println(D[i].w);
			}
		}
	}
}
