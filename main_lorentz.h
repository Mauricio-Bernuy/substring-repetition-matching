
#include "main_lorentz2.h"
void main_lorentz (string s, int shift = 0, bool printing = 0) {
	int n = (int) s.length();
	if (n == 1)  return;
 
	int nu = n/2,  nv = n-nu;
	string u = s.substr (0, nu),
		v = s.substr (nu);
	string ru = string (u.rbegin(), u.rend()),
		rv = string (v.rbegin(), v.rend());
 
	main_lorentz (u, shift);
	main_lorentz (v, shift + nu);
 
	vector<int> z1 = z_function (ru),
		z2 = z_function (v + '#' + u),
		z3 = z_function (ru + '#' + rv),
		z4 = z_function (v);
	for (int cntr=0; cntr<n; ++cntr) {
		int l, k1, k2;
		if (cntr < nu) {
			l = nu - cntr;
			k1 = get_z (z1, nu-cntr);
			k2 = get_z (z2, nv+1+cntr);
		}
		else {
			l = cntr - nu + 1;
			k1 = get_z (z3, nu+1 + nv-1-(cntr-nu));
			k2 = get_z (z4, (cntr-nu)+1);
		}
		if (k1 + k2 >= l)
			if (printing == true ) output_tandems (s, shift, cntr<nu, cntr, l, k1, k2);
	}

}