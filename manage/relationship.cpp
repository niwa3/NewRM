#include "manage.h"


//==========RelationshipManageFuncs============
RelationshipManageFuncs::RelationshipManageFuncs(std::string filename)
{
  std::ifstream db_conf(filename.c_str(), std::ios::in);
  std::string reading_line_buffer;
  std::vector<std::string> conf;
  std::string dbname;
  std::string user;
  std::string password;

  while(std::getline(db_conf, reading_line_buffer)){
    std::cout<<reading_line_buffer<<std::endl;
    std::string separated_string_buffer;
    std::istringstream line_separater(reading_line_buffer);
    while(std::getline(line_separater, separated_string_buffer, '=')){
      std::istringstream separated_word(separated_string_buffer);
      std::string tmp_conf;
      separated_word>>tmp_conf;
      conf.push_back(tmp_conf);
    }
  }

  for(std::vector<std::string>::iterator itr = conf.begin(); itr!=conf.end(); itr++){
    if(*itr=="dbname")dbname=*(itr+1);
    else if(*itr=="username")user=*(itr+1);
    else if(*itr=="password")password=*(itr+1);
  }

  r_dao.reset(new RelationshipDao(dbname,user,password));
}

int RelationshipManageFuncs::register_Relation(
    int d_id,
    std::string device_name,
    int s_id,
    std::string service_name,
    ANONYMITYMETHOD anonymity_method,
    int privacy_standard,
    int interval,
    std::string location)
{
  return r_dao->put(d_id, device_name, s_id, service_name, anonymity_method, privacy_standard, interval, location);
}

std::vector<int> RelationshipManageFuncs::register_Relation(
    std::vector<Relationship> new_relationships)
{
  return r_dao->put_all(new_relationships);
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_d_id(int d_id)
{
  std::vector<Relationship> relation_from_db;
  r_dao->fetch("where d_id="+std::to_string(d_id), relation_from_db);
  return relation_from_db;
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_s_id(int s_id)
{
  std::vector<Relationship> relation_from_db;
  r_dao->fetch("where s_id="+std::to_string(s_id), relation_from_db);
  return relation_from_db;
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_c_id(int c_id)
{
  std::vector<Relationship> relation_from_db;
  std::string WHERE_JOIN = "INNER JOIN ( select distinct d.id from device_info d where d.c_id=" + std::to_string(c_id)+" ) t on r.d_id = t.id";
  if (r_dao->fetch(WHERE_JOIN, relation_from_db)){return relation_from_db;}
  else return relation_from_db;
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_v_id(int v_id)
{
  std::vector<Relationship> relation_from_db;
  std::string WHERE_JOIN = "INNER JOIN ( select distinct s.id from service_info s where s.v_id=" + std::to_string(v_id)+" ) t on r.s_id = t.id";
  if (r_dao->fetch(WHERE_JOIN, relation_from_db)){return relation_from_db;}
  else return relation_from_db;
}

bool RelationshipManageFuncs::update_Relation_by_r_id(int r_id, std::string set_attr){
  return r_dao->update(set_attr, "id = " + std::to_string(r_id));
}

bool RelationshipManageFuncs::delete_Relation_by_r_id(int r_id){
  return r_dao->del("id = "+std::to_string(r_id));
}

bool RelationshipManageFuncs::delete_Relation_by_r_id(std::vector<int> r_id){
  int num = r_id.size();
  if(num == 1){
  return r_dao->del("id = "+std::to_string(*r_id.begin()));
  }
  std::string DEL_LIST = "id IN (";
  int i = 1;
  for(int id: r_id){
    DEL_LIST += std::to_string(id) + (i != num ? "," : "");
    i++;
  }
  DEL_LIST += ")";
  return r_dao->del(DEL_LIST);
}

bool RelationshipManageFuncs::delete_Relation_by_d_id(int d_id){
  return r_dao->del("d_id = "+std::to_string(d_id));
}

bool RelationshipManageFuncs::delete_Relation_by_s_id(int s_id){
  return r_dao->del("s_id = "+std::to_string(s_id));
}
