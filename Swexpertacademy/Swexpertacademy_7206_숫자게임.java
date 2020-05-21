import java.io.IOException;
import java.util.Scanner;

public class Solution {
   static int[] memo;
   static int answer = 0;
   public static void main(String[] args) throws IOException {
      Scanner sc = new Scanner(System.in);
      int T = sc.nextInt();
      memo = new int[100000];
      for(int n = 10; n < memo.length; n++) {
         char[] num = (n +"").toCharArray();
         memo[n] = getMax(num, num.length - 1);
      }
      for(int tc = 1; tc <= T; tc++) {
         System.out.println("#" + tc + " " + memo[sc.nextInt()]);
      }
   }
   static int getMax(char[] num, int n) {
      int maxV = -1;
      
      for(int i = 1; i < (int) Math.pow(2, n); i++) {
         int result = 1;
         String tmp ="";
         for(int idx = 0; idx < n; idx++) {
            tmp += num[idx];
            if((i & (1 << idx)) != 0) {
               result *= Integer.parseInt(tmp);
               tmp = "";
            }
         }
         tmp+= num[n];
         result *= Integer.parseInt(tmp);
         maxV = Math.max(maxV, memo[result]);
      }
      return maxV + 1;
   }
   
   static int getMultiple(String a, String b) {
      return Integer.parseInt(a) * Integer.parseInt(b);
   }
}