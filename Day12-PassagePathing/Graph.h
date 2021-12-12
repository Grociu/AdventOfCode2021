#include <vector>
#include <string>


// struct Edge
template <typename T>
struct Edge {
	T source;
	T destination;
};

template <typename T>
bool operator==(const Edge<T>& a, const Edge<T>& b) { return a.source == b.source && a.destination == b.destination; }

template <typename T>
bool same_source(const Edge<T>& a, const Edge<T>& b) { return a.source == b.source; }

template <typename T>
bool same_destination(const Edge<T>& a, const Edge<T>& b) { return  a.destination == b.destination; }


// class Graph
template <typename T>
class Graph{
public:
	Graph(const std::vector<Edge<T>>& edges);
	std::vector<T> get_adjecent(const T& vertex);
	int num_vertexes() { return adjecency_list.size(); }
private:
	int get_adj_lst_index(const T src);
	std::vector<std::vector<T>> adjecency_list;
};

// universal template member functions must be defined in the header file
template <typename T>
Graph<T>::Graph(const std::vector<Edge<T>>& edges) {
	for (auto& e : edges) {
		int index = get_adj_lst_index(e.source); // this resizes the vector if needed, taking care of out_of_range errors;
		adjecency_list[index].push_back(e.destination);
		// for undirected graph
		index = get_adj_lst_index(e.destination);
		adjecency_list[index].push_back(e.source);
	}
}

template <typename T>
std::vector<T> Graph<T>::get_adjecent(const T& vertex) {
	std::vector<T> adjacent = adjecency_list[get_adj_lst_index(vertex)];
	adjacent.erase(adjacent.begin()); // erase the current vertex, that is the identifier of the adjecency list, leaving only adjacent vertexes
	//DEBUG
	/*
	std::cout << "Adjacent to (" << vertex << "): ";
	for (auto& s : adjacent) std::cout << s << " , ";
	std::cout << std::endl;
	*/
	return adjacent;
}

template <typename T>
int Graph<T>::get_adj_lst_index(const T src) {
	// find existing
	for (int i = 0; i < adjecency_list.size(); i++) {
		if (adjecency_list[i][0] == src) return i;
	}
	// not found
	std::vector<T> a;
	a.push_back(src);
	adjecency_list.push_back(a);
	int n = adjecency_list.size() - 1;
	return n;
}
