#include "graph_struct.h"
#include "graph_matrix.h"

graph_struct::list_graph_node::graph_node::graph_node(list_graph_node* ptr_vertex, size_t weight)
{
	this->weight = weight;
	this->ptr_vertex = ptr_vertex;
	this->next = nullptr;
}



graph_struct::list_graph_node::list_graph_node(int value, size_t index)
{
	this->index = index;
	this->value = value;
	first = last = nullptr;
}

//void graph_struct::list_graph_node::operator=(const list_graph_node& other)
//{
//	this->index = other.index;
//	this->value = other.value;
//	this->first = this->last = nullptr;
//
//	graph_node* cur = other.first;
//	while (cur) {
//		add_node(cur->ptr_vertex, cur->weight);
//		cur = cur->next;
//	}
//}

void graph_struct::list_graph_node::add_node(list_graph_node* ptr_vertex, size_t weight)
{
	graph_node* cur = this->first;
	while (cur) { /* check for existed edge */
		if (cur->ptr_vertex == ptr_vertex) {
			cur->weight = weight;
			return;
		}
		cur = cur->next;
	}
	graph_node* new_node = new graph_node(ptr_vertex, weight);
	if (this->first) {
		this->last->next = new_node;
	}
	else {
		this->first = new_node;
	}
	this->last = new_node;
}

//void graph_struct::list_graph_node::find_for_components()
//{
//	graph_node* cur = this->first;
//	while (cur) {
//		if (!cur->ptr_vertex->visited) {
//			cur->ptr_vertex->visited = true;
//			cur->ptr_vertex->find_for_components();
//		}
//		cur = cur->next;
//	}
//}

void graph_struct::del_edge(size_t from, size_t to)
{
	list_graph_node::graph_node* cur = this->neighbours[from]->first, * prev = cur;
	if (cur->ptr_vertex->index == to) {
		this->neighbours[from]->first = cur->next;
		if (!cur->next) this->neighbours[from]->last = cur->next;
		delete cur;
		return;
	}
	while (cur) {
		cur = cur->next;
		if (cur->ptr_vertex->index == to) { 
			if (!cur->next) this->neighbours[from]->last = prev;
			prev->next = cur->next;
			delete cur;
			return;
		}
		prev = prev->next;
	}
}

void graph_struct::create_n_random_edges(size_t n)
{
	std::vector<std::vector<bool>> matrix; /* check for edge */
	matrix.resize(vertices, std::vector<bool>(vertices, false));

	for (size_t i = 0, j, k; i < n; ++i) {
		do {
			j = generate_int(0, vertices - 1);
			k = generate_int(0, vertices - 1);
		} while (matrix[j][k]);

		matrix[j][k] = true;
		size_t temp = generate_int(1, 20);
		neighbours[j]->add_node(neighbours[k], temp);
		if (!is_oriented && j != k) {
			matrix[k][j] = true;
			neighbours[k]->add_node(neighbours[j], temp);
		}
	}
}

void graph_struct::find_connected_vertex(const list_graph_node::graph_node* cur, std::vector<bool>& visited) const
{
	while (cur) {
		if (!visited[cur->ptr_vertex->index]) {
			visited[cur->ptr_vertex->index] = true;
			find_connected_vertex(cur->ptr_vertex->first, visited);
		}
		cur = cur->next;
	}
}

void graph_struct::dfs(const list_graph_node::graph_node* cur, std::vector<bool>& visited) const
{
	while (cur) {
		if (!visited[cur->ptr_vertex->index]) {
			visited[cur->ptr_vertex->index] = true;
			dfs(cur->ptr_vertex->first, visited);
		}
		cur = cur->next;
	}
}

