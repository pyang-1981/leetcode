#include <vector>

using namespace std;

template <class CombinationType>
class _CombIter {
 public:
  template<class CombType>
  friend bool operator==(const _CombIter<CombType> &i1,
                         const _CombIter<CombType> &i2);
  template<class CombType>
  friend bool operator!=(const _CombIter<CombType> &i1,
                         const _CombIter<CombType> &i2);
  _CombIter(const CombinationType &comb, bool end) : _comb(comb), _end(end) {}
  const vector<int> &operator*() const { return _comb.Current(); }
  const vector<int> *operator->() const { return &_comb.Current(); }
  const _CombIter &operator++() {
    if (!_comb.Next()) _end = true;
    return *this;
  }

 private:
  const CombinationType &_comb;
  bool _end;
};

template <class CombinationType>
bool operator==(const _CombIter<CombinationType> &i1,
                const _CombIter<CombinationType> &i2) {
  return i1._end == i2._end;
}

template <class CombinationType>
bool operator!=(const _CombIter<CombinationType> &i1,
                const _CombIter<CombinationType> &i2) {
  return i1._end != i2._end;
}

class Combination {
 public:
  using const_iterator = _CombIter<Combination>;

  Combination(int n, int k) : _n(n), _k(k) {
    if (k > n) throw;
    for (int i = 1; i <= k; i++) {
      _cur.push_back(i);
    }
  }

  const vector<int> &Current() const { return _cur; }

  bool Next() const {
    bool res = false;
    int i = _k - 1;
    for (int j = 0; i >= 0; i--, j++) {
      if (_cur[i] < _n - j) {
        _cur[i]++;
        res = true;
        break;
      }
    }
    if (res) {
      for (int j = i + 1; j <= _k - 1; j++) {
        _cur[j] = _cur[j - 1] + 1;
      }
    }

    return res;
  }

  const_iterator cbegin() const { return const_iterator(*this, false); }

  const_iterator cend() const { return const_iterator(*this, true); }

 private:
  int _n;
  int _k;
  mutable vector<int> _cur;
};




