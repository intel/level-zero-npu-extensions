# Instructions for Building the Level Zero Graph Extension Documentation

The directory contains documentation for the Intel Level Zero graph extension API for the Intel Movidius VPU driver. Documentation generation relies on Sphinx Python documentation generator. Before you can generate new documentation, please set up your Python virtual envoronment and install Sphinx. For example, run the following commands in a Git Bash terminal.

```shell
    pip install --upgrade pip
    pip install sphinx breathe sphinx_rtd_theme sphinxcontrib-visio
```

Once the virtual environment is ready, you can refresh documentation in the *build/html* directory and deploy it to the server.

```shell
    git remote update
    git checkout -b gh-pages origin/gh-pages
    git rebase origin/master
    sphinx-build -b html src build/html
    git add build/html
    git commit -m "Update Sphinx documentation"
    git push -f origin gh-pages
```