void graph_struct::dfs_by_weight(const list_graph_node::graph_node* cur, std::vector<bool>& visited) const
{
	std::vector<const list_graph_node::graph_node*> arr;
	while (cur) {
		arr.push_back(cur);
		cur = cur->next;
	}
	std::sort(arr.begin(), arr.end(),
		[](const list_graph_node::graph_node *& a, const list_graph_node::graph_node *& b) {
			return (a->weight < b->weight);
		});
	for (auto a : arr) {
		if (!visited[a->ptr_vertex->index]) {
			visited[a->ptr_vertex->index] = true;
			dfs_by_weight(a->ptr_vertex->first, visited);
		}
	}
}

void graph_struct::spanning_tree_dfs(size_t& tree_weight, const list_graph_node::graph_node* cur,
	size_t from, std::vector<bool>& visited, graph_struct*& result) const
{
	while (cur) {
		if (!visited[cur->ptr_vertex->index]) {
			visited[cur->ptr_vertex->index] = true;
			tree_weight += cur->weight;
			result->add_edge(from, cur->ptr_vertex->index, cur->weight);
			spanning_tree_dfs(tree_weight, cur->ptr_vertex->first, cur->ptr_vertex->index, visited, result);
		}
		cur = cur->next;
	}
}

void graph_struct::spanning_tree_dfs_by_weight(size_t& tree_weight, const list_graph_node::graph_node* cur,
	size_t from, std::vector<bool>& visited, graph_struct*& result) const
{
	std::vector<const list_graph_node::graph_node*> arr;
	while (cur) {
		arr.push_back(cur);
		cur = cur->next;
	}
	std::sort(arr.begin(), arr.end(),
		[](const list_graph_node::graph_node *& a, const list_graph_node::graph_node *& b) {
			return (a->weight < b->weight);
		});
	for (auto a : arr) {
		if (!visited[a->ptr_vertex->index]) {
			visited[a->ptr_vertex->index] = true;
			tree_weight += a->weight;
			result->add_edge(from, a->ptr_vertex->index, a->weight);
			spanning_tree_dfs(tree_weight, a->ptr_vertex->first, a->ptr_vertex->index, visited, result);
		}
	}
}

size_t graph_struct::min_distance(const std::vector<size_t>& distance, const std::vector<bool>& visited) const
{
	size_t min = UINT_MAX, min_index;
	for (size_t v = 0; v < vertices; ++v) {
		if (!visited[v] && distance[v] <= min) {
			min = distance[v], min_index = v;
		}
	}
	return min_index;
}

bool graph_struct::topological_sort(std::vector<char>& color, std::vector<list_graph_node*>& result, size_t& index)
{
	switch (color[index])
	{ /* Black = 'b', White = 'w', Grey = 'g' */
	case 'b':
		break;
	case 'g':
		return false;
	case 'w':
		color[index] = 'g';

		list_graph_node::graph_node* cur = neighbours[index]->first;
		while (cur) {
			if (!topological_sort(color, result, cur->ptr_vertex->index)) return false;
			cur = cur->next;
		}
		color[index] = 'b';
		result.push_back(neighbours[index]);
		break;
	}
	return true;
}

graph_struct::graph_struct(bool is_oriented, size_t num_of_vertices, size_t num_of_edges)
{
	if ((is_oriented && num_of_edges > (num_of_vertices * (num_of_vertices + 1)) / 2)
		|| (!is_oriented && num_of_edges > num_of_vertices * num_of_vertices))
		throw std::logic_error("Too many edges");

	this->is_oriented = is_oriented;
	neighbours.reserve(num_of_vertices);
	vertices = 0;
	for (size_t i = 0; i < num_of_vertices; ++i) {
		add_vertex(generate_int()); /* ++vertices */
	}
	create_n_random_edges(num_of_edges);
}

graph_struct::graph_struct(class graph_matrix* other_graph)
{
	this->vertices = other_graph->vertices;
	this->is_oriented = other_graph->is_oriented;
	this->neighbours.resize(vertices, new list_graph_node(0, 0));

	for (size_t i = 0; i < vertices; ++i) {
		neighbours[i]->value = other_graph->matrix[i].first;
		neighbours[i]->index = i;

		for (size_t j = 0; j < vertices; ++j) {
			if (other_graph->matrix[i].second[j]) {
				neighbours[i]->add_node(neighbours[j], other_graph->matrix[i].second[j]);
			}
		}
	}
}

