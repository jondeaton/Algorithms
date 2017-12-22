/**
 * @file path-finder.cpp
 * @brief Presents the implementation of the graph searching class
 *
 */

#include <path-finder.hpp>

template <class T>
static inline void set_all(T* arr, T val, size_t count);

template <class WT>
struct CompareDistances {
public:
  explicit CompareDistances(const WT* dists) : distances(dists) {}
  bool operator()(size_t a, size_t b) {
    return distances[a] > distances[b];
  }
private:
  const WT* distances;
};

template <class T, class WT>
PathFinder<T, WT>::PathFinder() : data_size(0) {
  prevs = (size_t*) malloc(data_size * sizeof(size_t));
  distances = (WT*) malloc(data_size * sizeof(WT));
}

template <class T, class WT>
Path<size_t> PathFinder<T, WT>::find_path(Graph<T, WT> graph, size_t source, size_t sink) {

  setup_arrays(graph.size());
  distances[source] = 0;

  CompareDistances<WT> cmp(distances);
  priority_queue<size_t, std::vector<size_t>, CompareDistances<WT>> queue(cmp);
  queue.push(source);

  while (!queue.empty()) {
    size_t v = queue.top();
    if (v == sink) return make_path(source, sink);
    queue.pop();
    for (Edge<WT> edge : graph[v]) {
      int alt = distances[v] + edge.weight;
      if (alt < distances[edge.to]) {
        distances[edge.to] = alt;
        prevs[edge.to] = v;
        if (queue.contains(v)) queue.update_priority(v)
        else queue.push(edge.to);
      }
    }
  }
  Path<size_t> path;
  return path; // return empty path
}

template <class T, class WT, class ... Ts>
Path<size_t> PathFinder<T, WT>::make_path(size_t start, size_t end) {
    Path<size_t> path;
  for (size_t v = end; v != start; v = prevs[v]) path.nodes.push_back(v);
  path.nodes.push_back(start);
  std::reverse(path.nodes.begin(), path.nodes.end());
  return path;
}

template <class T, class WT>
void PathFinder<T, WT>::setup_arrays(size_t new_size)  {
  if (new_size <= data_size) return;
  data_size = new_size;
  prevs = (size_t*) realloc(prevs, data_size * sizeof(size_t));
  distances = (WT*) realloc(distances, data_size * sizeof(WT));
  set_all(distances, std::numeric_limits<WT>::max(), data_size);
}

template <class T, class WT>
PathFinder<T, WT>::~PathFinder() {
  free(prevs);
  free(distances);
}

/**
 * @brief  Sets all of elements of an array to a specified value
 *
 * @tparam T  The type of element stored in the array
 * @param arr  The array to set the values of
 * @param val  The value to set all elements in the array to
 * @param count  The number of elements to set in the array
 */
template <class T>
static inline void set_all(T arr[], T val, size_t count) {
  for (size_t i = 0; i < count; i++) arr[i] = val;
}