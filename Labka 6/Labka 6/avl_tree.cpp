#include "avl_tree.h"

unsigned char avl_tree::avl_node::node_height()
{
	return (this ? this->height : 0);
}

int avl_tree::avl_node::balance_factor()
{
	return (this->right->node_height() - this->left->node_height());
}

void avl_tree::avl_node::fix_height()
{
	unsigned char hl = this->left->node_height();
	unsigned char hr = this->right->node_height();
	this->height = (hl > hr ? hl : hr) + 1;
}

avl_tree::avl_node* avl_tree::avl_node::rotate_right()
{
	avl_node* q = this->left;
	this->left = q->right;
	q->right = this;
	this->fix_height();
	q->fix_height();
	return q;
}

avl_tree::avl_node* avl_tree::avl_node::rotate_left()
{
	avl_node* p = this->right;
	this->right = p->left;
	p->left = this;
	this->fix_height();
	p->fix_height();
	return p;
}

avl_tree::avl_node* avl_tree::avl_node::balance()
{
	this->fix_height();
	if (this->balance_factor() == 2) {
		if (this->right->balance_factor() < 0)
			this->right = this->right->rotate_right();
		return this->rotate_left();
	}
	if (this->balance_factor() == -2) {
		if (this->left->balance_factor() > 0)
			this->left = this->left->rotate_left();
		return this->rotate_right();
	}
	return this;
}

avl_tree::avl_node* avl_tree::avl_node::find_min()
{
	return this->left ? this->left->find_min() : this;
}

avl_tree::avl_node* avl_tree::avl_node::remove_min()
{
	if (this->left == 0)
		return this->right;
	this->left = this->left->remove_min();
	return this->balance();
}

avl_tree::avl_node* avl_tree::avl_node::remove(avl_node*& del_node, bool& check)
{
	if (!this) return nullptr;
	if (del_node->_complex.value < this->_complex.value)
		this->left = this->left->remove(del_node, check);
	else if (del_node->_complex.value > this->_complex.value ||
		(del_node->_complex.value == this->_complex.value && !(del_node->_complex.data == this->_complex.data)))
		this->right = this->right->remove(del_node, check);
	else //  del_node->_complex == this->_complex
	{
		avl_node* q = this->left;
		avl_node* r = this->right;
		delete this;
		check = true;
		if (!r) return q;
		avl_node* min = r->find_min();
		min->right = r->remove_min();
		min->left = q;
		return min->balance();
	}
	return this->balance();
}

void avl_tree::avl_node::find_by_value(std::vector<complex>*& result, const double& value, const double& e) const
{
	if (this) {
		if (fabs(this->_complex.value - value) <= e) {
			result->push_back(this->_complex.data);
			this->left->find_by_value(result, value, e);
			this->right->find_by_value(result, value, e);
		}
		if (!(this->_complex.value <= value - e))
			this->left->find_by_value(result, value, e);
		if (!(this->_complex.value > value + e))
			this->right->find_by_value(result, value, e);
	}
}

avl_tree::avl_node::avl_node()
{
	left = right = nullptr;
	height = 1;
}

avl_tree::avl_node::avl_node(const node& _complex)
{
	this->_complex = _complex;
	left = right = nullptr;
	height = 1;
}

avl_tree::avl_node* avl_tree::avl_node::add(avl_node*& new_node)
{
	if (!this) return new avl_node(new_node->_complex);
	if (new_node->_complex.value == this->_complex.value) { 
		new_node->right = this->right;
		this->right = new_node;
	}
	else if (new_node->_complex.value < this->_complex.value)
		this->left = this->left->add(new_node);
	else
		this->right = this->right->add(new_node);
	return this->balance();
}

void avl_tree::avl_node::print() const
{
	if (this->left) {
		this->left->print();
	}
	std::cout << "Value - " << this->_complex.value << "\nz = ";
	_complex.data.print();
	std::cout << std::endl;
	if (this->right) {
		this->right->print();
	}
}

avl_tree::avl_tree()
{
	this->root = nullptr;
}

void avl_tree::print() const
{
	if (!this->root) std::cout << "Tree is empty";
	else root->print();
}

void avl_tree::add(const complex& data)
{
	avl_node* new_node = new avl_node(node(data));
	add(new_node);
}

void avl_tree::add(avl_tree::avl_node* new_node)
{
	if (!new_node) new_node = new avl_node();
	if (!this->root) {
		this->root = new_node;
	}
	else {
		this->root->add(new_node);
		delete new_node;
	}
}

void avl_tree::add_n_random(size_t n)
{
	for (size_t i = 0; i < n; ++i) {
		add();
	}
}

bool avl_tree::pop(const complex& data)
{
	avl_node* del_node = new avl_node(node(data));
	bool check = false;
	this->root->remove(del_node, check);
	return check;
}

std::vector<complex>* avl_tree::find_by_value(double value, double e) const
{
	std::vector<complex>* result = new std::vector<complex>;
	this->root->find_by_value(result, value, e);
	return result;
}
