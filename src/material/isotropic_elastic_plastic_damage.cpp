
#include "isotropic_elastic_plastic_damage.hpp"

#include "exceptions.hpp"

#include "io/json.hpp"

namespace neon
{
isotropic_elastic_plastic_damage::isotropic_elastic_plastic_damage(json const& material_data)
    : isotropic_elastic_plastic(material_data)
{
    if (material_data.find("softening_multiplier") == end(material_data))
    {
        throw std::domain_error("\"softening_multiplier\" needs to be specified");
    }
    if (material_data.find("kinematic_hardening_modulus") == end(material_data))
    {
        throw std::domain_error("\"kinematic_hardening_modulus\" needs to be specified");
    }
    if (material_data.find("plasticity_viscous_exponent") == end(material_data))
    {
        throw std::domain_error("\"plasticity_viscous_exponent\" needs to be specified");
    }
    if (material_data.find("plasticity_viscous_denominator") == end(material_data))
    {
        throw std::domain_error("\"plasticity_viscous_denominator\" needs to be specified");
    }
    if (material_data.find("damage_viscous_exponent") == end(material_data))
    {
        throw std::domain_error("\"damage_viscous_exponent\" needs to be specified");
    }
    if (material_data.find("damage_viscous_denominator") == end(material_data))
    {
        throw std::domain_error("\"damage_viscous_denominator\" needs to be specified");
    }

    gamma = material_data["softening_multiplier"];
    C = material_data["kinematic_hardening_modulus"];
    np = material_data["plasticity_viscous_exponent"];
    sp = material_data["plasticity_viscous_denominator"];
    nd = material_data["damage_viscous_exponent"];
    sd = material_data["damage_viscous_denominator"];
}
}
