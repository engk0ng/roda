#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <algorithm>
#include <array>
#include <sstream>
#include <vector>

#include <roda/algorithm.hpp>
#include <roda/FilterIterator.hpp>
#include <roda/RangeIterator.hpp>

TEST_CASE("RangeIterator and FilterIterator")
{
  auto range =
   std::array<int, 20>{{15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}};
  auto rangeit = roda::RangeIterator{range};
  auto filterit =
   roda::FilterIterator(rangeit, [](const auto& a) { return a > 20; });

  auto cout = std::ostringstream{};
  roda::for_each(filterit, [&cout](auto val) {
    cout << val << ' ';
  });

  REQUIRE(cout.str() == "21 22 23 24 25 ");
}