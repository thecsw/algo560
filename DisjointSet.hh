#ifndef _DISJOINT_SET_LIBRARY
#define _DISJOINT_SET_LIBRARY
#include "ArrayList.hh"

struct DisjointSetNode {
	DisjointSetNode *parent;
	int rank;
	int payload;
};

class DisjointSet {
    private:
	DisjointSetNode **_arr;
	int _len;

	// _to_build is the temp array stored before MakeSet is called.
	int *_to_build;

	// _find returns the representative node.
	DisjointSetNode *_find(int) const;
	// _get_node returns the actual node, nullptr if not found.
	DisjointSetNode *_get_node(int) const;
	// _path returns ArrayList of nodes, including source and rep.
	ArrayList<DisjointSetNode *> *_path(int) const;

    public:
	DisjointSet(int *, int);
	~DisjointSet();

	void MakeSet();
	int UnionByRank(int, int);
	int find(int) const;
	int PathCompression(int);
	void PrintPath(int) const;
};
#endif /* _DISJOINT_SET_LIBRARY */
