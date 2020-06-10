# Update GTO in CONDA

1. Build the conda package locally using the following command inside this directory:
	```sh
	conda build .
	```

2. Upload the package using the command below, but considering the following aspects:
	- $location: the location where the package was created locally. This will be provided at the end of the previous command execution.
	- $version: the version defined in the metal.yml file.

	```sh
	anaconda upload -u cobilab $location/gto-$version-0.tar.bz2
	```