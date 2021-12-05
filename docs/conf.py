# -*- coding: utf-8 -*-
# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# http://www.sphinx-doc.org/en/master/config
"""Sphinx configuration."""
from datetime import datetime

# -- Project information -----------------------------------------------------

PROJECT = "jmbde-QT"
AUTHOR = "Jürgen Mülbert"
COPYRIGHT = f"2013-{datetime.now().year}, {AUTHOR}"
EXTENSIONS = [
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",
]
AUTODOC_TYPEHINTS = "description"
HTML_THEME = "furo"
