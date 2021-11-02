#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Note that Heap is by default a max heap.
template <class T, class Comp = std::less<T>>
class Heap {
 public:
  using iterator = typename vector<T>::iterator;
  using size_type = typename vector<T>::size_type;

  Heap() { make_heap(_heap.begin(), _heap.end(), Comp()); }
  Heap(const vector<T> &vec) : _heap(vec) {
    make_heap(_heap.begin(), _heap.end(), Comp());
  }
  Heap(typename vector<T>::iterator first, typename vector<T>::iterator last)
      : _heap(first, last) {
    make_heap(_heap.begin(), _heap.end(), Comp());
  }

  T Pop() {
    pop_heap(_heap.begin(), _heap.end(), Comp());
    T t = _heap.back();
    _heap.pop_back();
    return t;
  }
  T &Top() { return _heap[0]; }
  void Push(const T &t) {
    _heap.push_back(t);
    push_heap(_heap.begin(), _heap.end(), Comp());
  }

  bool Empty() { return _heap.empty(); }
  size_type Size() { return _heap.size(); }

  iterator begin() { return _heap.begin(); }
  iterator end() { return _heap.end(); }

 private:
  vector<T> _heap;
};

int main() {
  Heap<int> h({2, 1, 4, 3});

  for (auto it = h.begin(); it != h.end(); ++it) {
    cout << *it << "," << endl;
  }
}
