#!/bin/sh
#g++ -Wall -g -O0 test.cpp relationship_manager.cpp relation_creater.cpp dao/dao.cpp manage/customer.cpp manage/device.cpp manage/login.cpp manage/relationship.cpp manage/service.cpp manage/vender.cpp utility/sha256.cpp -lpqxx -std=c++11 -lcryptopp
g++ -Wall -g -O0 test.cpp relationship_manager.cpp dao/dao.cpp manage/customer.cpp manage/device.cpp manage/login.cpp manage/relationship.cpp manage/service.cpp manage/vender.cpp utility/sha256.cpp -lpqxx -std=c++11 -lcryptopp
#clang++ -g -O0 manage.cpp dao.cpp sha256.cpp -lpqxx -std=c++11 -lcryptopp
