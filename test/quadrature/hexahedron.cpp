
#include <catch2/catch.hpp>

#include "quadrature/hexahedron/gauss_legendre.hpp"
#include "interpolations/hexahedron.hpp"

#include "mesh/element_topology.hpp"
#include "interpolations/interpolation_factory.hpp"

#include <numeric>

constexpr auto ZERO_MARGIN = 1.0e-5;

using namespace neon;

TEST_CASE("Hexahedron quadrature scheme test", "[quadrature.hexahedron]")
{
    using namespace neon::quadrature::hexahedron;

    SECTION("Hexahedron", "[quadrature.hexahedron.gauss_legendre]")
    {
        gauss_legendre h1(1);
        gauss_legendre h3(3);
        gauss_legendre h5(5);

        REQUIRE(h1.points() == 1);
        REQUIRE(h3.points() == 8);
        REQUIRE(h5.points() == 27);

        REQUIRE(std::accumulate(begin(h1.weights()), end(h1.weights()), 0.0) == Approx(8.0));
        REQUIRE(std::accumulate(begin(h3.weights()), end(h3.weights()), 0.0) == Approx(8.0));
        REQUIRE(std::accumulate(begin(h5.weights()), end(h5.weights()), 0.0) == Approx(8.0));
    }
    SECTION("hexahedron8")
    {
        hexahedron8 hex8;
        gauss_legendre integration(1);

        REQUIRE(hex8.number_of_nodes() == 8);

        for (auto const& coordinate : integration.coordinates())
        {
            auto const [N, dN] = hex8.evaluate(coordinate);

            for (int i = 0; i < 8; i++)
            {
                REQUIRE(N(i) == Approx(0.125));
            }

            REQUIRE(N.sum() == Approx(1.0));

            REQUIRE(dN.col(0).sum() == Approx(0.0).margin(ZERO_MARGIN));
            REQUIRE(dN.col(1).sum() == Approx(0.0).margin(ZERO_MARGIN));
            REQUIRE(dN.col(2).sum() == Approx(0.0).margin(ZERO_MARGIN));
        }
    }
    SECTION("hexahedron20")
    {
        hexahedron20 hex20;

        gauss_legendre integration(3);

        REQUIRE(hex20.number_of_nodes() == 20);

        for (auto const& coordinate : integration.coordinates())
        {
            auto const [N, dN] = hex20.evaluate(coordinate);

            REQUIRE(N.sum() == Approx(1.0));

            REQUIRE(dN.col(0).sum() == Approx(0.0).margin(ZERO_MARGIN));
            REQUIRE(dN.col(1).sum() == Approx(0.0).margin(ZERO_MARGIN));
            REQUIRE(dN.col(2).sum() == Approx(0.0).margin(ZERO_MARGIN));
        }
    }
    SECTION("hexahedron27 one Evaluation")
    {
        hexahedron27 hex27;

        gauss_legendre integration(5);

        REQUIRE(hex27.number_of_nodes() == 27);

        for (auto const& coordinate : integration.coordinates())
        {
            auto const [N, dN] = hex27.evaluate(coordinate);

            REQUIRE(N.sum() == Approx(1.0));

            REQUIRE(dN.col(0).sum() == Approx(0.0).margin(ZERO_MARGIN));
            REQUIRE(dN.col(1).sum() == Approx(0.0).margin(ZERO_MARGIN));
            REQUIRE(dN.col(2).sum() == Approx(0.0).margin(ZERO_MARGIN));
        }
    }
}
// TEST_CASE("Hexahedron volume evaluation")
// {
//     SECTION("hexahedron8 volume evaluation")
//     {
//         hexahedron8 hex8();
//
//         matrix x(3, 8);
//         x << 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, //
//             0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0,  //
//             0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0;
//
//         REQUIRE(hex8.compute_measure(x) == Approx(1.0));
//     }
//     SECTION("hexahedron20 volume evaluation")
//     {
//         hexahedron20 hex20;
//
//         // xyz coordinates of the unit cube
//         matrix x(3, 20);
//         x << 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.5, 1.0, 0.5, 0.0, 0.5, 1.0, 0.5, 0.0, 0.0,
//             1.0, 1.0, 0.0, //
//             0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, /**/ 0.0, 0.5, 1.0, 0.5, 0.0, 0.5, 1.0, 0.5,
//             0.0, 0.0, 1.0, 1.0, //
//             0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.5,
//             0.5, 0.5, 0.5;
//
//         REQUIRE(hex20.compute_measure(x) == Approx(1.0));
//     }
//     SECTION("hexahedron27 volume evaluation")
//     {
//         SECTION("Six point rule")
//         {
//             hexahedron27 hex27;
//
//             // xyz coordinates of the unit cube
//             matrix x(3, 27);
//             x << 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, /**/ 0.5, 1.0, 0.5, 0.0, 0.5, 1.0, 0.5,
//                 0.0, 0.0, 1.0, 1.0, 0.0, /**/ 0.5, 0.5, 0.5, 0.5, 0.0, 1.0, 0.5, //
//                 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, /**/ 0.0, 0.5, 1.0, 0.5, 0.0, 0.5, 1.0, 0.5,
//                 0.0, 0.0, 1.0, 1.0, /**/ 0.5, 0.5, 0.0, 1.0, 0.5, 0.5, 0.5, //
//                 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, /**/ 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
//                 0.5, 0.5, 0.5, 0.5, /**/ 0.0, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5;
//
//             REQUIRE(hex27.compute_measure(x) == Approx(1.0));
//
//             x *= 2.0;
//
//             REQUIRE(hex27.compute_measure(x) == Approx(8.0));
//         }
//         SECTION("Eight point rule")
//         {
//             hexahedron27 hex27;
//
//             // xyz coordinates of the unit cube
//             matrix x(3, 27);
//             x << 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, /**/ 0.5, 1.0, 0.5, 0.0, 0.5, 1.0, 0.5,
//                 0.0, 0.0, 1.0, 1.0, 0.0, /**/ 0.5, 0.5, 0.5, 0.5, 0.0, 1.0, 0.5, //
//                 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, /**/ 0.0, 0.5, 1.0, 0.5, 0.0, 0.5, 1.0, 0.5,
//                 0.0, 0.0, 1.0, 1.0, /**/ 0.5, 0.5, 0.0, 1.0, 0.5, 0.5, 0.5, //
//                 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, /**/ 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
//                 0.5, 0.5, 0.5, 0.5, /**/ 0.0, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5;
//
//             REQUIRE(hex27.compute_measure(x) == Approx(1.0));
//
//             x *= 2.0;
//
//             REQUIRE(hex27.compute_measure(x) == Approx(8.0));
//         }
//     }
// }
