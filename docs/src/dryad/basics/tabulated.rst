Tabulated data
==============

A lot of data given in evaluated nuclear data libraries and application data libraries
are given as tabulated data, i.e. a sequence of :math:`x` and :math:`y` values with one
or more interpolation regions. Basic examples would tabulated cross section data,
reaction product multiplicity data and probability distributions.

Data layout
-----------

All tabulated data in dryad use the same data layout. First of all, there are 4 sequences
that contain the actual raw data of the table:

* a sequence of :math:`x` values
* a sequence of :math:`y` values
* a sequence of indices pointing to the end of each interpolation region
* a sequence of interpolation types, one for each interpolation region

In addition to these 4 data sequences, each table also has a number of light-weight views
(defined by what are essentially pointers into the :math:`x` values and :math:`y` values)
that represent the interpolation regions defined in the tabulated data. Since tabulated
data must have at least one interpolation region, there will always be at least one of
these defined for any tabulated data set.

Since these internal interpolation region tables are always aware of what their interpolation
type is, they can perform operations such as interpolation, linearisation, integrations,
etc. without any branching in the source code - leading to slightly better performance.

In addition, when we can ensure that these internal interpolation regions only have unique
:math:`x` values, we can simplify a lot of operations where a duplicate :math:`x` value
would normally lead to issues such as a division by zero (this is for example the case when
interpolating over a discontinuity). The first :math:`x` value of the discontinuity will
be treated as the end point of an interpolation region and the second :math:`x` value in
the discontinuity will become the first point in the next interpolation region.

Interpolation
-------------

Any interpolation region within tabulated data will use one of the following
interpolation types:

* constant or histogram: :math:`y` is constant in :math:`x` and a panel in the tabulated
  data is interpolated as:

.. math::
   y = y_1

* lin-lin: :math:`y` is linear in :math:`x` and a panel in the tabulated data is
  interpolated as:

.. math::
   y = y_1 + \frac{y_2 - y_1}{x_2 - x_1}(x - x_1)

* lin-log: :math:`y` is linear in :math:`\ln(x)` and a panel in the tabulated data is
  interpolated as:

.. math::
   y = y_1 + \frac{y_2 - y_1}{\ln\left(\frac{x_2}{x_1}\right)}\ln\left(\frac{x}{x_1}\right)

* log-lin: :math:`\ln(y)` is linear in :math:`x` and a panel in the tabulated data is
  interpolated as:

.. math::
   y = y_1 \exp\left( \ln\left(\frac{y_2}{y_1}\right) \frac{x - x_1}{x_2 - x_1} \right)

* log-log: :math:`\ln(y)` is linear in :math:`x` and a panel in the tabulated data is
  interpolated as:

.. math::
   y = y_1 \exp\left( \ln\left(\frac{y_2}{y_1}\right) \frac{\ln\left(\frac{x}{x_1}\right)}{\ln\left(\frac{x_2}{x_1}\right)} \right)
