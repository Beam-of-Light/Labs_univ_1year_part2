// Tasks: 1, 4, 5 
#include "pch.h"
#include "tree.h"

int main()
{
	try
	{
		tree a;
		for (size_t i = 0; i < 10; i++)
		{
			a.add_node_by_random(generate_int(0, 100));
		}

		std::cout << "Childer: " << a.num_of_children() << "\nNodes: " << a.num_of_nodes() << "\nHeight: " << a.height() << std::endl;
		std::cout << "\n--- Avarage ---\nChildren: " << a.avarage_num_of_children() << "\nNodes: " << a.avarage_num_of_nodes() << "\nHeight: " << a.avarage_height() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << std::endl << ex.what() << std::endl;
	}

	return 0;
}