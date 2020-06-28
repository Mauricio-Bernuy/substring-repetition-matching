#include <iostream>
#include <vector>

using namespace std;

vector<int> z_function (const string & s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}

void output_tandem (const string & s, int shift, bool left, 
                    int cntr, int l, int l1, int l2) {
	int pos;
	if (left)
		pos = cntr-l1;
	else
		pos = cntr-l1-l2-l1+1;
	cout << "[" << shift + pos << ".." << 
    shift + pos+2*l-1 << "] = " << s.substr (pos, 2*l) << endl;
}
 
void output_tandems (const string & s, int shift, bool left, 
                        int cntr, int l, int k1, int k2) {
	for (int l1=1; l1<=l; ++l1) {
		if (left && l1 == l)  break;
		if (l1 <= k1 && l-l1 <= k2)
			output_tandem (s, shift, left, cntr, l, l1, l-l1);
	}
}
 
inline int get_z (const vector<int> & z, int i) {
	return 0<=i && i<(int)z.size() ? z[i] : 0;
}
 