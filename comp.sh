#!/bin/sh
g++ manage.cpp dao.cpp sha256.cpp -lpqxx -std=c++11 -lcryptopp
