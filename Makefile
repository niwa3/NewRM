CXXFLAGS = -Wall -lpqxx -std=c++11 -lcryptopp
test: relationship_manager.o
		g++ -o test test.cpp relationship_manager.o dao.o customer.o device.o login.o relationship.o service.o vender.o sha256.o $(CXXFLAGS)
relationship_manager.o: relationship_manager.cpp
		g++ -c relationship_manager.cpp dao/dao.cpp manage/customer.cpp manage/device.cpp manage/login.cpp manage/relationship.cpp manage/service.cpp manage/vender.cpp utility/sha256.cpp $(CXXFLAGS)
clean:
		rm -f *.o test
