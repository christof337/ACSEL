# Matrix gradient - shifting precision

"Matrice_grad" est un programme visant à simuler une descente de gradient sur une matrice.
Nous nous proposons de faire varier la précision des types utilisés afin d'observer les impacts sur la convergence. On observera aussi les impacts lors de changements de taille de matrice, de pré-remplissage de matrice, ou encore de choix de mode d'arrondi.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
If you just want to run the program, you can run src/main as a basic binary file (no prerequisites needed).

### Prerequisites

* [Gcc compiler](https://gcc.gnu.org/)
* [GSL Library](https://www.gnu.org/software/gsl/) (part of GNU)
* [CMake](https://cmake.org/)
* [MPFR](http://www.mpfr.org/)
For the tests :
* [check](https://github.com/libcheck/check/releases) 11.0.0

### Installing

Clone the repo or download the sources.
From the project root :
Initialize the config files
```
cmake .
```

Build the project

```
make
```

That's it! You just have to run the newly generated `src/main` in order to run the app.

## Running the tests

You can run tests by simply installing `check` and running
```
make test
```

## Deployment

No special attention have been given to enabling this app to run on a live system.

## Built With

* [Gcc](https://gcc.gnu.org/) - The compiler used
* [CMake](https://cmake.org/) - Build tool
* [check](https://libcheck.github.io/check/) - Testing framework

## Contributing

Feel free to contribute if you feel some improvements can be made.

## Authors

* **Christophe Pont** - *Main contributor* - [christof337](https://github.com/christof337)
* **David Defour** - *Specs lead*
* **Bijan Mohammadi** - *Initial work*

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

*Ce programme est basé sur [matrice_grad](https://github.com/christof337/ACSEL/tree/master/matrice_grad/old%20sources), fourni par Bijan Mohammadi (no copyright involved).*
