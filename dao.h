#ifndef __INCLUDED_DAO_H_
#define __INCLUDED_DAO_H_

#include <iostream>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include <memory>
#include <vector>
#include <cryptopp/osrng.h>
#include <iomanip>
#include <unistd.h>
//#include "type.h"
#include "sha256.h"

class DataBase{
  private:
    std::unique_ptr<pqxx::connection> conn;

};

#endif
