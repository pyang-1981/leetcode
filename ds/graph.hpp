#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
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
using DFSProcessor = GraphProcessor<std::stack<int>>;
using BFSProcessor = GraphProcessor<std::queue<int>>;

template <class PriorityType>
using PrioritizedIndex = std::tuple<PriorityType, int>;
namespace std {
template <class PriorityType>
struct less<PrioritizedIndex<PriorityType>> {
  bool operator(const PrioritizedIndex &a, const PrioritizedIndex &b) const {
    return std::get<0>(a) < std::get<0>(b);
  }
};
}  // namespace std
template <class PriorityType>
using PFSProcessor = GraphProcessor<std::set<PrioritizedIndex<PriorityType>>>;
template <class PriorityType>
using PriorityProcessor = std::function<double(
    int add, int weight, PriorityType pri_add, PriorityType pri)>;

template <class GraphType>
std::vector<int> DFS(const GraphType &g, DFSProcessor treeEdgeProcessor,
                     DFSProcessor backEdgeProcessor = DFSProcessor(),
                     DFSProcessor crossEdgeProcessor = DFSProcessor()) {
  std::vector<int> pre(g.Size(), 0);
  std::vector<int> post(g.Size(), );
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
            if (first_unvisited == -1) {
              first_unvisited = l->to;
            }
          } else {
            if (parent[t] == l->to && !GraphTraits<GraphType>::IsDigraph()) {
              continue;  // this is a parent link
            }
            if (backEdgeProcessor) {
              auto action = backEdgeProcessor(l->to, l->weight, s);
              if (action == TERMINATE) {
                return;
              }
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

  return parent;
}

template <class GraphType>
vector<int> BFS(const GraphType &g, BFSProcessor treeEdgeProcessor,
                BFSProcessor backEdgeProcessor = BFSProcessor(),
                BFSProcessor crossEdgeProcessor = BFSProcessor()) {
  std::vector<bool> visited(g.Size(), false);
  std::vector<int> weights(g.Size(), -1);
  std::vector<int> parent(g.Size(), -1);
  std::queue<int> q;

  auto bfs = [&](int i) {
    q.push(i);
    while (!q.empty()) {
      int t = q.front();
      q.pop();
      auto action = treeEdgeProcessor(t, weights[t], q);
      visited[t] = true;
      if (action == TERMINATE) {
        return;
      } else if (action == BACKTRACE) {
        continue;
      }
      for (auto l = g[t].adj.get(); l != nullptr; l = (l->next).get()) {
        if (!visited[l->to]) {
          q.push(l->to);
          weights[l->to] = l->weight;
          parent[l->to] = t;
        } else {
          if (parent[t] == l->to && !GraphTraits<GraphType>::IsDigraph()) {
            continue;
          }
          auto action = backEdgeProcessor(l->to, l->weight, q);
          if (action == TERMINATE) {
            return;
          }
        }
      }
    }
  };

  for (int i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      bfs(i);
    }
  }

  return parent;
}

template <class GraphType, class PriorityType>
vector<int> PFS(const GraphType &g, int start, PriorityType priorities[],
                PriorityProcessor<PriorityType> priProcessor,
                PFSProcessor<PriorityType> treeEdgeProcessor) {
  std::vector<bool> visited(g.Size(), false);
  std::vector<int> weights(g.Size(), -1);
  std::vector<int> parent(g.Size(), -1);
  std::set<PrioritizedIndex<PriorityType>> s;

  s.insert(std::make_tuple(priorities[i], i));
  while (!s.empty()) {
    double p;
    int t;
    std::tie(p, t) = *(s.begin());
    s.erase(s.begin());
    auto action = treeEdgeProcessor(t, weights[t], s);
    visited[t] = true;
    if (action == TERMINATE) {
      return;
    } else if (action == BACKTRACE) {
      continue;
    }
    for (auto l = g[t].adj.get(); l != nullptr; l = (l->next).get()) {
      if (!visited[l->to]) {
        weights[l->to] = l->weight;
        parent[l->to] = t;
        PriorityType pri =
            priProcessor(t, l->weight, priorities[t], priorities[l->to]);
        priorities[l->to] = pri;
        s.insert(std::make_tuple(pri, l->to));
      } else {
        if (parent[t] == l->to && !GraphTraits<GraphType>::IsDigraph()) {
          continue;
        }
        PriorityType pri =
            priProcessor(t, l->weight, priorities[t], priorities[l->to]);
        if (pri < priorities[l->to]) {
          weights[l->to] = l->weight;
          parent[l->to] = t;
          s.erase(std::make_tuple(priorities[l->to], l->to));
          s.insert(std::make_tuple(pri, l->to));
          priorities[l->to] = pri;
        }
      }
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
