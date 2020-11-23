#include <iostream>

using namespace std;

void make_next(string p, int nxt[]) {
	int len = p.length(), i = 0, j = -1;
	nxt[0] = -1;
	while (i < len) {
		if (j == -1 || p[i] == p[j])
			nxt[++i] = ++j;
		else j = nxt[j];
	}
}

void match(string s, string p, int nxt[]) {
	bool flag = false;
	int i = 0, j = 0, len_s = s.length(), len_p = p.length();
	while (i < len_s) {
		while (i < len_s && j < len_p) {
			if (j == -1 || s[i] == p[j])
				++i, ++j;
			else j = nxt[j];
		}
		if (j == len_p) {
			flag = true;
			cout << "match start at s" << i - len_p << endl;
			j = nxt[j];
		}
	}
	if (!flag) cout << "No match!" << endl;
}

int main() {
	string s, p;
	cin >> s;
	cin >> p;
	//cout << p.length() << "  " << s.length() << endl;

	int nxt[p.length()];
	make_next(p, nxt);
	match(s, p, nxt);
	return 0;
}