import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class Solution_9760 {
	static public class point{
		char al;
		int num;
		
		public point(char al, int num) {
			this.al = al;
			this.num = num;
		}
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int t = sc.nextInt();
		for(int tc =1; tc <= t; tc++) {
			String ans =" ";
			
			List<point> M = new ArrayList<>();
			
			// ют╥б
			for(int i = 0; i < 5; i++) {
				String input = sc.next();
				char r_input[] = input.toCharArray();
				int num;
				if(r_input[1] == 'A') {
					num = 1;
				}else if(r_input[1] == 'T') {
					num = 10;
				}else if(r_input[1] == 'J') {
					num = 11;
				}else if(r_input[1] == 'Q') {
					num = 12;
				}else if(r_input[1] == 'K') {
					num = 13;
				}else{
					num = r_input[1] - '0';
				}
				M.add(new point(r_input[0], num));
			}
			
			Collections.sort(M, new Comparator<point>() {
				@Override
				public int compare(point o1, point o2) {
					// TODO Auto-generated method stub
					return o1.num - o2.num;
				}
			});
			
			int result_i = 0, result_c = 0,st_count = 0;
			
	        for(int i = 0; i<5;i++){
	            for(int j = i+1;j<5;j++){
	                if(M.get(i).al == M.get(j).al){
						result_i++;
	                }
	                if(M.get(i).num == M.get(j).num){
	                    result_c++;
	                }
	            }
	        }
	        
	        for(int i =0;i<4;i++){
	            if((M.get(i + 1).num - M.get(i).num == 1)){
	                st_count ++;
	            }
	        }
	        
	        if(result_i == 10){
	            if(st_count == 4) {
	            	ans = "Straight Flush";
	            }
	            else {
	            	ans = "Flush ";
	            }
	        }
	        else{
	            if(result_c == 1){
	            	ans = "One pair";
	            }
	            else if(result_c == 2){
	            	ans = "Two pair";
	            }
	            else if(result_c == 3){
	            	ans = "Three of a kind";
	            }
	            else if(result_c == 4){
	            	ans = "Full House";
	            }
	            else if(result_c == 6){
	            	ans = "Four of a Kind";
	            }
	            else if(st_count == 4){
	            	ans = "Straight";
	            }
	            else{
	            	ans = "High card";
	            }
	        }
	        
	        System.out.println("#" + tc + " " + ans);
		}
	}
}
