
#include "quadrature/tetrahedron/witherden_vincent_tetrahedron.hpp"

#include <algorithm>

namespace neon
{
witherden_vincent_tetrahedron::witherden_vincent_tetrahedron(int const minimum_degree)
{
    switch (minimum_degree)
    {
        case 1:
        {
            m_degree = 1;
            m_weights = {1.0};
            m_coordinates = {{0, 0.25, 0.25, 0.25}};
            break;
        }
        case 2:
        {
            m_degree = 2;
            m_weights = {0.25, 0.25, 0.25, 0.25};
            m_coordinates = {{0, 0.1381966011250105, 0.1381966011250105, 0.5854101966249685},
                             {1, 0.1381966011250105, 0.5854101966249685, 0.1381966011250105},
                             {2, 0.5854101966249685, 0.1381966011250105, 0.1381966011250105},
                             {3, 0.1381966011250105, 0.1381966011250105, 0.1381966011250105}};
            break;
        }
        case 3:
        {
            m_degree = 3;
            m_weights = {0.1362178425370874,
                         0.1137821574629126,
                         0.1362178425370874,
                         0.1137821574629126,
                         0.1362178425370874,
                         0.1137821574629126,
                         0.1362178425370874,
                         0.1137821574629126};
            m_coordinates = {{0, 0.3281633025163817, 0.3281633025163817, 0.015510092450854884},
                             {1, 0.1080472498984286, 0.1080472498984286, 0.6758582503047142},
                             {2, 0.3281633025163817, 0.015510092450854884, 0.3281633025163817},
                             {3, 0.1080472498984286, 0.6758582503047142, 0.1080472498984286},
                             {4, 0.015510092450854884, 0.3281633025163817, 0.3281633025163817},
                             {5, 0.6758582503047142, 0.1080472498984286, 0.1080472498984286},
                             {6, 0.3281633025163817, 0.3281633025163817, 0.3281633025163817},
                             {7, 0.1080472498984286, 0.1080472498984286, 0.1080472498984286}};
            break;
        }
        case 4:
        case 5:
        {
            m_degree = 5;
            m_weights = {0.1126879257180159,
                         0.07349304311636196,
                         0.1126879257180159,
                         0.07349304311636196,
                         0.1126879257180159,
                         0.07349304311636196,
                         0.1126879257180159,
                         0.07349304311636196,
                         0.04254602077708147,
                         0.04254602077708147,
                         0.04254602077708147,
                         0.04254602077708147,
                         0.04254602077708147,
                         0.04254602077708147};
            m_coordinates = {{0, 0.3108859192633006, 0.3108859192633006, 0.06734224221009821},
                             {1, 0.09273525031089125, 0.09273525031089125, 0.7217942490673263},
                             {2, 0.3108859192633006, 0.06734224221009821, 0.3108859192633006},
                             {3, 0.09273525031089125, 0.7217942490673263, 0.09273525031089125},
                             {4, 0.06734224221009821, 0.3108859192633006, 0.3108859192633006},
                             {5, 0.7217942490673263, 0.09273525031089125, 0.09273525031089125},
                             {6, 0.3108859192633006, 0.3108859192633006, 0.3108859192633006},
                             {7, 0.09273525031089125, 0.09273525031089125, 0.09273525031089125},
                             {8, 0.04550370412564964, 0.45449629587435036, 0.45449629587435036},
                             {9, 0.45449629587435036, 0.04550370412564964, 0.45449629587435036},
                             {10, 0.04550370412564964, 0.04550370412564964, 0.45449629587435036},
                             {11, 0.45449629587435036, 0.45449629587435036, 0.04550370412564964},
                             {12, 0.04550370412564964, 0.45449629587435036, 0.04550370412564964},
                             {13, 0.45449629587435036, 0.04550370412564964, 0.04550370412564964}};
            break;
        }
        case 6:
        {
            m_degree = 6;
            m_weights = {0.01007721105532064, 0.05535718154365472, 0.03992275025816749,
                         0.01007721105532064, 0.05535718154365472, 0.03992275025816749,
                         0.01007721105532064, 0.05535718154365472, 0.03992275025816749,
                         0.01007721105532064, 0.05535718154365472, 0.03992275025816749,
                         0.04821428571428571, 0.04821428571428571, 0.04821428571428571,
                         0.04821428571428571, 0.04821428571428571, 0.04821428571428571,
                         0.04821428571428571, 0.04821428571428571, 0.04821428571428571,
                         0.04821428571428571, 0.04821428571428571, 0.04821428571428571};
            m_coordinates = {{0, 0.04067395853461137, 0.04067395853461137, 0.8779781243961658},
                             {1, 0.3223378901422755, 0.3223378901422755, 0.0329863295731736},
                             {2, 0.214602871259152, 0.214602871259152, 0.356191386222544},
                             {3, 0.04067395853461137, 0.8779781243961658, 0.04067395853461137},
                             {4, 0.3223378901422755, 0.0329863295731736, 0.3223378901422755},
                             {5, 0.214602871259152, 0.356191386222544, 0.214602871259152},
                             {6, 0.8779781243961658, 0.04067395853461137, 0.04067395853461137},
                             {7, 0.0329863295731736, 0.3223378901422755, 0.3223378901422755},
                             {8, 0.356191386222544, 0.214602871259152, 0.214602871259152},
                             {9, 0.04067395853461137, 0.04067395853461137, 0.04067395853461137},
                             {10, 0.3223378901422755, 0.3223378901422755, 0.3223378901422755},
                             {11, 0.214602871259152, 0.214602871259152, 0.214602871259152},
                             {12, 0.06366100187501744, 0.6030056647916492, 0.26967233145831593},
                             {13, 0.6030056647916492, 0.06366100187501744, 0.26967233145831593},
                             {14, 0.06366100187501744, 0.06366100187501744, 0.26967233145831593},
                             {15, 0.6030056647916492, 0.26967233145831593, 0.06366100187501744},
                             {16, 0.06366100187501744, 0.26967233145831593, 0.06366100187501744},
                             {17, 0.26967233145831593, 0.06366100187501744, 0.06366100187501744},
                             {18, 0.06366100187501744, 0.26967233145831593, 0.6030056647916492},
                             {19, 0.26967233145831593, 0.06366100187501744, 0.6030056647916492},
                             {20, 0.06366100187501744, 0.06366100187501744, 0.6030056647916492},
                             {21, 0.26967233145831593, 0.6030056647916492, 0.06366100187501744},
                             {22, 0.06366100187501744, 0.6030056647916492, 0.06366100187501744},
                             {23, 0.6030056647916492, 0.06366100187501744, 0.06366100187501744}};
            break;
        }
        default:
        {
            throw std::domain_error("This is not the scheme you are looking for.");
        }
    }

    // Convert the weightings to proper quadrature format
    std::transform(begin(m_weights), end(m_weights), begin(m_weights), [](auto const weight) {
        return weight / 6.0;
    });
}
}