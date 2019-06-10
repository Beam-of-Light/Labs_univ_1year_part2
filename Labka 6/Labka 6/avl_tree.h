#ifndef AVL_TREE
#define AVL_TREE
#include "ordered_list.h"

class avl_tree :
	public ordered_list
{
private:
	class avl_node
	{
	private:
		unsigned char node_height();
		int balance_factor();
		void fix_height();
		avl_node* rotate_right();
		avl_node* rotate_left();
		avl_node* balance();
		avl_node* find_min();
		avl_node* remove_min();
		avl_node* remove(avl_node*& del_node, bool& check);
		void find_by_value(std::vector<complex>*& result, const double& value, const double& e) const;

		node _complex;
		avl_node* left, * right;
		unsigned char height;
	
	public:
		avl_node();
		avl_node(const node& _complex);
		avl_node* add(avl_node*& new_node);
		void print() const;

		friend class avl_tree;
	};
	avl_node* root;

public:
	avl_tree();
	void print() const override;
	void add(const complex& data) override;
	void add(avl_node* new_node = nullptr);
	void add_n_random(size_t n) override;
	bool pop(const complex& data) override;
	std::vector<complex>* find_by_value(double value, double e = 0) const override;
};

#endif /* AVL_TREE */