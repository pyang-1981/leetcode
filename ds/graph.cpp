#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

struct _link {
  int to = -1;
  int weight = -1;
  std::unique_ptr<_link> next;

  _link(int t, int w, std::unique_ptr<_link> l)
      : to(t), weight(w), next(std::move(l)) {}
};

struct _node {
  std::unique_ptr<_link> adj;
  int inDegree = 0;
  int outDegree = 0;
  int degree = 0;

  template <class GraphType>
  void _InsertLink(int to, int weight, GraphType &g) {
    for (auto l = adj.get(); l != nullptr; l = (l->next).get()) {
      if (l->to == to) {
        l->weight = weight;
        return;
      }
    }
    auto l = std::make_unique<_link>(to, weight, std::move(adj));
    adj = std::move(l);
    outDegree++;
    degree++;
    g._nodes[to].inDegree++;
  }
  template <class GraphType>
  void _DeleteLink(int to, GraphType &g) {
    for (_link *l = adj.get(), *p = nullptr; l != nullptr;
         p = l, l = (l->next).get()) {
      if (l->to = to) {
        if (l == adj.get()) {
          adj = std::move(adj->next);
        } else {
          p->next = std::move(l->next);
        }
        outDegree--;
        degree--;
        g._nodes[to].inDegree--;
      }
    }
  }
};

class Edge {
 public:
  Edge(int from, int to) : _from(from), _to(to) {}
  Edge(int from, int to, int weight) : _from(from), _to(to), _weight(weight) {}
  template <class GraphType>
  Edge(int from, int to, GraphType &g) : _from(from), _to(to) {
    if (from >= g.Size() || to >= g.Size()) {
      return;
    }
    for (auto l = g[from].adj.get(); l != nullptr; l = (l->next).get()) {
      if (l->to == to) {
        _weight = l->weight;
        _l = l;
        break;
      }
    }
  }
  operator bool() const { return _l != nullptr; }
  int Weight() const { return _weight; }
  int To() const { return _to; }
  int From() const { return _from; }

 private:
  int _from = -1;
  int _to = -1;
  int _weight = -1;
  _link *_l = nullptr;
};

using AdjMatrix = std::vector<std::vector<int>>;

AdjMatrix ConvertBinaryMatrix(const std::vector<_node> &nodes) {
  AdjMatrix m(nodes.size());
  for (int i = 0; i < m.size(); i++) {
    m[i] = std::vector<int>(m.size());
    for (auto l = nodes[i].adj.get(); l != nullptr; l = (l->next).get()) {
      m[i][l->to] = 1;
    }
  }
  return m;
}

AdjMatrix ConvertWeightMatrix(const std::vector<_node> &nodes) {
  AdjMatrix m(nodes.size());
  for (int i = 0; i < m.size(); i++) {
    m[i] = std::vector<int>(m.size());
    for (auto l = nodes[i].adj.get(); l != nullptr; l = (l->next).get()) {
      m[i][l->to] = l->weight;
    }
  }
  return m;
}

class Graph {
 public:
  friend class _node;
  Graph(int n) : _nodes(n) {}
  Edge InsertEdge(const Edge &e) {
    if (e.From() >= Size() || e.To() >= Size()) {
      return e;
    }
    _nodes[e.From()]._InsertLink(e.To(), e.Weight(), *this);
    _nodes[e.To()]._InsertLink(e.From(), e.Weight(), *this);
    return Edge(e.From(), e.To(), *this);
  }
  void DeleteEdge(const Edge &e) {
    if (e.From() >= Size() || e.To() >= Size()) {
      return;
    }
    _nodes[e.From()]._DeleteLink(e.To(), *this);
    _nodes[e.To()]._DeleteLink(e.From(), *this);
  }
  size_t Size() const { return _nodes.size(); }
  const _node &operator[](size_t index) const { return _nodes[index]; }
  AdjMatrix BinaryMatrix() const { return ConvertBinaryMatrix(_nodes); }
  AdjMatrix WeightMatrix() const { return ConvertWeightMatrix(_nodes); };

