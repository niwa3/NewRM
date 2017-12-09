//sha256.h
#ifndef __INCLUDED_SHA256_H__
#define __INCLUDED_SHA256_H__

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <iostream>
#include <string>

namespace myhash{
  std::string mySha256(std::string);
  std::string genSalt();
}
#endif
