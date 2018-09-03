#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <algorithm>
#include <array>
#include <sstream>
#include <type_traits>
#include <vector>

#include <roda/FilterIterator.hpp>
#include <roda/RangeIterator.hpp>
#include <roda/ReverseRangeIterator.hpp>
#include <roda/algorithm.hpp>

TEST_CASE("RangeIterator")
{
  auto arr = std::array<int, 5>{{1, 2, 3, 4, 5}};
  auto rangeit = roda::RangeIterator{arr};

  auto cout = std::ostringstream{};
  roda::for_each(rangeit, [&cout](auto val) { cout << val << ' '; });

  REQUIRE(cout.str() == "1 2 3 4 5 ");
}

TEST_CASE("ReverseRangeIterator")
{
  auto arr = std::array<int, 5>{{1, 2, 3, 4, 5}};
  auto rangeit = roda::ReverseRangeIterator{arr};

  auto cout = std::ostringstream{};
  roda::for_each(rangeit, [&cout](auto val) { cout << val << ' '; });

  REQUIRE(cout.str() == "5 4 3 2 1 ");
}

TEST_CASE("FilterIterator")
{
  auto arr = std::array<int, 10>{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
  auto rangeit = roda::RangeIterator{arr};
  auto filterit =
   roda::FilterIterator(rangeit, [](const auto& a) { return a >= 5; });

  auto cout = std::ostringstream{};
  roda::for_each(filterit, [&cout](auto val) { cout << val << ' '; });

  REQUIRE(cout.str() == "5 6 7 8 9 ");

  using RangeItType = std::decay_t<decltype(rangeit)>;

  REQUIRE((std::is_same_v<std::random_access_iterator_tag,
                          typename RangeItType::IteratorCategory>));
  REQUIRE((std::is_same_v<int, typename RangeItType::ValueType>));
  REQUIRE((std::is_same_v<ptrdiff_t, typename RangeItType::DifferenceType>));
  REQUIRE((std::is_same_v<int*, typename RangeItType::Pointer>));
  REQUIRE((std::is_same_v<int&, typename RangeItType::Reference>));
}

TEST_CASE("count and count_if")
{
  auto v = std::vector<int>{1, 2, 3, 4, 4, 3, 7, 8, 9, 10};
  auto it = roda::RangeIterator{v};

  auto num_items1 = roda::count(it, 3);
  auto num_items2 = roda::count(it, 5);
  auto num_items3 = roda::count_if(it, [](int i) { return i % 3 == 0; });

  REQUIRE(num_items1 == 2);
  REQUIRE(num_items2 == 0);
  REQUIRE(num_items3 == 3);
}
