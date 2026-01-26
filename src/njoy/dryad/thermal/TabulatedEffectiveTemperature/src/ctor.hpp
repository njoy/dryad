private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedEffectiveTemperature( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedEffectiveTemperature() = default;

TabulatedEffectiveTemperature( const TabulatedEffectiveTemperature& ) = default;
TabulatedEffectiveTemperature( TabulatedEffectiveTemperature&& ) = default;

TabulatedEffectiveTemperature& operator=( const TabulatedEffectiveTemperature& ) = default;
TabulatedEffectiveTemperature& operator=( TabulatedEffectiveTemperature&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param moderatorTemperatures   the moderator temperatures values
 *  @param values                  the effective temperature values
 *  @param boundaries              the boundaries of the interpolation regions
 *  @param interpolants            the interpolation types of the interpolation regions
 */
TabulatedEffectiveTemperature( std::vector< double > moderatorTemperatures,
                     std::vector< double > values,
                     std::vector< std::size_t > boundaries,
                     std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( moderatorTemperatures ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for an effective temperature table using a single interpolation zone
 *
 *  @param moderatorTemperatures   the moderator temperatures values
 *  @param values                  the effective temperature values
 *  @param interpolant             the interpolation type of the data (default lin-lin)
 */
TabulatedEffectiveTemperature( std::vector< double > moderatorTemperatures,
                              std::vector< double > values,
                              InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( moderatorTemperatures ), std::move( values ), interpolant ) {}
