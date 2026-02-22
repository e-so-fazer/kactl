/**
 * Author: Arthur Botelho
 * Description: combinatorics structure
 * Time: O(mxn)
 * Memory: O(mxn)
 * Status: stress-tested
*/

#include "../math/ModPow.h"

int mul(int a, int b) {return (int)((ll)a * b % mod);}
struct Combinatorics{
	vi f, fi;
	Combinatorics(int mxn):f(mxn),fi(mxn){
		f[0] = 1; rep(i, 1, mxn)f[i]=mul(f[i-1],i);
		fi[mxn-1] = modpow(f[mxn-1], mod-2);
		for(int i=mxn-1;i>0;i--)fi[i-1] = mul(fi[i],i);
	}
	int choose(int n, int k){return mul(f[n],mul(fi[k],fi[n-k]));}
};