graph_struct::~graph_struct()
{
	for (size_t i = 0; i < vertices; ++i) {
		list_graph_node::graph_node* cur = neighbours[i]->first, * temp = cur;
		while (cur) {
			cur = cur->next;
			delete temp;
			temp = cur;
		}
		neighbours[i]->first = neighbours[i]->last = nullptr;
	}
}

void graph_struct::add_vertex(int value)
{
	++vertices;
	neighbours.push_back(new list_graph_node(value, neighbours.size()));
}

void graph_struct::add_edge(size_t from, size_t to, size_t weight)
{
	neighbours[from]->add_node(neighbours[to], weight);
	if (!is_oriented && from != to) {
		neighbours[to]->add_node(neighbours[from], weight);
	}
}

void graph_struct::dfs() const
{
	if (vertices == 0) return;
	std::vector<bool> visited(vertices, false);
	visited[0] = true;
	dfs(neighbours[0]->first, visited);
}

void graph_struct::dfs_by_weight() const
{
	if (vertices == 0) return;
	std::vector<bool> visited(vertices, false);
	visited[0] = true;
	dfs_by_weight(neighbours[0]->first, visited);
}

graph_struct* graph_struct::spanning_tree_dfs(size_t& tree_weight) const
{
	if (vertices == 0 || is_oriented) return nullptr;
	std::vector<bool> visited(vertices, false);

	// Creating spanning tree(forest)
	graph_struct* result = new graph_struct(is_oriented, vertices, 0);
	for (size_t i = 0; i < vertices; ++i) {
		result->neighbours[i]->value = this->neighbours[i]->value;
	}

	tree_weight = 0;
	for (size_t i = 0; i < vertices; ++i) {
		if (!visited[i]) {
			visited[i] = true;
			spanning_tree_dfs(tree_weight, neighbours[i]->first, i, visited, result);
		}
	}
	return result;
}

graph_struct* graph_struct::spanning_tree_dfs_by_weight(size_t& tree_weight) const
{
	if (vertices == 0 || is_oriented) return nullptr;
	std::vector<bool> visited(vertices, false);

	// Creating spanning tree(forest)
	graph_struct* result = new graph_struct(is_oriented, vertices, 0);
	for (size_t i = 0; i < vertices; ++i) {
		result->neighbours[i]->value = this->neighbours[i]->value;
	}

	tree_weight = 0;
	for (size_t i = 0; i < vertices; ++i) {
		if (!visited[i]) {
			visited[i] = true;
			spanning_tree_dfs_by_weight(tree_weight, neighbours[i]->first, i, visited, result);
		}
	}
	return result;
}

std::vector<std::vector<size_t>> graph_struct::dijkstra() const
{
	std::vector<std::vector<size_t>> distance;
	for (size_t i = 0; i < vertices; ++i) {
		distance.push_back(dijkstra(i));
	}
	return distance;
}

std::vector<size_t> graph_struct::dijkstra(size_t from) const
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
		list_graph_node::graph_node* v = neighbours[u]->first;
		while (v) {
			if (!visited[v->ptr_vertex->index] && distance[u] + v->weight < distance[v->ptr_vertex->index]) {
				distance[v->ptr_vertex->index] = distance[u] + v->weight;
			}
			v = v->next;
		}
	}
	return distance;
}

size_t graph_struct::dijkstra(size_t from, size_t to) const
{
	return size_t(dijkstra(from)[to]);
}

