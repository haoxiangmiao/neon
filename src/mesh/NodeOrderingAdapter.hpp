
#pragma once

#include "mesh/ElementTopology.hpp"
#include "numeric/IndexTypes.hpp"

#include <unordered_map>

#include <vtkCellType.h>

namespace neon
{
/**
 * NodeOrderingAdapter provides methods for converting the element nodal
 * connectivity ordering between different formats.
 */
class NodeOrderingAdapter
{
public:
    /**
     * Convert the nodal connectivities from the gmsh node ordering to the
     * reference ordering in \cite Hughes2012
     */
    void convert_from_gmsh(std::vector<List>& nodal_connectivity,
                           ElementTopology const topology) const;

    [[nodiscard]] std::vector<List> convert_to_vtk(std::vector<List> nodal_connectivity,
                                                   ElementTopology const element_topology) const;

    /** Add strong types to gmsh integer element codes */
    [[nodiscard]] ElementTopology gmsh_type_to_enum(int const element_code) const;

    [[nodiscard]] VTKCellType to_vtk(ElementTopology element_topology) const;

protected:
    std::unordered_map<int, ElementTopology> gmsh_converter{{2, ElementTopology::Triangle3},
                                                            {3, ElementTopology::Quadrilateral4},
                                                            {4, ElementTopology::Tetrahedron4},
                                                            {5, ElementTopology::Hexahedron8},
                                                            {6, ElementTopology::Prism6},
                                                            {9, ElementTopology::Triangle6},
                                                            {11, ElementTopology::Tetrahedron10},
                                                            {10, ElementTopology::Quadrilateral9},
                                                            {12, ElementTopology::Hexahedron27},
                                                            {16, ElementTopology::Quadrilateral8},
                                                            {17, ElementTopology::Hexahedron20}};

    std::unordered_map<ElementTopology, VTKCellType>
        vtk_converter{{ElementTopology::Triangle3, VTK_TRIANGLE},
                      {ElementTopology::Quadrilateral4, VTK_QUAD},
                      {ElementTopology::Quadrilateral8, VTK_QUADRATIC_QUAD},
                      {ElementTopology::Quadrilateral9, VTK_BIQUADRATIC_QUAD},
                      {ElementTopology::Tetrahedron4, VTK_TETRA},
                      {ElementTopology::Hexahedron8, VTK_HEXAHEDRON},
                      {ElementTopology::Prism6, VTK_WEDGE},
                      {ElementTopology::Triangle6, VTK_QUADRATIC_TRIANGLE},
                      {ElementTopology::Tetrahedron10, VTK_QUADRATIC_TETRA},
                      {ElementTopology::Hexahedron20, VTK_QUADRATIC_HEXAHEDRON},
                      {ElementTopology::Hexahedron27, VTK_TRIQUADRATIC_HEXAHEDRON}};
};
}
