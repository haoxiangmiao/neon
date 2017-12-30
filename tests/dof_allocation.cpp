
#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "mesh/DofAllocator.hpp"

#include <range/v3/view/set_algorithm.hpp>

#include <memory>

using namespace neon;

constexpr auto ZERO_MARGIN = 1.0e-5;

TEST_CASE("Dof List Allocation", "[DofAllocator]")
{
    SECTION("One element")
    {
        std::vector<std::vector<int64>> const nodal_connectivity{{0, 1, 2, 3}};

        std::vector<std::vector<int64>> const known_dof_list{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}};

        std::vector<std::vector<int64>> const computed_list = allocate_dof_list(3,
                                                                                nodal_connectivity);

        REQUIRE(ranges::view::set_difference(computed_list.at(0), known_dof_list.at(0)).empty());
    }
    SECTION("Two elements")
    {
        std::vector<std::vector<int64>> const nodal_connectivity = {{0, 1, 2, 3}, {4, 2, 1, 5}};

        std::vector<std::vector<int64>> const known_dof_list{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                                                             {12, 13, 14, 6, 7, 8, 3, 4, 5, 15, 16, 17}};

        std::vector<std::vector<int64>> const computed_list = allocate_dof_list(3,
                                                                                nodal_connectivity);

        REQUIRE(ranges::view::set_difference(computed_list.at(0), known_dof_list.at(0)).empty());
        REQUIRE(ranges::view::set_difference(computed_list.at(1), known_dof_list.at(1)).empty());
    }
}
TEST_CASE("Dof List Filter", "[DofAllocator]")
{
    SECTION("One element 0 offset")
    {
        std::vector<std::vector<int64>> const nodal_connectivity = {{0, 1, 2, 3}};

        std::vector<std::vector<int64>> const known_dof_list{{0, 3, 6, 9}};

        std::vector<std::vector<int64>> const computed_list = filter_dof_list(3, 0, nodal_connectivity);

        REQUIRE(ranges::view::set_difference(computed_list.at(0), known_dof_list.at(0)).empty());
    }
    SECTION("One element 1 offset")
    {
        std::vector<std::vector<int64>> const nodal_connectivity = {{0, 1, 2, 3}};

        std::vector<std::vector<int64>> const known_dof_list{{1, 4, 7, 10}};

        std::vector<std::vector<int64>> const computed_list = filter_dof_list(3, 1, nodal_connectivity);

        REQUIRE(ranges::view::set_difference(computed_list.at(0), known_dof_list.at(0)).empty());
    }
}
