/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  ParticleID projectile_;
  ParticleID target_;
  ReactionType type_;
  std::optional< ParticleID > residual_;
  std::string short_symbol_;
  std::string long_symbol_;

public:

  /* constructor */
  Entry( ParticleID projectile, ParticleID target, ReactionType type,
         std::string sshort, std::string slong ) :
    projectile_( std::move( projectile ) ), target_( std::move( target ) ),
    type_( std::move( type ) ), short_symbol_( std::move( sshort ) ),
    long_symbol_( std::move( slong ) ),
    residual_( std::nullopt ) {

    if ( ! this->type().isSpecial() ) {


    }
  }

  /* methods */
  const ParticleID& projectile() const noexcept { return this->projectile_; }
  const ParticleID& target() const noexcept { return this->target_; }
  const ReactionType& type() const noexcept { return this->type_; }
  const std::optional< ParticleID >& residual() const noexcept { return this->residual_; }
  const std::string& shortSymbol() const noexcept { return this->short_symbol_; }
  const std::string& longSymbol() const noexcept { return this->long_symbol_; }
};