void graph_struct::topological_sort()
{
	if (vertices == 0 || !is_oriented) return;

	std::vector<char> color(vertices, 'w');
	std::vector<list_graph_node*> result;

	for (size_t i = 0, size = 0; i < vertices; ++i)
	{ /* check for isolated vertices */
		if (color[i] == 'w') {
			if (!topological_sort(color, result, i)) return;
		}
	}
	std::reverse(result.begin(), result.end());
	neighbours = result;
	for (size_t i = 0; i < vertices; ++i) {
		neighbours[i]->index = i;
	}
}

graph_struct* graph_struct::reverse_delete(size_t& tree_weight) const
{
	if (vertices == 0 || is_oriented || !check_connectivity()) return nullptr;
	using edge = std::pair<std::pair<size_t, size_t>, size_t>; /* ((from, to), weight) */
	std::vector<edge> E;

	// Creating spanning tree(forest)
	graph_struct* result = new graph_struct(is_oriented, vertices, 0);
	for (size_t i = 0; i < vertices; ++i) {
		result->neighbours[i]->value = this->neighbours[i]->value;

		list_graph_node::graph_node* cur = this->neighbours[i]->first;
		while (cur) {
			if ((int)i - (int)cur->ptr_vertex->index > 0) {
				result->add_edge(i, cur->ptr_vertex->index, cur->weight);
				E.push_back(edge(std::pair<size_t, size_t>(i, cur->ptr_vertex->index), cur->weight));
			}
			cur = cur->next;
		}
	}
	std::sort(E.begin(), E.end(),
		[](const edge & a, const edge & b) {
			return (a.second > b.second);
		});

	tree_weight = 0;
	for (size_t i = 0, size = E.size(); i < size; ++i) {
		result->del_edge(E[i].first.first, E[i].first.second); /* del edge */
		result->del_edge(E[i].first.second, E[i].first.first);
		if (!result->check_connectivity()) {
			tree_weight += E[i].second;
			result->add_edge(E[i].first.first, E[i].first.second, E[i].second); /* undo del */
		}
	}
	return result;
}

bool graph_struct::check_connectivity() const
{	// if is oriented then check for super-connectivity
	if (vertices == 0) return true;
	std::vector<bool> visited(vertices, false);
	if (is_oriented) {
		for (size_t i = 0; i < vertices; ++i) {
			visited[i] = true;
			find_connected_vertex(neighbours[i]->first, visited);

			for (size_t i = 0; i < vertices; ++i) {
				if (!visited[i]) return false;
				visited[i] = false;
			}
		}
	}
	else {
		visited[0] = true;
		find_connected_vertex(neighbours[0]->first, visited);
		for (size_t i = 0; i < vertices; ++i) {
			if (!visited[i]) return false;
		}
	}
	return true;
}

void graph_struct::print() const
{
	for (size_t i = 0; i < vertices; ++i)
	{
		list_graph_node::graph_node* cur = neighbours[i]->first;
		std::cout << '(' << neighbours[i]->value << ',' << neighbours[i]->index << "):\t";
		while (cur) {
			std::cout << cur->ptr_vertex->index << ' ';
			cur = cur->next;
		}
		std::cout << std::endl;
	}
}

void graph_struct::print_with_weight() const
{
	for (size_t i = 0; i < vertices; ++i)
	{
		list_graph_node::graph_node* cur = neighbours[i]->first;
		std::cout << '(' << neighbours[i]->value << ',' << neighbours[i]->index << "):\t";
		while (cur) {
			std::cout << '(' << cur->ptr_vertex->index << ',' << cur->weight << ") ";
			cur = cur->next;
		}
		std::cout << std::endl;
	}
}

//size_t graph_struct::num_of_components()
//{
//	size_t num = 0;
//	for (size_t i = 0; i < vertices; ++i) {
//		if (!neighbours[i].visited) {
//			neighbours[i].find_for_components();
//			++num;
//		}
//	}
//	for (size_t i = 0; i < vertices; ++i)
//	{	/* clean */
//		neighbours[i].visited = false;
//	}
//	return size_t(num);
//}
