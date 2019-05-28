// Tasks: 1, 4, 5, 10, 17, 18
#include "pch.h"
#include "tree.h"
#include "binary_tree.h"

int main()
{
	try
	{
		//tree a;
		//for (size_t i = 0; i < 10; i++)
		//{
		//	a.add_node_by_random(generate_int(-100, 100));
		//}
		//std::cout << "Tree:\n";
		//a.print();

		//std::cout << "\nChilder: " << a.num_of_children() << "\nNodes: " << a.num_of_nodes() << "\nHeight: " << a.height() << std::endl;
		//std::cout << "\n--- Avarage ---\nChildren: " << a.average_num_of_children() << "\nNodes: " << a.average_num_of_nodes() << "\nHeight: " << a.average_height() << std::endl;

		//a.delete_node(2);

		//std::cout << "\nAfter delete Tree:\n";
		//a.print();

		binary_tree b;
		for (size_t i = 0; i < 12; i++)
		{
			b.add(generate_int(0, 100));
		}
		b.print();

		binary_h_tree c;
		c.rebuild(&b);

		c.print();
	}
	catch (const std::exception& ex)
	{
		std::cout << std::endl << ex.what() << std::endl;
	}

	return 0;
}