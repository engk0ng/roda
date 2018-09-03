#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <algorithm>
#include <array>
#include <sstream>
#include <type_traits>
#include <vector>

#include <roda/FilterIterator.hpp>
#include <roda/RangeIterator.hpp>
#include <roda/algorithm.hpp>

TEST_CASE("RangeIterator and FilterIterator")
{
  auto arr = std::array<int, 20>{{15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}};
  auto rangeit = roda::RangeIterator{arr};
  auto filterit =
   roda::FilterIterator(rangeit, [](const auto& a) { return a > 20; });

  auto cout = std::ostringstream{};
  roda::for_each(filterit, [&cout](auto val) { cout << val << ' '; });

  REQUIRE(cout.str() == "21 22 23 24 25 ");

  using RangeItType = std::decay_t<decltype(rangeit)>;

  REQUIRE((std::is_same_v<std::random_access_iterator_tag,
                          typename RangeItType::IteratorCategory>));
  REQUIRE((std::is_same_v<int, typename RangeItType::ValueType>));
  REQUIRE((std::is_same_v<ptrdiff_t, typename RangeItType::DifferenceType>));
  REQUIRE((std::is_same_v<int*, typename RangeItType::Pointer>));
  REQUIRE((std::is_same_v<int&, typename RangeItType::Reference>));
}