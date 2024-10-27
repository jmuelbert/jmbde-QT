###################
 Contributor Guide
###################

Thank you for your interest in improving this project. This project is
open-source under the `MIT license`_ and welcomes contributions in the
form of bug reports, feature requests, and pull requests.

Here is a list of important resources for contributors:

-  `Source Code`_
-  Documentation_
-  `Issue Tracker`_
-  `Code of Conduct`_

.. _documentation: https://{{cookiecutter.project_name}}.readthedocs.io/

.. _issue tracker: https://github.com/{{cookiecutter.github_user}}/{{cookiecutter.project_name}}/issues

.. _mit license: https://opensource.org/licenses/MIT

.. _source code: https://github.com/{{cookiecutter.github_user}}/{{cookiecutter.project_name}}

*********************
 How to report a bug
*********************

Report bugs on the `Issue Tracker`_.

When filing an issue, make sure to answer these questions:

-  Which operating system and Python version are you using?
-  Which version of this project are you using?
-  What did you do?
-  What did you expect to see?
-  What did you see instead?

The best way to get your bug fixed is to provide a test case, and/or
steps to reproduce the issue.

**************************
 How to request a feature
**************************

Request features on the `Issue Tracker`_.

********************************************
 How to set up your development environment
********************************************

You need Python 3.6+ and the following tools:

-  Poetry_
-  Nox_

Install the package with development requirements:

.. code:: console

   $ poetry install

You can now run an interactive Python session, or the command-line
interface:

.. code:: console

   $ poetry run python
   $ poetry run jmbde-python

.. _nox: https://nox.thea.codes/

.. _poetry: https://python-poetry.org/

*************************
 How to test the project
*************************

Run the full test suite:

.. code:: console

   $ nox

List the available Nox sessions:

.. code:: console

   $ nox --list-sessions

You can also run a specific Nox session. For example, invoke the unit
test suite like this:

.. code:: console

   $ nox --session=tests

Unit tests are located in the ``tests`` directory, and are written using
the pytest_ testing framework.

.. _pytest: https://pytest.readthedocs.io/

***********************
 How to submit changes
***********************

Open a `pull request`_ to submit changes to this project.

Your pull request needs to meet the following guidelines for acceptance:

-  The Nox test suite must pass without errors and warnings.
-  Include unit tests. This project maintains 100% code coverage.
-  If your changes add functionality, update the documentation
   accordingly.

Feel free to submit early, though—we can always iterate on this.

You can ensure that your changes adhere to the code style by
reformatting with Black_:

.. code:: console

   $ nox --session=black

It is recommended to open an issue before starting work on anything.
This will allow a chance to talk it over with the owners and validate
your approach.

.. _black: https://black.readthedocs.io/

.. _pull request: https://github.com/{{cookiecutter.github_user}}/{{cookiecutter.project_name}}/pulls

..
   github-only

.. _code of conduct: CODE_OF_CONDUCT.rst
