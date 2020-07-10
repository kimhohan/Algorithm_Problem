import java.util.Arrays;
import java.util.Comparator;

public class 가장큰수 {
	public static void main(String[] args) {
		int[] array = { 1, 5, 2, 6, 3, 7, 4 };
		int[][] commands = { { 2, 5, 3 }, { 4, 4, 1 }, { 1, 7, 3 } };
		// int[] ans = solution(array, commands);
		int number[] = { 3, 30, 34, 5, 9 };
		String ans = solution(number);

		/*
		 for (int i = 0; i < ans.length; i++) { System.out.println(ans[i]); }
		 */
		System.out.println(ans);

	}

	static public String solution(int[] numbers) {
		String answer = new String();
		/** 1 **/
		String str_numbers[] = new String[numbers.length];
		
		/** 2 **/
		for(int i=0; i<str_numbers.length; i++) {
			str_numbers[i] = String.valueOf(numbers[i]);
		}
		
		/** 3 **/
		Arrays.sort(str_numbers, new Comparator<String>() {
			@Override
			public int compare(String o1, String o2) {
				return (o2+o1).compareTo(o1+o2);
			}
		});
		
		/** 4 **/
		if(str_numbers[0].startsWith("0")) { 
			answer += "0";
		} else {
			for(int j=0; j<str_numbers.length; j++) {
				answer += str_numbers[j];
			}
		}
		
		return answer;
	}
}