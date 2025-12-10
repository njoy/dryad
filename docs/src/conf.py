# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'dryad'
copyright = '2025, Wim Haeck'
author = 'Wim Haeck'
release = '0.0.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

# point to the folder containing the njoy. python bindings .so file
import os
import sys
sys.path.insert( 0, '../' )

extensions = [
    "sphinx.ext.autodoc",
    "numpydoc",
    ]

templates_path = ['../_templates']
exclude_patterns = []

# numpydoc settings
numpydoc_xref_param_type = True
numpydoc_class_members_toctree = False
numpydoc_show_class_members = False
numpydoc_show_inherited_class_members = False


# Napoleon settings
# napoleon_google_docstring = False
# napoleon_numpy_docstring = True
# napoleon_include_init_with_doc = True
# napoleon_include_private_with_doc = False
# napoleon_include_special_with_doc = True
# napoleon_use_admonition_for_examples = True
# napoleon_use_admonition_for_notes = True
# napoleon_use_admonition_for_references = True
# napoleon_use_ivar = False
# napoleon_use_param = True
# napoleon_usekeyword = True
# napoleon_use_rtype = True
# napoleon_preprocess_types = True
# napoleon_type_aliases = None
# napoleon_attr_annotations = True


# autodoc settings
autodoc_default_options = {
    'exclude_members': '__init__',
}
autodoc_typehints = 'both'
autodoc_docstring_signature = True
autoclass_content = 'both' # this is for signature - needs be both or init to show sig.
# best bet is to use "both" and put nothing in the init doc string


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output


html_theme = 'pydata_sphinx_theme'
# html_theme = 'haiku'
html_static_path = ['_static']

# for pydata theme
html_theme_options = {

}
