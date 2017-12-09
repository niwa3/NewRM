//sha256.cpp
#include "sha256.h"

namespace myhash{
  std::string mySha256(std::string src){
    byte buffer[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256 hash;
    hash.CalculateDigest(buffer,(byte*)src.c_str(),src.size());
    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(buffer,sizeof(buffer));
    encoder.MessageEnd();
    return output;
  }
  
  std::string genSalt(){
    std::string salt;
    byte buffer[8];
    CryptoPP::OS_GenerateRandomBlock(true, buffer, 8);
    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::StringSink(salt));
    encoder.Put(buffer,sizeof(buffer));
    encoder.MessageEnd();
    return salt;
  }
}

