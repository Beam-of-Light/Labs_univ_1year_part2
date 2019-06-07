#ifndef GRAPH_STRUCT_H
#define GRAPH_STRUCT_H
#include "pch.h"

class graph_struct
{
private:
	class list_graph_node
	{
	private:
		class graph_node
		{
		private:
			list_graph_node* ptr_vertex;
			graph_node* next;
			size_t weight;

		public:
			graph_node(list_graph_node* ptr_vertex, size_t weight);

			friend class list_graph_node;
			friend class graph_struct;
			friend class graph_matrix;
		};

		int value;
		size_t index;
		graph_node* first, * last;

	public:
		list_graph_node(int value, size_t index);
		void add_node(list_graph_node* ptr_vertex, size_t weight);

		friend class graph_struct;
		friend class graph_matrix;
	};

	void del_edge(size_t from, size_t to);
	void create_n_random_edges(size_t n);
	void find_connected_vertex(const list_graph_node::graph_node* cur, std::vector<bool>& visited) const;
	void dfs(const list_graph_node::graph_node* cur, std::vector<bool>& visited) const;
	void dfs_by_weight(const list_graph_node::graph_node* cur, std::vector<bool>& visited) const;

	// For spanning tree(forest)
	void spanning_tree_dfs(size_t& tree_weight, const list_graph_node::graph_node* cur,
		size_t from, std::vector<bool>& visited, graph_struct*& result) const;
	void spanning_tree_dfs_by_weight(size_t& tree_weight, const list_graph_node::graph_node* cur, 
		size_t from, std::vector<bool>& visited, graph_struct*& result) const;

	// For dijkstra
	size_t min_distance(const std::vector<size_t>& distance, const std::vector<bool>& visited) const;

	// For topological_sort
	bool topological_sort(std::vector<char>& color, std::vector<list_graph_node*>& result, size_t& index);

	bool is_oriented;
	size_t vertices; /* number of vertices */
	std::vector<list_graph_node*> neighbours;

public:
	graph_struct(bool is_oriented, size_t num_of_vertices, size_t num_of_edges);
	graph_struct(class graph_matrix* other_graph);
	~graph_struct();
	void add_vertex(int value);
	void add_edge(size_t from, size_t to, size_t weight);

	void dfs() const;
	void dfs_by_weight() const;

	// Spanning tree(forest)
	graph_struct* spanning_tree_dfs(size_t& tree_weight) const;
	graph_struct* spanning_tree_dfs_by_weight(size_t& tree_weight) const;

	// Dijkstra
	std::vector<std::vector<size_t>> dijkstra() const;
	std::vector<size_t> dijkstra(size_t from) const;
	size_t dijkstra(size_t from, size_t to) const;

	void topological_sort();
	graph_struct* reverse_delete(size_t& tree_weight) const;

	bool check_connectivity() const;
	void print() const;
	void print_with_weight() const;
	//int min_distance(const size_t& index1, const size_t& index2)
	//{
	//	if (index1 == index2) return 0;
	//
	//	queue<list_graph_node*> q;
	//	q.push(&neighbours[index1]);
	//	neighbours[index1].visited = true;
	//
	//	std::vector<size_t> result;
	//	size_t i = 0, j = 0;
	//	while (!q.empty())
	//	{
	//		graph_node* cur = q.front()->first;
	//		q.pop();
	//		while (cur != nullptr)
	//		{
	//			if (cur->ptr_vertex == &neighbours[index2])
	//			{
	//				for (size_t i = 0; i < VERTICES; ++i)
	//				{	/* clean */
	//					neighbours[i].visited = false;
	//				}
	//				return size_t(result.size() + 1);
	//			}
	//			if (cur->ptr_vertex->visited == false)
	//			{
	//				q.push(cur->ptr_vertex);
	//				cur->ptr_vertex->visited = true;
	//				++j;
	//			}
	//			cur = cur->next;
	//		}
	//
	//		if (i != 0)
	//		{
	//			--i;
	//		}
	//		else {
	//			i = j;
	//			result.push_back(j);
	//			j = 0;
	//		}
	//	}
	//	for (size_t i = 0; i < VERTICES; ++i)
	//	{	/* clean */
	//		neighbours[i].visited = false;
	//	}
	//	return -1; // way doesn't exist
	//}

	friend class graph_matrix;
};


#endif /* GRAPH_STRUCT_H */