#!/bin/sh
g++ -Wall -g -O0 test.cpp relationship_manager.cpp relation_creater.cpp manage.cpp dao.cpp sha256.cpp -lpqxx -std=c++11 -lcryptopp
#clang++ -g -O0 manage.cpp dao.cpp sha256.cpp -lpqxx -std=c++11 -lcryptopp
