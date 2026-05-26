#ifndef HEADER_H
#define HEADER_H

#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <time.h>
#include <unordered_map>
#include <vector>
#include <ios>
#include <istream>
#include <stddef.h>
#include <strstream>

#ifdef __APPLE__
#include <sys/types.h>
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif // __APPLE__


// include nlohmann-json 
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace nlohmann;

// include SFML libary
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// include LUA libary
//extern "C" {Z
//#include <lua/lauxlib.h>
//#include <lua/lua.h>
//#include <lua/lualib.h>
//}
#endif /* HEADER_H */
