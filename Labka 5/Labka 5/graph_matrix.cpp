#include "graph_matrix.h"
#include "graph_struct.h"


void graph_matrix::create_n_random_edges(size_t n)
{
	for (size_t i = 0, j, k; i < n; ++i) {
		do {
			j = generate_int(0, vertices - 1);
			k = generate_int(0, vertices - 1);
		} while (matrix[j].second[k]);

		size_t temp = generate_int(1, 20);
		matrix[j].second[k] = temp;
		if (!is_oriented && j != k) {
			matrix[k].second[j] = temp;
		}
	}
}

void graph_matrix::dfs(const vertex& v, std::vector<bool>& visited) const
{
	for (size_t i = 0; i < vertices; ++i) {
		if (v.second[i] && !visited[i]) {
			visited[i] = true;
			dfs(this->matrix[i], visited);
		}
	}
}

void graph_matrix::dfs_by_weight(const vertex& v, std::vector<bool>& visited) const
{
	// index(index to, weight)
	std::vector<std::pair<size_t, size_t>> index(vertices, std::pair<size_t, size_t>(0, 0));
	for (size_t i = 0; i < vertices; ++i){
		index[i].first = i;
		index[i].second = v.second[i];
	}
	std::sort(index.begin(), index.end(),
		[](const std::pair<size_t, size_t> & a, const std::pair<size_t, size_t> & b) {
			return a.second < b.second;
		});

	for (size_t i = 0; i < vertices; ++i) {
		if (index[i].second && !visited[index[i].first]) {
			visited[index[i].first] = true;
			dfs_by_weight(this->matrix[index[i].first], visited);
		}
	}
}

void graph_matrix::spanning_tree_dfs(size_t& tree_weight, size_t from,
	std::vector<bool>& visited, graph_matrix*& result) const
{
	for (size_t i = 0; i < vertices; ++i) {
		if (matrix[from].second[i] && !visited[i]) {
			visited[i] = true;
			tree_weight += matrix[from].second[i];
			result->add_edge(from, i, matrix[from].second[i]);
			spanning_tree_dfs(tree_weight, i, visited, result);
		}
	}
}

void graph_matrix::spanning_tree_dfs_by_weight(size_t& tree_weight, size_t from, 
	std::vector<bool>& visited, graph_matrix*& result) const
{
	// index(index to, weight)
	std::vector<std::pair<size_t, size_t>> index(vertices, std::pair<size_t, size_t>(0, 0));
	for (size_t i = 0; i < vertices; ++i) {
		index[i].first = i;
		index[i].second = matrix[from].second[i];
	}
	std::sort(index.begin(), index.end(),
		[](const std::pair<size_t, size_t> & a, const std::pair<size_t, size_t> & b) {
			return a.second < b.second;
		});

	for (size_t i = 0; i < vertices; ++i) {
		if (index[i].second && !visited[index[i].first]) {
			visited[index[i].first] = true;
			tree_weight += index[i].second;
			result->add_edge(from, i, matrix[from].second[i]);
			spanning_tree_dfs_by_weight(tree_weight, index[i].first, visited, result);
		}
	}
}

size_t graph_matrix::min_distance(const std::vector<size_t>& distance, const std::vector<bool>& visited) const
{
	size_t min = UINT_MAX, min_index;
	for (size_t v = 0; v < vertices; ++v) {
		if (!visited[v] && distance[v] <= min) {
			min = distance[v], min_index = v;
		}
	}
	return min_index;
}

bool graph_matrix::topological_sort(std::vector<char>& color, std::vector<std::pair<int, size_t>>& result, size_t& index)
{
	switch (color[index])
	{ /* Black = 'b', White = 'w', Grey = 'g' */
	case 'b':
		break;
	case 'g':
		return false;
	case 'w':
		color[index] = 'g';
		for (size_t i = 0; i < vertices; ++i) {
			if (matrix[index].second[i]) {
				if (!topological_sort(color, result, i)) return false;
			}
		}
		color[index] = 'b';
		result.push_back(std::pair<int, size_t>(matrix[index].first, index));
		break;
	}
	return true;
}

