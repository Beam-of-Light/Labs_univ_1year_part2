#include "binary_tree.h"

void binary_tree_node::print() const
{
	std::cout << this->value;
	size_t h = this->height();

	std::cout << (h > 2 ? "  " : "(");
	if (!this->left)
		std::cout << '.';
	else this->left->print();
	std::cout << ", ";

	if (!this->right)
		std::cout << '.';
	else this->right->print();
	std::cout << (h > 2 ? "  " : ")");
}

size_t binary_tree_node::height() const
{
	size_t num, max = 0;
	if (this->left){
		num = 1 + this->left->height();
		if (max < num) max = num;
	}
	if (this->right){
		num = 1 + this->right->height();
		if (max < num) max = num;
	}

	return size_t(max);
}

binary_tree_node::binary_tree_node(const int& value, binary_tree_node* left = nullptr, binary_tree_node* right = nullptr)
{
	this->value = value;
	this->left = left;
	this->right = right;
}

binary_tree_node::~binary_tree_node()
{
	if (this->left){
		delete this->left;
		this->left = nullptr;
	}
	if (this->right){
		delete this->right;
		this->right = nullptr;
	}
}





binary_tree::binary_tree()
{
	this->root = nullptr;
}


binary_tree::~binary_tree()
{
	delete this->root;
	this->root = nullptr;
}

void binary_tree::add(const int& value)
{
	binary_tree_node* new_node = new binary_tree_node(value);
	if (!this->root){
		this->root = new_node;
	}
	else {
		binary_tree_node* temp = this->root;
		while (temp){
			if (new_node->value > temp->value){
				if (temp->right){
					temp = temp->right;
				}
				else {
					temp->right = new_node;
					break;
				}
			}
			else if (new_node->value == temp->value){
				new_node->right = temp->right;
				temp->right = new_node;
				break;
			}
			else{
				if (temp->left){
					temp = temp->left;
				}
				else{
					temp->left = new_node;
					break;
				}
			}
		}
	}
}

void binary_tree::print() const
{
	if (this->root == nullptr) std::cout << "\nTree is empty\n";
	else root->print();
}



binary_h_tree_node* binary_h_tree::rebuild(const binary_tree_node* bin_tree, binary_h_tree_node* sym_left = nullptr, binary_h_tree_node* sym_right = nullptr)
{
	binary_h_tree_node* temp = new binary_h_tree_node(bin_tree->value, nullptr, nullptr);
	
	if ((temp->ltag = (bin_tree->left != nullptr)))
		temp->left = this->rebuild(bin_tree->left, sym_left, temp);
	else temp->left = sym_left;

	if ((temp->rtag = (bin_tree->right != nullptr)))
		temp->right = rebuild(bin_tree->right, temp, sym_right);
	else temp->right = sym_right;

	return temp;
}

binary_h_tree::binary_h_tree()
{
	this->root = nullptr;
}

binary_h_tree::~binary_h_tree()
{
	delete this->root;
	this->root = nullptr;
}

void binary_h_tree::rebuild(const binary_tree* bin_tree)
{
	if (!bin_tree || !bin_tree->root) return;
	else this->root = this->rebuild(bin_tree->root);
}

void binary_h_tree::print() const
{
	if (this->root == nullptr) std::cout << "\nTree is empty\n";
	else root->print();
}

void binary_h_tree_node::print() const
{
	std::cout << this->value;
	size_t h = this->height();

	std::cout << (h > 2 ? "  " : "(");
	if (!this->ltag)
		std::cout << '.';
	else this->left->print();
	std::cout << ", ";

	if (!this->rtag)
		std::cout << '.';
	else this->right->print();
	std::cout << (h > 2 ? "  " : ")");
}

size_t binary_h_tree_node::height() const
{
	size_t num, max = 0;
	if (this->ltag) {
		num = 1 + this->left->height();
		if (max < num) max = num;
	}
	if (this->rtag) {
		num = 1 + this->right->height();
		if (max < num) max = num;
	}

	return size_t(max);
}

binary_h_tree_node::binary_h_tree_node(const int& value, binary_h_tree_node* left = nullptr, binary_h_tree_node* right = nullptr)
{
	this->value = value;
	this->left = left;
	this->right = right;
	this->ltag = this->rtag = false;
}
