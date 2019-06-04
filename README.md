# meuporg
Best #meuporg.

[![Build Status](https://travis-ci.org/Qu3tzal/meuporg.svg?branch=royale)](https://travis-ci.org/Qu3tzal/meuporg)

Checkout the `royale`  branch to see how we are turning this amazing MMORPG into an awesome Battle Royale !

To compile the SFML

to clone the repo with the SFML

```
git clone --recursive https://github.com/Qu3tzal/meuporg.git
```
To compile the SFML
```
cd SFML
cmake . -DCMAKE_BUILD_TYPE=Debug && make
cmake . -DCMAKE_BUILD_TYPE=Release && make
```

To compile the client 

```
cd meuporg-client
mkdir build
cd build
cmake ..
make
```
To compile the server 

```
cd meuporg-server
mkdir build
cd build
cmake ..
make
```
