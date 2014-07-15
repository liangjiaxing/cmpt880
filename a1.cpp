#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 1000;

char x[MAXN] = "AGCGUUGCGCACUU";

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

int main() {
	//scanf("%s", x);
	int n = strlen(x);

	// set all the value in array N as 0.
	memset(N, -1, sizeof(N));

	N[0][0] = 0;
	for (int i = 1; i < n; i++) {
		N[i][i] = 0;
		N[i][i - 1] = 0;
	}

	printf("Answer: %d\n", solve(0, n - 1));
	puts(x);
	printOpt(0, n - 1);
	puts("");
}
