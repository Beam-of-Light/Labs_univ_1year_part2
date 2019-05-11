#ifndef STACK_H
#define STACK_H

class stack
{	// stack interface
public:
	virtual size_t size() const = 0;
	virtual bool is_empty() const = 0;

	virtual void push(const double &x, const double &y, const double &z) = 0;
	virtual void push(const my_point &this_point) = 0;
	virtual void push_rand() = 0;
	virtual void pop() = 0;
	virtual const my_point& peek() const = 0;
	virtual void print_and_del() = 0;
};





class stack_static : public stack
{	// stack based on a static array
public:
	static const int MAX = 10000;
	stack_static();

	size_t size() const override;
	bool is_empty() const override;

	void push(const double &x, const double &y, const double &z) override;
	void push(const my_point &this_point) override;
	void push_rand() override;
	void pop() override;
	const my_point& peek() const override;
	void print_and_del() override;

private:
	my_point array[MAX];
	size_t _size;

	bool is_free_space() const;
};





class stack_dynamic : public stack
{	// stack based on a dynamic array
private:
	std::vector<my_point> array;
	size_t _size;

public:
	stack_dynamic();

	size_t size() const override;
	bool is_empty() const override;

	void push(const double &x, const double &y, const double &z) override;
	void push(const my_point &this_point) override;
	void push_rand() override;
	void pop() override;
	const my_point& peek() const override;
	void print_and_del() override;
};





class stack_list : public stack
{	// stack based on a list
private:
	class list_point
	{
	public:
		my_point point;
		list_point *next;

		list_point();
		list_point(list_point* const next, const my_point &point);
	};

	list_point *list;
	size_t _size;

public:
	stack_list();
	~stack_list();

	size_t size() const override;
	bool is_empty() const override;

	void push(const double &x, const double &y, const double &z) override;
	void push(const my_point &this_point) override;
	void push_rand() override;
	void pop() override;
	const my_point& peek() const override;
	void print_and_del() override;
};

#endif //STACK_H