 private:
  std::vector<_node> _nodes;
};

class Digraph {
 public:
  friend class _node;
  Digraph(int n) : _nodes(n) {}
  Edge InsertEdge(const Edge &e) {
    if (e.From() >= Size() || e.To() >= Size()) {
      return e;
    }
    _nodes[e.From()]._InsertLink(e.To(), e.Weight(), *this);
    return Edge(e.From(), e.To(), *this);
  }
  void DeleteEdge(const Edge &e) {
    if (e.From() >= Size() || e.To() >= Size()) {
      return;
    }
    _nodes[e.From()]._DeleteLink(e.To(), *this);
  }
  size_t Size() const { return _nodes.size(); }
  const _node &operator[](size_t index) const { return _nodes[index]; }
  AdjMatrix BinaryMatrix() const { return ConvertBinaryMatrix(_nodes); }
  AdjMatrix WeightMatrix() const { return ConvertWeightMatrix(_nodes); };

 private:
  std::vector<_node> _nodes;
};

template <class GraphType>
struct GraphTraits {
  static bool IsDigraph() { return false; }
};

template <>
struct GraphTraits<Digraph> : public GraphTraits<Graph> {
  static bool IsDigraph() { return true; }
};

enum SearchAction { CONTINUE, BACKTRACE, TERMINATE };

template <class QType>
using GraphProcessor = std::function<SearchAction(int i, int weight, QType &q)>;

template <class GraphType>
void DFS(const GraphType &g, GraphProcessor<std::stack<int>> treeEdgeProcessor,
         GraphProcessor<std::stack<int>> backEdgeProcessor =
             GraphProcessor<std::stack<int>>(),
         GraphProcessor<std::stack<int>> crossEdgeProcessor =
             GraphProcessor<std::stack<int>>()) {
  std::vector<bool> visited(g.Size(), false);
  std::vector<int> weights(g.Size(), -1);
  std::vector<int> parent(g.Size(), -1);
  std::stack<int> s;
  auto dfs = [&](int i) {
    s.push(i);
    while (!s.empty()) {
      int t = s.top();
      s.pop();
      if (!visited[t]) {
        auto action = treeEdgeProcessor(t, weights[t], s);
        visited[t] = true;
        if (action == TERMINATE) {
          return;
        } else if (action == BACKTRACE) {
          continue;
        }
        for (auto l = g[t].adj.get(); l != nullptr; l = (l->next).get()) {
          if (!visited[l->to]) {
            parent[l->to] = t;
            weights[l->to] = l->weight;
            s.push(l->to);
          } else {
            if (parent[t] == l->to && !GraphTraits<GraphType>::IsDigraph()) {
              continue;  // this is a parent link
            }
            auto action = backEdgeProcessor(l->to, weights[l->to], s);
            if (action == TERMINATE) {
              return;
            } else if (action == BACKTRACE) {
              break;
            }
          }
        }
      }
    }
  };

  for (int i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      dfs(i);
    }
  }
}

int main() {
  Digraph g(2);
  g.InsertEdge(Edge(0, 1));
  g.InsertEdge(Edge(1, 0));

  int start = -1;
  std::vector<int> cycle;
  GraphProcessor<std::stack<int>> treeEdgeProcessor =
      [&cycle](int i, int weight, std::stack<int> &s) -> SearchAction {
    cycle.push_back(i);
    return CONTINUE;
  };
  GraphProcessor<std::stack<int>> backEdgeProcessor =
      [&start, &cycle](int i, int weight, std::stack<int> &s) -> SearchAction {
    cycle.push_back(i);
    start = i;
    return TERMINATE;
  };
  DFS(g, treeEdgeProcessor, backEdgeProcessor);

  bool discard = true;
  for (int i = 0; i < cycle.size(); i++) {
    if (cycle[i] == start) {
      discard = false;
    }
    if (!discard) {
      std::cout << cycle[i] << std::endl;
    }
  }
  return 0;
}
