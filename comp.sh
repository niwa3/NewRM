#!/bin/sh
g++ -g -O0 manage.cpp dao.cpp sha256.cpp -lpqxx -std=c++11 -lcryptopp
#clang++ -g -O0 manage.cpp dao.cpp sha256.cpp -lpqxx -std=c++11 -lcryptopp
