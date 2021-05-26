#ifndef BINARY_SEARCH_TREE_HH
#define BINARY_SEARCH_TREE_HH
#include "BinarySearchNode.hh"
#include <functional>

class BinarySearchTree {
    private:
	BinarySearchNode *_root;

	BinarySearchNode *_add(BinarySearchNode *, BinarySearchNode *);
	void _clear(BinarySearchNode *);
	BinarySearchNode *_find(BinarySearchNode *, int);
	BinarySearchNode *_remove(BinarySearchNode *, int);

	int _get_size(BinarySearchNode *) const;
	int _get_height(BinarySearchNode *) const;
	int _find_min(BinarySearchNode *) const;
	int _find_max(BinarySearchNode *) const;

	void _fill_arr_with_inorder(BinarySearchNode *, int *, int *) const;

	void _visit_pre_order(BinarySearchNode *,
			      std::function<void(int)>) const;
	void _visit_post_order(BinarySearchNode *,
			       std::function<void(int)>) const;
	void _visit_in_order(BinarySearchNode *,
			     std::function<void(int)>) const;
	void _visit_left_side_view(BinarySearchNode *,
				   std::function<void(int)>) const;
	void _visit_right_side_view(BinarySearchNode *,
				    std::function<void(int)>) const;
	void _visit_level_order_level(BinarySearchNode *, int,
				      std::function<void(int)>) const;
	void _visit_level_order_level_no_visit(BinarySearchNode *, int, int *,
					       int *) const;

    public:
	BinarySearchTree();
	~BinarySearchTree();

	void add(int);
	void remove(int);
	void clear();

	void removeMin();
	void removeMax();

	bool isEmpty() const;
	int getSize() const;
	int getHeight() const;
	int findMin() const;
	int findMax() const;

	int findInOrderSuccessor(int) const;

	void visitPreOrder(std::function<void(int)>) const;
	void visitPostOrder(std::function<void(int)>) const;
	void visitInOrder(std::function<void(int)>) const;
	void visitLeftSideView(std::function<void(int)>) const;
	void visitRightSideView(std::function<void(int)>) const;
	void visitLevelOrder(std::function<void(int)>) const;
	void visitSpiralLevelOrder(std::function<void(int)>) const;
};
#endif
