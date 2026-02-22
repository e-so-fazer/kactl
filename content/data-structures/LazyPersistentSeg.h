/**
 * Author: Arthur Botelho
 * Description: Persistent Lazy Sparse Segment Tree
 * Can be changed by modifying Spec
 * Time: O(\log N * (ch + cmp))
 * Status: not stress-tested
 */

template<class I, class S> struct LazyPersistentSeg{ //I is index type
	using T = typename S::T; //value type
	using L = typename S::L; //lazy type
	struct Node{int lc, rc; T val; L lz; bool ig;};
	I n; vector<Node> v;
	int new_node(int l=0, int r=0){return v.eb(l,r,S::op(v[l].val,v[r].val),L(),1), sz(v)-1;}
	LazyPersistentSeg(){ //only creates object, should be "init"ed to get root
		//v.reserve(MXN); //faster node creation
		v.eb(0,0,S::id,L(),1); //blank node
	}
	int init(I s){return n = s, new_node();}
	int lazy_clone(int i, L lz, I lx, I rx){
		int ni = new_node(v[i].lc, v[i].rc);
		v[ni].lz = v[i].ig ? lz : S::cmp(v[i].lz, lz); 
		v[ni].ig = 0; v[ni].val = S::ch(v[i].val, lz, lx, rx);
		return ni;
	}
	void prop(int i, I lx, I rx){
		if (v[i].ig)return;
		int mx = lx + (rx - lx) / 2; v[i].ig = 1;
		if (lx < rx)
			v[i].lc = lazy_clone(v[i].lc, v[i].lz, lx, mx),
			v[i].rc = lazy_clone(v[i].rc, v[i].lz, mx, rx);
	}
	int update(L lz, I l, I r, int root){return update(lz, l, r, root, 0, n);}
	int update(L lz, I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return i;
		if (l <= lx and rx <= r)return lazy_clone(i, lz, lx, rx);
		I mx = lx + (rx - lx) / 2; prop(i, lx, rx);
		return new_node(update(lz, l, r, v[i].lc, lx, mx), update(lz, l, r, v[i].rc, mx, rx));
	}
	T query(I l, I r, int root){return query(l, r, root, 0, n);}
	T query(I l, I r, int i, I lx, I rx){
		if (r <= lx or rx <= l)return S::id;
		if (l <= lx and rx <= r)return v[i].val;
		I mx = lx + (rx - lx) / 2; prop(i, lx, rx);
		return S::op(query(l, r, v[i].lc, lx, mx), query(l, r, v[i].rc, mx, rx));
	}
};