public class Solution {
	public static void main(String[] args) {
		String a = solution("()))((()");
		System.out.println(a);

	}

	public static String solution(String p) {
		if(p.length() == 0) {
			return "";
		}
		
		if(isCorrect(p) ==  true){
			return p;
		}
		
		int cnt = division(p);
		String u = p.substring(0, cnt);
		String v = p.substring(cnt, p.length());
		
		if(isCorrect(u) ==true) {
			return u + solution(v);
		} else {
			String temp = "(" + solution(v) + ")";
			u = u.substring(1, u.length() -1);
			u = reverse(u);
			
			return temp + u;
		}
	}

	// w를 가장 작은 크기의 균형 문자열로 자를 수 있는 index 리턴
	static int division(String w) {
		int close = 0, open = 0;
		int i;
		for (i = 0; i < w.length(); i++) {
			if (w.charAt(i) == '(') {
				open++;
			} else
				close++;
			if (open == close)
				return i + 1;
		}
		return i;
	}

	// 문자열 w의 옳은 문자열 여부 리턴
	static boolean isCorrect(String w) {
		int count = 0;
		for (int i = 0; i < w.length(); i++) {
			if (w.charAt(i) == '(') {
				count++;
			} else
				count--;
			if (count < 0)
				return false;
		}
		return count == 0;
	}

	// 문자열 w의 괄호방향 뒤집기
	static String reverse(String w) {

		StringBuffer ret = new StringBuffer();
		for (int i = 0; i < w.length(); i++) {
			if (w.charAt(i) == ')') {
				ret.append('(');
			} else
				ret.append(')');
		}
		return ret.toString();
	}
}