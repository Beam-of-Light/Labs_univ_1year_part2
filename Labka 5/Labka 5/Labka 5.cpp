// Tasks: 1, 2, 5, 11, 14, 18, 19
#include "pch.h"
#include "graph_struct.h"
#include "graph_matrix.h"

int main()
{
	try
	{
		graph_struct a(false, 6, 12);
		size_t weight;
		a.print_with_weight();
		std::cout << std::endl;
		auto result = a.reverse_delete(weight);

		result->print_with_weight();
		std::cout << std::endl;
		delete result;

		//graph_struct a(false, 6, 9);
		//a.print();
		//size_t weight;
		//graph_struct b = *a.spanning_tree_dfs(weight);
		//b.print();

		//graph_struct a(true, 6, 0);
		//a.add_edge(0, 1, 6);
		//a.add_edge(2, 1, 7);
		//a.add_edge(5, 4, 8);
		//a.add_edge(4, 2, 9);
		//a.add_edge(3, 4, 10);
		//a.print();
		//std::cout << std::endl;
		//graph_matrix b(&a);	
		//auto result = a.dijkstra();
		//for (const auto& t : result) {
		//	for (const auto& s : t) {
		//		if (s == UINT_MAX) {
		//			std::cout << "inf ";
		//		}
		//		else std::cout << s << ' ';
		//	}
		//	std::cout << std::endl;
		//}
		//a.topological_sort();
		//a.print();

		//std::cout << std::endl;
		//b.print();
		//std::cout << std::endl;
		//result = b.dijkstra();
		//for (const auto& t : result) {
		//	for (const auto& s : t) {
		//		if (s == UINT_MAX) {
		//			std::cout << "inf ";
		//		}
		//		else std::cout << s << ' ';
		//	}
		//	std::cout << std::endl;
		//}
		//b.topological_sort();
		//b.print();

		//graph_struct b(false, 6, 15);
		//b.print();
		//b.add_edge(3, 1, 4);
		//std::cout << std::endl << b.check_connectivity() << std::endl;
		//b.print();

		//graph_struct a(&b);
		//std::cout << std::endl;
		//a.print();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "\nSomething wrong" << std::endl;
	}
	return 0;
}