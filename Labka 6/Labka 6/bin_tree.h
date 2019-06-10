#ifndef BIN_TREE
#define BIN_TREE
#include "ordered_list.h"

class bin_tree :
	public ordered_list
{	// Binary search tree
private:
	class bin_tree_node
	{
	private:
		void change_parent(bin_tree_node* new_child = nullptr) const;
		void del_node_with_2children();
		void find_by_value(std::vector<complex>*& result, const double& value, const double& e) const;

		node _complex;
		bin_tree_node* left, * right, * parent;

	public:
		bin_tree_node(bin_tree_node* left = nullptr, bin_tree_node* right = nullptr, bin_tree_node* parent = nullptr);
		bin_tree_node(const node& _complex, bin_tree_node* left = nullptr, bin_tree_node* right = nullptr, bin_tree_node* parent = nullptr);
		void print() const;
		friend class bin_tree;
	};
	bin_tree_node* find(const complex& data);

	bin_tree_node* root;

public:
	bin_tree();
	void print() const override;
	void add(const complex& data) override;
	void add(bin_tree_node* new_node = nullptr);
	void add_n_random(size_t n) override;
	bool pop(const complex& data) override;
	std::vector<complex>* find_by_value(double value, double e = 0) const override;
};

#endif /* BIN_TREE */