#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>
#include <string>
using namespace std;

const int MAXN = 1000;
const int M = 6;

char cases[][MAXN] = {
    "AGCGUUGCGCACUU",
    "AAAAAAAAAAAAAA",
    "AAAAAAAUUUUUUU",
    "AGCU",
    "",
    "A"
    };

char *x;

int N[MAXN][MAXN];

bool match(char ch1, char ch2) {
	if (ch1 == 'C' && ch2 == 'G') return true;
	if (ch1 == 'A' && ch2 == 'U') return true;
	if (ch1 == 'G' && ch2 == 'U') return true;
	return false;
}

int solve(int i, int j) {
	if (N[i][j] > -1) return N[i][j];

	N[i][j] = solve(i, j - 1);

	if (match(x[i], x[j]) || match(x[j], x[i])) {
		N[i][j] = max(N[i][j], solve(i + 1, j - 1) + 1);
	}

	for (int k = i + 1; k <= j - 2; k++) {
		N[i][j] = max(N[i][j], solve(i, k) + solve(k + 1, j));
	}

	return N[i][j];
}

void printOpt(int i, int j) {
	if (i > j) return;

	if (N[i][j] == N[i][j - 1]) {
		printOpt(i, j - 1);
		putchar('.');
		return;
	}

	if ((match(x[i], x[j]) || match(x[j], x[i]))
		&& N[i][j] == N[i + 1][j - 1] + 1) {
		putchar('(');
		printOpt(i + 1, j - 1);
		putchar(')');
		return;
	}

	for (int k = i + 1; k <= j - 2; k++) {
		if (N[i][j] == N[i][k] + N[k + 1][j]) {
			printOpt(i, k);
			printOpt(k + 1, j);
			return;
		}
	}
}

int ans;
int n;
stack<char> st;
int counts;

void printAllOpts(int m, int cnt, string s) {
    // printf("%d\n", m);
    if (m >= n) {
        if (cnt == ans && st.empty()) {
            puts(s.c_str());
            counts++;
        }
        return;
    }

    if (!st.empty() && (match(st.top(), x[m]) || match(x[m], st.top()))) {
        int t = st.top();
        st.pop();
        printAllOpts(m + 1, cnt + 1, s + ')');
        st.push(t);
    }
    st.push(x[m]);
    printAllOpts(m + 1, cnt, s + '(');
    st.pop();
    printAllOpts(m + 1, cnt, s + '.');
}

int main() {
	//scanf("%s", x);
	for (int re = 0; re < M; re++) {
	    x = cases[re];
        n = strlen(x);
        // set all the value in array N as 0.
        memset(N, -1, sizeof(N));

        N[0][0] = 0;
        for (int i = 1; i < n; i++) {
            N[i][i] = 0;
            N[i][i - 1] = 0;
        }
        ans = solve(0, n - 1);
        printf("Answer: %d\n", ans);
        puts(x);
        // printOpt(0, n - 1); puts("");
        counts = 0;
        printAllOpts(0, 0, ""); printf("number of optimal: %d\n", counts);
        puts("\n");
	}
}
