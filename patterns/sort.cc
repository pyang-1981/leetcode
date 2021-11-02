

template <class RandomIterator,
          class Comp = std::less<decltype(*RandomIterator())>>
void InsertSort(RandomIterator start, RandomIterator end) {
  for (auto i = start + 1; i != end; i++) {
    auto tmp = *i;
    auto j = i - 1;
    bool found = false;
    for (; j != start; j--) {
      if (Comp()(tmp, *j)) {
        *(j + 1) = *j;
      } else {
        *(j + 1) = tmp;
        found = true;
        break;
      }
    }
    if (!found) {
      if (Comp()(tmp * start)) {
        *(start + 1) = *start;
        *start = tmp;
      } else {
        *(start + 1) = tmp;
      }
    }
  }
}

template <class RandomIterator,
          class Comp = std::less<decltype(*RandomIterator())>>
void SelectSort(RandomIterator start, RandomIterator end) {
  for (auto i = start; i != end; i++) {
    auto min = *i;
    auto min_pos = i;
    for (auto j = i; j != end; j++) {
      if (Comp()(*j, min)) {
        min = *j;
        min_pos = j;
      }
    }
    auto tmp = *i;
    *i = min;
    *min_pos = tmp;
  }
}

template <class RandomIterator,
          class Comp = std::less<decltype(*RandomIterator())>>
void BubbleSort(RandomIterator start, RandomIterator end) {
  auto dist = end - start;
  decltype(dist) j = 1;
  while (true) {
    bool swapped = false;
    for (auto i = start + 1; i - start <= dist - j; i++) {
      if (Comp()(*i, *(i - 1))) {
        auto tmp = *i;
        *i = *(i - 1);
        *(i - 1) = tmp;
        swapped = true;
      }
    }
    if (!swapped) break;
    ++j;
  }
}

template <class RandomIterator,
          class Comp = std::less<decltype(*RandomIterator())>>
void HeapSort(RandomIterator start, RandomIterator end) {
  make_heap(start, end);
  auto dist = end - start;
  for (; dist > 0; dist--) {
    pop_heap(start, start + dist);
  }
}