void graph_matrix::rearrange(std::vector<std::pair<int, size_t>>& result)
{
	auto temp = matrix;
	for (size_t i = 0; i < vertices; ++i) {
		matrix[i].first = result[i].first;

		for (size_t j = 0; j < vertices; ++j) {
			matrix[i].second[j] = temp[result[i].second].second[result[j].second];
		}
	}
}

graph_matrix::graph_matrix(bool is_oriented, size_t num_of_vertices, size_t num_of_edges)
{
	if ((is_oriented && num_of_edges > (num_of_vertices * (num_of_vertices + 1)) / 2)
		|| (!is_oriented && num_of_edges > num_of_vertices * num_of_vertices))
		throw std::logic_error("Too many edges");

	this->is_oriented = is_oriented;
	vertices = num_of_vertices;
	matrix.reserve(num_of_vertices);
	
	for (size_t i = 0; i < vertices; ++i) {
		matrix.push_back(vertex(generate_int(), std::vector<size_t>(num_of_vertices, 0)));
	}
	create_n_random_edges(num_of_edges);
}

graph_matrix::graph_matrix(graph_struct* other_graph)
{
	this->vertices = other_graph->vertices;
	this->is_oriented = other_graph->is_oriented;
	this->matrix.resize(vertices, vertex(0, std::vector<size_t>(vertices, 0)));

	for (size_t i = 0; i < vertices; ++i) {
		matrix[i].first = other_graph->neighbours[i]->value;
		graph_struct::list_graph_node::graph_node* cur = other_graph->neighbours[i]->first;
		while (cur) {
			matrix[i].second[cur->ptr_vertex->index] = cur->weight;
			cur = cur->next;
		}
	}
}

void graph_matrix::add_vertex(int value)
{
	for (size_t i = 0; i < vertices; ++i){
		matrix[i].second.push_back(0);
	}
	++vertices;
	matrix.push_back(vertex(value, std::vector<size_t>(vertices, 0)));
}

void graph_matrix::add_edge(size_t from, size_t to, size_t weight)
{
	matrix[from].second[to] = weight;
	if (!is_oriented && to != from) {
		matrix[to].second[from] = weight;
	}
}

void graph_matrix::dfs() const
{
	if (vertices == 0) return;
	std::vector<bool> visited(vertices, false);
	visited[0] = true;
	dfs(this->matrix[0], visited);
}

void graph_matrix::dfs_by_weight() const
{
	if (vertices == 0) return;
	std::vector<bool> visited(vertices, false);
	visited[0] = true;
	dfs_by_weight(this->matrix[0], visited);
}

graph_matrix* graph_matrix::spanning_tree_dfs(size_t& tree_weight) const
{
	if (vertices == 0 || is_oriented) return nullptr;
	std::vector<bool> visited(vertices, false);

	// Creating spanning tree(forest)
	graph_matrix* result = new graph_matrix(is_oriented, vertices, 0);
	for (size_t i = 0; i < vertices; ++i) {
		result->matrix[i].first = this->matrix[i].first;
	}

	tree_weight = 0;
	for (size_t i = 0; i < vertices; ++i) {
		if (!visited[i]) {
			visited[i] = true;
			spanning_tree_dfs(tree_weight, i, visited, result);
		}
	}
	return result;
}

graph_matrix* graph_matrix::spanning_tree_dfs_by_weight(size_t& tree_weight) const
{
	if (vertices == 0 || is_oriented) return nullptr;
	std::vector<bool> visited(vertices, false);

	// Creating spanning tree(forest)
	graph_matrix * result = new graph_matrix(is_oriented, vertices, 0);
	for (size_t i = 0; i < vertices; ++i) {
		result->matrix[i].first = this->matrix[i].first;
	}

	tree_weight = 0;
	for (size_t i = 0; i < vertices; ++i) {
		if (!visited[i]) {
			visited[i] = true;
			spanning_tree_dfs_by_weight(tree_weight, i, visited, result);
		}
	}
	return result;
}

