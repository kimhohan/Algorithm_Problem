import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import javax.swing.plaf.synth.SynthSplitPaneUI;

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

		String[] lines = { "2016-09-15 20:59:57.421 0.351s", "2016-09-15 20:59:58.233 1.181s",
				"2016-09-15 20:59:58.299 0.8s", "2016-09-15 20:59:58.688 1.041s", "2016-09-15 20:59:59.591 1.412s",
				"2016-09-15 21:00:00.464 1.466s", "2016-09-15 21:00:00.741 1.581s", "2016-09-15 21:00:00.748 2.31s",
				"2016-09-15 21:00:00.966 0.381s", "2016-09-15 21:00:02.066 2.62s" };

		String[] words = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
		String[] q = { "fro??", "????o", "fr???", "fro???", "pro?" };

//		int[][] frame = { { 1, 0, 0, 1 }, { 1, 1, 1, 1 }, { 2, 1, 0, 1 }, { 2, 2, 1, 1 }, { 5, 0, 0, 1 },
//				{ 5, 1, 0, 1 }, { 4, 2, 1, 1 }, { 3, 2, 1, 1 } };

		int[][] frame = { { 0, 0, 0, 1 }, { 2, 0, 0, 1 }, { 4, 0, 0, 1 }, { 0, 1, 1, 1 }, { 1, 1, 1, 1 },
				{ 2, 1, 1, 1 }, { 3, 1, 1, 1 }, { 2, 0, 0, 0 }, { 1, 1, 1, 0 }, { 2, 2, 0, 1 } };

		int[][] res = solution(5, frame);

		System.out.println(res);
	}

	static class point {
		int y, x, con;

		public point(int y, int x, int con) {
			this.y = y;
			this.x = x;
			this.con = con;
		}

	}

	static int[][] gi_map;
	static int[][] bo_map;

	public static int[][] solution(int n, int[][] build_frame) {
		int[][] answer = {};
		List<point> list = new LinkedList<point>();
		gi_map = new int[n + 2][n + 2];
		bo_map = new int[n + 2][n + 2];
		// map:1 -> 기둥, map:2 -> 보

		for (int i = 0; i < build_frame.length; i++) {
			int x = build_frame[i][0] + 1;
			int y = build_frame[i][1] + 1;
			int what = build_frame[i][2];
			int how = build_frame[i][3];
			int flag = 0;
			// 설치
			if (how == 1) {
				// 기둥이라면
				if (what == 0) {
					if (cangi(y, x) == 1) {
						gi_map[y][x] = 1;
						flag = 1;
					}
				}
				if (what == 1) {
					if (canbo(y, x) == 1) {
						bo_map[y][x] = 1;
						flag = 1;
					}
				}

				// answer 대입
				if (flag == 1) {
					list.add(new point(y-1, x-1, what));
				}
			}
			// 삭제
			else {
				if (what == 0) {
					gi_map[y][x] = 0;
				} else {
					bo_map[y][x] = 0;
				}

				if (candelete(y, x, n) == 1) {
					// 지우기
					for (int q = 0; q < list.size(); q++) {
						if (list.get(q).x+1 == x && list.get(q).y+1 == y && list.get(q).con == what) {
							list.remove(q);
							break;
						}
					}
					continue;
				}

				if (what == 0) {
					gi_map[y][x] = 1;
				} else {
					bo_map[y][x] = 1;
				}
			}
		}

		// list정렬
		list.sort(new Comparator<point>() {

			@Override
			public int compare(point o1, point o2) {
				// TODO Auto-generated method stub
				if (o1.x == o2.x && o1.y == o2.y) {
					return o1.con - o2.con;
				}
				if (o1.x == o2.x) {
					return o1.y - o2.y;
				}
				return o1.x - o2.x;
			}
		});

		return answer;
	}

	static int canbo(int y, int x) {
		if (gi_map[y-1][x] == 1 || gi_map[y - 1][x + 1] == 1 || (bo_map[y][x - 1] == 1 && bo_map[y][x + 1] == 1)) {
			return 1;
		}
		return 0;
	}

	static int cangi(int y, int x) {
		if (y == 1 || gi_map[y - 1][x] == 1 || bo_map[y][x] == 1 || bo_map[y][x - 1] == 1) {
			return 1;
		}
		return 0;
	}

	static int candelete(int y, int x, int n) {
		for (int i = 1; i <= n + 1; ++i) {
			for (int j = 1; j <= n + 1; ++j) {
				if (gi_map[i][j] == 1 && cangi(i, j) == 0) {
					return 0;
				}
				if (bo_map[i][j] == 1 && canbo(i, j) == 0) {
					return 0;
				}
			}
		}

		return 1;
	}
}
