#ifndef NJOY_DRYAD_RESONANCES_TABULATEDLEVELSPACINGS
#define NJOY_DRYAD_RESONANCES_TABULATEDLEVELSPACINGS

#include <vector>
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"
#include "njoy/dryad/resonances/TabulatedLevelSpacings/src/ctor.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

    /**
     *  @class
     *  @brief A tabulated average level spacing <D>(E) for one spin group
     */

    class TabulatedLevelSpacings :
        protected scion::math::InterpolationTable< double, double > {
            public:

                /* type aliases */
                using InterpolationTable::XType;
                using InterpolationTable::YType;

                /* methods */

                /**
                 *  @brief returns the energy values
                 */
                const std::vector< double >& energies() const {
                    return this->x();
                }

                /**
                 *  @brief  Return the average level spacing values
                 */
                const std::vector< double >& values() const {
                    return this->y();
                }

                /**
                 * @brief Return the lower energy limit
                 */
                double lowerEnergyLimit() const {
                    return this->x().front();
                }

                /**
                 * @brief Return the upper energy limit
                 */
                double upperEnergyLimit() const {
                    return this->x().back();
                }

                using InterpolationTable::boundaries;
                using InterpolationTable::interpolants;
                using InterpolationTable::numberPoints;
                using InterpolationTable::numberRegions;
                using InterpolationTable::isLinearised;

                using InterpolationTable::operator();

                /**
                 *  @brief  Evaluate the everage level spacing at a given energy
                 *
                 *  Interpolates on the tabulated grid using the interpolation rules.
                 */

                /**
                 *  @brief  Comparison operator: equal
                 *
                 *  @param[in] right    the object on the right-hand-side
                 */
                bool operator==( const TabulatedLevelSpacings& right ) const {
                    return InterpolationTable::operator==( right );
                }

                /**
                 *  @brief Comparison operator: not equal
                 *
                 *  @param[in] right   the object on the right hand side
                 */
                bool operator!=( const TabulatedLevelSpacings& right ) const {
                    return ! this->operator==( right );
                }
        };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
