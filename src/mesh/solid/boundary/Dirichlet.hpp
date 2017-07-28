
#pragma once

#include "mesh/solid/boundary/Boundary.hpp"
#include "numeric/DenseTypes.hpp"

namespace neon::solid
{
class Dirichlet : public Boundary
{
public:
    Dirichlet(List dofs, double const prescribed_value, bool const is_load_ramped = true);

    auto const& dof_view() const { return dofs; }

    /** Get the value depending on the loading factor */
    auto const value_view(double const load_factor) const
    {
        return interpolate_prescribed_value(load_factor);
    }

protected:
    List dofs;
};
}
