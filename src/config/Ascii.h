// Copyright (c) 2018, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information

#pragma once

const std::string windowsAsciiArt =
 "\n _                             _                        _      _  \n"
 "  | |                           (_)                      | |    | |   \n" 
 "  | | __ ___   __ _   ___  ___   _  _ __     __ _   ___  | |  __| |   \n"
 "  | |/ // _ \ / _` | / __|/ _ \ | || '_ \   / _` | / _ \ | | / _` |   \n"
 "  |   <|  __/| (_| || (__| (_) || || | | | | (_| || (_) || || (_| |   \n"
 "  |_|\_\\___| \__, | \___|\___/ |_||_| |_|  \__, | \___/ |_| \__,_|   \n"
  "              __ / |                         __/ |                    \n"
  "             |____/                        |____/                     \n";

const std::string nonWindowsAsciiArt = 
      "\n _                             _                        _      _  \n"
 "  | |                           (_)                      | |    | |   \n" 
 "  | | __ ___   __ _   ___  ___   _  _ __     __ _   ___  | |  __| |   \n"
 "  | |/ // _ \ / _` | / __|/ _ \ | || '_ \   / _` | / _ \ | | / _` |   \n"
 "  |   <|  __/| (_| || (__| (_) || || | | | | (_| || (_) || || (_| |   \n"
 "  |_|\_\\___| \__, | \___|\___/ |_||_| |_|  \__, | \___/ |_| \__,_|   \n"
  "              __ / |                         __/ |                    \n"
  "             |____/                        |____/                     \n";

/* Windows has some characters it won't display in a terminal. If your ascii
   art works fine on Windows and Linux terminals, just replace 'asciiArt' with
   the art itself, and remove these two #ifdefs and above ascii arts */
#ifdef _WIN32
const std::string asciiArt = windowsAsciiArt;
#else
const std::string asciiArt = nonWindowsAsciiArt;
#endif
