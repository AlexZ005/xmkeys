# xmkeys

xmkeys is a Qt application which maps keyboard keys to mouse buttons.

## Getting Started

Binary files could be found in releases.

To compile:
0. Run from  project directory: qpm install de.skycoder42.qhotkey
1. Open the project folder with Qt Creator and compile xmkeys binary. 
2. Compile modified xev: gcc xev.c -o xev -lX11
2.1. Place compiled xev to the build path.
3. Place xmodmapgrep.ssh file in the build path.

### Prerequisites

[qpm](https://www.qpm.io/)
xmodmap and xkbset should be available in the system

## Built using

* Qt Creator 4.4.0
* gcc 4.9.2

## Contributing

Pull requests are welcome.

## ToDo

Global shortcuts.

## Authors

* **AlexZ005**
* **Jim Fulton** - *MIT X Consortium - xev source* - [xev.c](http://xev.sourcearchive.com/documentation/1:1.0.2-0ubuntu1/xev_8c-source.html)
 
See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration
* etc

