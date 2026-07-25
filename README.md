# Ekzeckt a game

This repository contains the game project "Ekzeckt"
in it I learn the c++ language and its capabilities
the SFML and Nolhmann-json libraries are included
also minimal work with MacOS frameworks (already was removed)

## Features

- **Texture Generation**: Procedural generation of textures using SFML and magic.
- **Noise Viewer**: Tools for Perlin and Simplex noise manipulation and visualization.
- **L-System Trees**: Implementation of L-systems for generating tree-like structures.
- **SFML Integration**: work with  the SFML 3.x.x, depending on the commit).

## Project Structure
- `content/`: contains the map, items, and game entities 
- `core/`: main functionality for initialising the application, also include math, data collections, and some tools
- `states/`: Contains application states, be it settings, editor or gameplay
- `Localisation/` contains implementation files for working with localisation (will add documentation in the future)
- `GUI/`: some stuff Buttons, sliders, etc.
- `entity/`: entity logic, useless for the current behaviour
- `metadata`: some files for building on OSX

## Known Issues

- Continued performance optimizations for large textures and noise rendering.
- Continued search for keyboard input issue
(keyboard is not handled correctly when app is launched directly instead of via VSCode (macOS issues))
- there is no correct initialization of text variables from/for localization

## Future Plans

- Work with GUI part, also with custom variabless view
- Improve GUI for noise and texture editing. 
- Improve GUI for gameplay part
- Improve save/load system something part of game, for uniform view 
- Additional procedural generation tools (e.g., terrain generation, impot/export textures, map data).
- Performance optimizations for real-time rendering.
- Work with AI/Bot system (entity logic)
- Add suport audio (for now its in test, first trying)

## Contributing

Feel free to fork the repository and submit pull requests with new ideas or fixes. Make sure to document any changes and follow the existing coding style.

## License

This repository is distributed under the MIT License. See `LICENSE` for details.

## Contact

For questions or feedback, open an issue or contact me via GitHub.

## using libs:
- SFML (https://github.com/SFML/SFML)
- nlohmann/JSON (https://github.com/nlohmann/json)

Fonts was taken from:
- https://www.1001fonts.com

The FontStruction “7:12 Serif”
(http://fontstruct.com/fontstructions/show/243645) by “CMunk” is licensed
under a Creative Commons Attribution Share Alike license
(http://creativecommons.org/licenses/by-sa/3.0/).


