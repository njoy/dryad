.. currentmodule:: njoy.dryad

ReactionProduct
===============

The ReactionProduct class contains all information such as multiplicity, distribution
data or derived data such as average cosine and energy for a given reaction product.

Constructor
~~~~~~~~~~~
.. autosummary::
    :toctree:  generated/

    ReactionProduct

Modifiable Attributes
~~~~~~~~~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/

    ~ReactionProduct.product_identifier
    ~ReactionProduct.parent_identifier
    ~ReactionProduct.chain_index
    ~ReactionProduct.multiplicity
    ~ReactionProduct.average_cosine
    ~ReactionProduct.average_energy
    ~ReactionProduct.distribution_data

Read-only Attributes
~~~~~~~~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/

    ~ReactionProduct.has_average_cosine
    ~ReactionProduct.has_average_energy
    ~ReactionProduct.has_distribution_data

Methods
~~~~~~~
.. autosummary::
    :toctree: generated/

    ~ReactionProduct.normalise
