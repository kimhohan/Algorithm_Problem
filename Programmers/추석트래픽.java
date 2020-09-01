import java.util.LinkedList;
import java.util.List;

public class Solution {

	public static void main(String[] args) {

//		String[] key = {

//				"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>",

//				"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>",

//				"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>" };

//		String word = "blind";

		String[] key = {

				"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>",

				"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>" };

		String word = "Muzi";

		// int[][] lock = { { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 1 } };

		// "CBD" ["BACDE", "CBADF", "AECB", "BDA"]

		String[] skill_trees = { "BACDE", "CBADF", "AECB", "BDA" };

		String skill = "CBD";

		String[][] clothes = { { "yellow_hat", "headgear" }, { "blue_sunglasses", "eyewear" },

				{ "green_turban", "headgear" }, { "green_turban", "head" }, { "green_turbaasdn", "head" },

				{ "green_turban", "headge" }, { "green_turbawdwdn", "headge" } };

		int[][] a = { { 2, 5, 3 }, { 4, 4, 1 }, { 1, 7, 3 } };

		String[] asd = { "119", "97674223", "11195524421" };

		int[] b = { 1, 2, 7, 6, 4 };

//		String[] lines = {
//				"2016-09-15 20:59:57.421 0.351s",
//				"2016-09-15 20:59:58.233 1.181s",
//				"2016-09-15 20:59:58.299 0.8s",
//				"2016-09-15 20:59:58.688 1.041s",
//				"2016-09-15 20:59:59.591 1.412s",
//				"2016-09-15 21:00:00.464 1.466s",
//				"2016-09-15 21:00:00.741 1.581s",
//				"2016-09-15 21:00:00.748 2.31s",
//				"2016-09-15 21:00:00.966 0.381s",
//				"2016-09-15 21:00:02.066 2.62s"
//		};

		String[] lines = { "2016-09-15 01:00:04.002 2.0s", "2016-09-15 01:00:07.000 2s" };

		int res = solution(lines);

		System.out.println(res);

	}

	static class list {
		double start;
		double end;

		public list(double start, double end) {
			this.start = start;
			this.end = end;
		}
	}

	public static int solution(String[] lines) {
		int answer = 0;
		//List<list> list = new LinkedList<list>();
		double startTime[] = new double[lines.length];
		double endTime[] = new double[lines.length];
		
		for (int i = 0; i < lines.length; i++) {
			String stand = lines[i].substring(11, 23);
			String times = lines[i].substring(24, lines[i].length() - 1);
			String[] time = stand.split(":");
			double t = Double.parseDouble(times);
			int h = Integer.parseInt(time[0]);
			int m = Integer.parseInt(time[1]);
			double s = Double.parseDouble(time[2]);

			double end = (h * 3600) + (m * 60) + s;
			double start = end -t +0.001;

			startTime[i]  = start;
			endTime[i]  = end;
			//list.add(new list(start, end));
		}
		
		// 최댓 값찾기
		for (int i = 0; i < startTime.length; i++) {
			int res = 0;

			double ss = startTime[i];
			double se = ss + 1;

			for (int k = 0; k < startTime.length; k++) {

				if (ss <= startTime[k] && se > startTime[k]) {
					res++;
					continue;
				}

				if (ss <= endTime[k] && se > endTime[k]) {
					res++;
					continue;
				}

				// 사이 일때
				if (ss >= startTime[k] && se <= endTime[k]) {
					res++;
					continue;
				}
			}

			if (answer < res) {
				answer = res;
			}
		}

		for (int i = 0; i < startTime.length; i++) {
			int res = 0;

			double ss = endTime[i];
			double se = ss + 1;

			for (int k = 0; k < startTime.length; k++) {

				if (ss <= startTime[k] && se > startTime[k]) {
					res++;
					continue;
				}

				if (ss <= endTime[k] && se > endTime[k]) {
					res++;
					continue;
				}

				// 사이 일때
				if (ss >= startTime[k] && se <= endTime[k]) {
					res++;
					continue;
				}
			}

			if (answer < res) {
				answer = res;
			}
		}

		return answer;
	}

}