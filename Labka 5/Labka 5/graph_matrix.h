#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H
#include "pch.h"

using vertex = std::pair<int, std::vector<size_t>>;

class graph_matrix
{
private:
	void create_n_random_edges(size_t n);
	void dfs(const vertex& v, std::vector<bool>& visited) const;
	void dfs_by_weight(const vertex& v, std::vector<bool>& visited) const;
	
	// For spanning tree(forest)
	void spanning_tree_dfs(size_t& tree_weight, size_t from, std::vector<bool>& visited, graph_matrix*& result) const;
	void spanning_tree_dfs_by_weight(size_t& tree_weight, size_t from, std::vector<bool>& visited, graph_matrix*& result) const;

	// For dijkstra
	size_t min_distance(const std::vector<size_t>& distance, const std::vector<bool>& visited) const;

	// For topological_sort
	bool topological_sort(std::vector<char>& color, std::vector<std::pair<int, size_t>>& result, size_t& index);
	void rearrange(std::vector<std::pair<int, size_t>>& result);


	std::vector<vertex> matrix; /* vector(value, vector(weight)) */
	size_t vertices; /* number of vertices */
	bool is_oriented;

public:
	graph_matrix(bool is_oriented, size_t num_of_vertices, size_t num_of_edges);
	graph_matrix(class graph_struct* other_graph);
	void add_vertex(int value);
	void add_edge(size_t from, size_t to, size_t weight);
	
	void dfs() const;
	void dfs_by_weight() const;

	// Spanning tree(forest)
	graph_matrix* spanning_tree_dfs(size_t& tree_weight) const;
	graph_matrix* spanning_tree_dfs_by_weight(size_t& tree_weight) const;

	// Dijkstra
	std::vector<std::vector<size_t>> dijkstra() const;
	std::vector<size_t> dijkstra(size_t from) const;
	size_t dijkstra(size_t from, size_t to) const;

	void topological_sort();
	graph_matrix* reverse_delete(size_t& tree_weight) const;
	
	bool check_connectivity() const;
	void print() const;

	friend class graph_struct;
};

#endif /* GRAPH_MATRIX_H */