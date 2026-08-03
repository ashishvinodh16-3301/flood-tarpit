# FLOOD — C++ TCP Tarpit

A lightweight, multi-threaded TCP tarpit written in C++. Traps incoming
connections (e.g. from port scanners or automated bots) and feeds them a
slow, endless stream of junk data to waste their time and resources.

## Features
- Multi-threaded: handles many simultaneous connections independently
- User-selectable listening port at runtime
- Live connection/attacker logging to console

## Requirements
- g++ with C++17 support
- POSIX-compliant system (Linux, Termux/Android, macOS)

## Build
\`\`\`bash
g++ -std=c++17 -O2 -pthread flood.cpp -o flood
\`\`\`

## Run
\`\`\`bash
./flood
\`\`\`
You'll be prompted to choose a port, or press Enter for the default.

## Disclaimer
Intended for defensive/educational use on networks and systems you own
or are authorized to test.

## License
MIT
