/**
 * Author: Ruan Petrus
 * Description: Suffix automaton
 * Time: O(n) build
 * Memory: O(n * 26)
 * Status: not yet tested
 */

vector<int> len, lnk;
vector<array<int,26>> to;
int saID;
void push(int c, int a, int p) {
	len[a] = len[p] + 1;
	for (; p > 0 && !to[p][c]; p = lnk[p]) to[p][c] = a;
	int q = to[p][c];
	if (p == 0) lnk[a] = 1;
	else if (len[p] + 1 == len[q]) lnk[a] = q;
	else {
		int clone = saID++;
		lnk[clone] = lnk[q];
		to[clone] = to[q];
		len[clone] = len[p] + 1;
		lnk[a] = lnk[q] = clone;
		for (; to[p][c] == q; p = lnk[p]) to[p][c] = clone;
	}
}
void construct(const string &s) {
	int n = sz(s);
	len.assign(2*n+2, 0), lnk.assign(2*n+2, 0);
	to.assign(2*n+2, {0});
	int p = 1;
	saID = n+2;
	for (auto c: s) push(c-'a', p+1, p), p++;
}
