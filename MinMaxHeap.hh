#ifndef __MIN_MAX_HEAP
#define __MIN_MAX_HEAP
class MinMaxHeap {
    private:
	int *_arr;
	int _len;
	int _cap;

	void _expand();
	void _upheap_min(int);
	void _upheap_max(int);
	void _push_down(int);

	int _first_kid(int) const;
	int _second_kid(int) const;
	int _parent(int) const;
	int _grandparent(int) const;
	bool _is_min(int) const;
	bool _is_max(int) const;
	int _find_second_smallest() const;
	int _find_largest() const;
	int _find_second_largest() const;

    public:
	MinMaxHeap();
	~MinMaxHeap();
	void BuildHeap(int *, int);
	void Insert(int);
	int DeleteMin();
	int DeleteMax();
	int FindMin() const;
	int FindMax() const;
	void PrintAllLevels() const;
	void MinLevelElements() const;
	void MaxLevelElements() const;
	int getSize() const;
};
#endif