std::vector<std::vector<size_t>> graph_matrix::dijkstra() const
{
	std::vector<std::vector<size_t>> distance;
	for (size_t i = 0; i < vertices; ++i) {
		distance.push_back(dijkstra(i));
	}
	return distance;
}

std::vector<size_t> graph_matrix::dijkstra(size_t from) const
{
	std::vector<size_t> distance(vertices, UINT_MAX);
	distance[from] = 0;
	std::vector<bool> visited(vertices, false);

	for (size_t count = 0; count < vertices - 1; ++count) {
		size_t u = min_distance(distance, visited);
		visited[u] = true;
		
		// Check for existed path
		if (distance[u] == UINT_MAX) break;

		// Update distance u -> v
		for (size_t v = 0; v < vertices; ++v) {
			if (!visited[v] && matrix[u].second[v] && distance[u] + matrix[u].second[v] < distance[v]) {
				distance[v] = distance[u] + matrix[u].second[v];
			}
		}
	}
	return distance;
}

size_t graph_matrix::dijkstra(size_t from, size_t to) const
{
	return size_t(dijkstra(from)[to]);
}

void graph_matrix::topological_sort()
{
	if (vertices == 0 || !is_oriented) return;

	std::vector<char> color(vertices, 'w');
	std::vector<std::pair<int, size_t>> result;

	for (size_t i = 0; i < vertices; ++i)
	{ /* check for isolated vertices */
		if (color[i] == 'w') {
			if (!topological_sort(color, result, i)) return;
		}
	}
	std::reverse(result.begin(), result.end());
	rearrange(result);
}

graph_matrix* graph_matrix::reverse_delete(size_t& tree_weight) const
{
	if (vertices == 0 || is_oriented || !check_connectivity()) return nullptr;

	// Creating spanning tree(forest)
	graph_matrix * result = new graph_matrix(is_oriented, vertices, 0);
	for (size_t i = 0; i < vertices; ++i) {
		result->matrix[i].first = this->matrix[i].first;
		result->matrix[i].second = this->matrix[i].second;
	}
	using edge = std::pair<std::pair<size_t, size_t>, size_t>; /* ((from, to), weight) */
	std::vector<edge> E;
	
	for (size_t i = 0; i < vertices; ++i)
		for (size_t j = i + 1; j < vertices; ++j)
			if (matrix[i].second[j])
				E.push_back(edge(std::pair<size_t, size_t>(i, j), matrix[i].second[j]));

	std::sort(E.begin(), E.end(),
		[](const edge& a, const edge& b) {
			return (a.second > b.second);
		});

	tree_weight = 0;
	for (size_t i = 0, size = E.size(); i < size; ++i) {
		result->matrix[E[i].first.first].second[E[i].first.second] = 0; /* del edge */
		result->matrix[E[i].first.second].second[E[i].first.first] = 0;
		if (!result->check_connectivity()) {
			tree_weight += E[i].second;
			result->matrix[E[i].first.first].second[E[i].first.second] = E[i].second; /* undo del */
			result->matrix[E[i].first.second].second[E[i].first.first] = E[i].second;
		}
	}
	return result;
}

bool graph_matrix::check_connectivity() const
{	// if is oriented then check for super-connectivity
	if (vertices == 0) return true;
	std::vector<bool> visited(vertices, false);
	if (is_oriented) {
		for (size_t i = 0; i < vertices; ++i){
			visited[i] = true;
			dfs(matrix[i], visited);
			
			for (size_t i = 0; i < vertices; ++i) {
				if (!visited[i]) return false;
				visited[i] = false;
			}
		}
	} else {
		visited[0] = true;
		dfs(matrix[0], visited);
		for (size_t i = 0; i < vertices; ++i){
			if (!visited[i]) return false;
		}
	}
	return true;
}

void graph_matrix::print() const
{
	for (size_t i = 0; i < vertices; ++i) {
		std::cout << '(' << matrix[i].first << ',' << i << "):\t";
		for (size_t j = 0; j < vertices; j++) {
			std::cout << matrix[i].second[j] << ' ';
		}
		std::cout << std::endl;
	}
}
