#include "./define.h"

const int PriLvl::MAXLVL=3;
const int PriLvl::MINLVL=0;
const int PriLvl::HIGH=3;
const int PriLvl::MID=2;
const int PriLvl::LOW=1;
const int PriLvl::NONE=0;

const int NodeType::SENSOR=1;
const int NodeType::ACTUATOR=3;
const int NodeType::NONE=0;

const int DataType::POWER=1;
const int DataType::TEMP=2;
const int DataType::CO2=3;
const int DataType::WIND=4;
const int DataType::NONE=0;

const sig_atomic_t eflag=0;
const std::string SOCKET_NAME="/tmp/unix-socket";

void sigpipe_handle(int x){
  std::cerr<<"sigerr\n";
  eflag=1;
}
//==========RelationshipManager==============

RelationshipManager::RelationshipManager(){
  socketName_=SOCKET_NAME;

  unlink(socketName_.c_str());
}

RelationshipManager::~RelationshipManager(){
}

void RelationshipManager::run(){
  create();
  serve();
}

void RelationshipManager::create(){
  try{
    struct sockaddr_un server_addr;
    int soval = 1;

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socketName_.c_str(), sizeof(server_addr.sun_path) -1);
  
  }
}

int main(int argc, char* argv[]){
}
