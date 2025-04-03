/**
 *  @class
 *  @brief Private helper class to reaction products and residual resolution
 */
class Entry {

  /* fields */
  int mt_;
  std::vector< unsigned int > particles_;
  int residual_;

  /* auxiliary functions */
  int resolveResidual() {

    int residual = 0;
    residual -= this->neutrons();
    residual -= 1001 * this->protons();
    residual -= 1002 * this->deuterons();
    residual -= 1003 * this->tritons();
    residual -= 2003 * this->helions();
    residual -= 2004 * this->alphas();
    return residual;
  }

public:

  /* constructor */
  Entry( int mt, std::vector< unsigned int > particles ) :
      mt_( mt ), particles_( std::move( particles ) ) {

    this->residual_ = resolveResidual();
  }

  /* methods */
  auto mt() const { return this->mt_; }
  int neutrons() const  { return this->particles_[0]; }
  int protons() const   { return this->particles_[1]; }
  int deuterons() const { return this->particles_[2]; }
  int tritons() const   { return this->particles_[3]; }
  int helions() const   { return this->particles_[4]; }
  int alphas() const    { return this->particles_[5]; }
};
