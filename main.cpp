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

const std::string SOCKET_NAME="/tmp/unix-socket";
//==========RelationshipManager==============

RelationshipManager::RelationshipManager(){
  socketName_=SOCKET_NAME;
  endflag=false;
}

RelationshipManager::~RelationshipManager(){
  close(server_);
}

int main(int argc, char* argv[]){
}
