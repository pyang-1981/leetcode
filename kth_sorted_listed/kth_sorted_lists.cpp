#include <iostream>
#include <vector>
#include <type_traits>
#include <optional>

//! Get the kth elements in two sorted sequences.
/*! Given two sorted sequences, get the kth element
 *  from the combined elements
 */

//! Reduce the range of one of the 
template<typename RandIter1, typename RandIter2>
auto reduce(size_t k,
	    RandIter1 r1_begin, RandIter1 r1_end,   // [r1_begin, r1_end)
	    RandIter2 r2_begin, RandIter2 r2_end)   // [r2_begin, r2_end)
// c++ 14 allows auto inference of return type, the following line
// is not needed
//-> optional<typename std::remove_reference<decltype(*r1_begin)>::type>
{
	// Localized the typedefs for this function only.
	using ValType = typename std::remove_reference<decltype(*r1_begin)>::type;
	using ResType = std::optional<ValType>;
  using DiffType1 = typename RandIter1::difference_type;
  using DiffType2 = typename RandIter2::difference_type;

	// Not enough elements.
	if (r1_end - r1_begin + r2_end - r2_begin < k)
		return ResType(); // Return a null object.

	if (r1_begin == r1_end)
		return ResType(*(r2_begin + (k -1)));

	if (r2_begin == r2_end)
		return ResType(*(r1_begin + (k - 1)));

  DiffType1 mid1 = (r1_end - 1 - r1_begin) / 2;
  DiffType2 mid2 = (r2_end - 1 - r1_begin) / 2;

  if (mid1 + mid2 + 2 < k)  return reduce(k - mid1 - mid2 - 2, r1_begin + mid1 + 1, r1_end, r2_begin + mid2 + 1, r2_end);
  else {
    auto val1 = *(r1_begin + mid1);
    auto val2 = *(r2_begin + mid2);
    if(mid1 + mid2 + 2 ==k) {
      if (val1 > val2)   return ResType(val1);
      else return ResType(val2);
    }
    if (val1 > val2) return reduce(k, r1_begin, r1_begin + mid1, r2_begin, r2_end);
    else return reduce(k, r1_begin, r1_end, r2_begin, r2_begin + mid2);
  }
}



int main()
{
	std::vector<int> v1 = {1,2,3,4};
	std::vector<int> v2 = {2,3,4,5};

	std::optional<int> res = reduce(1, v1.begin(), v1.end(), v2.begin(), v2.end());
	std::cout << res.value() << std::endl;
	return 1;
}
