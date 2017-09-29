#include "dao.h"


//===========class DataBase===========
DataBase::DataBase(
    std::string dbname,
    std::string user,
    std::string password
    )
{
  try{
  std::string CONNECT_CONF="dbname='"+dbname;
  CONNECT_CONF+="' user='"+user;
  CONNECT_CONF+="' password='"+password+"'";
  _conn.reset(new pqxx::connection(CONNECT_CONF));
  if(_conn.get()->is_open()){
      std::cout<<"Database "<<_conn.get()->dbname()<<" opened." <<std::endl;
  }
  }catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
  }
}

DataBase::~DataBase(){ 
  if(_conn){
    if(_conn.get()->is_open()) _conn.get()->disconnect();
  }
}
//====================================



//===========class LoginInfoDao=======
LoginInfoDao::LoginInfoDao(
    std::string dbname, 
    std::string user, 
    std::string password
    )
  : DataBase(dbname, user, password){
}

bool LoginInfoDao::put(
    std::string login,
    std::string hashed_pass,
    std::string salt,
    USERTYPE user_type)
{
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_LOGIN_INFO;

    INSERT_LOGIN_INFO = "INSERT INTO login_info(login, passwd, salt, user_type) VALUES ("
      + _T.get()->quote(login) + ","
      + _T.get()->quote(hashed_pass)+ ","
      + _T.get()->quote(salt) + ", "
      + std::to_string((int)user_type) + ");";

    _T.get()->exec(INSERT_LOGIN_INFO);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool LoginInfoDao::fetch(
    std::string where, 
    LoginInfo &info_from_db)
{
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_LOGIN_INFO;
    SELECT_LOGIN_INFO = "SELECT id, login, passwd, salt, user_type FROM login_info WHERE "
      + where + ";";
    pqxx::result login_info_from_db;
    login_info_from_db=_T.get()->exec(SELECT_LOGIN_INFO);
    if(login_info_from_db.empty()){
      std::cerr<< where + " does not exist.\n";
      return false;
    }
    pqxx::result::iterator itr_login_info;
    itr_login_info = login_info_from_db.begin();
    info_from_db.user_id = itr_login_info["id"].as<int>();
    info_from_db.login = itr_login_info["login"].as<std::string>();
    info_from_db.salt = itr_login_info["salt"].as<std::string>();
    info_from_db.hashed_pass = itr_login_info["passwd"].as<std::string>();
    info_from_db.user_type = static_cast<USERTYPE>(itr_login_info["user_type"].as<int>());
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool LoginInfoDao::update(std::string set_attr, std::string where)
{ try{ _T.reset(new pqxx::work(*_conn.get())); std::string UPDATE; UPDATE = "UPDATE login_info SET " + set_attr + " WHERE " + where + ";"; _T.get()->exec(UPDATE); _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}
//====================================



//========class CustomerInfoDao=======
CustomerInfoDao::CustomerInfoDao(
    std::string dbname,
    std::string user,
    std::string password)
: DataBase(dbname, user, password){
}

bool CustomerInfoDao::put(
    int l_id,
    std::string last_name,
    std::string first_name,
    std::string birthday,
    std::string phone_num,
    std::string e_mail_addr
    ){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_CUSTOMER_INFO;
    INSERT_CUSTOMER_INFO = "INSERT INTO customer_info"
      "(l_id, last_name, first_name, birthday, phone_num, e_mail_addr)"
      " VALUES (" + std::to_string(l_id) +
      "," + _T.get()->quote(last_name) +
      "," + _T.get()->quote(first_name) +
      ", " + _T.get()->quote(birthday) +
      "," + _T.get()->quote(phone_num) +
      "," + _T.get()->quote(e_mail_addr) +
      ");";
    _T.get()->exec(INSERT_CUSTOMER_INFO);
    _T.get()->commit();
    return true;
  }

  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool CustomerInfoDao::fetch(
    std::string where,
    CustomerInfo &customer_info_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_CUSTOMER_INFO;
    SELECT_CUSTOMER_INFO = "SELECT id, l_id, last_name, first_name, birthday, phone_num, e_mail_addr "
      "FROM customer_info WHERE "
      + where + ";";
    pqxx::result result_from_db;
    result_from_db =_T.get()->exec(SELECT_CUSTOMER_INFO);
    if(result_from_db.empty()){
      std::cerr<<"no customer info\n";
      return false;
    }
    pqxx::result::iterator itr_result_info;
    itr_result_info = result_from_db.begin();
    customer_info_from_db.l_id = itr_result_info["l_id"].as<int>();
    customer_info_from_db.c_id = itr_result_info["id"].as<int>();
    customer_info_from_db.last_name = itr_result_info["last_name"].as<std::string>();
    customer_info_from_db.first_name = itr_result_info["first_name"].as<std::string>();
    customer_info_from_db.birthday = itr_result_info["birthday"].as<std::string>();
    customer_info_from_db.phone_num = itr_result_info["phone_num"].as<std::string>();
    customer_info_from_db.e_mail_addr = itr_result_info["e_mail_addr"].as<std::string>();
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
};

bool CustomerInfoDao::update(
    std::string set_attr,
    std::string where){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string UPDATE;
    UPDATE = "UPDATE customer_info SET " + set_attr + " WHERE " + where + ";";
    _T.get()->exec(UPDATE);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}
//====================================

//===========DeviceInfoDao============
DeviceInfoDao::DeviceInfoDao(
    std::string dbname,
    std::string user,
    std::string password)
: DataBase(dbname, user, password){
}

bool DeviceInfoDao::put(
    int c_id,
    std::string device_name,
    int default_privacy_standard,
    DEVICETYPE device_type,
    DATATYPE data_type,
    int interval,
    std::string location
    ){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_DEVICE_INFO;
    INSERT_DEVICE_INFO = "INSERT INTO device_info"
      "(c_id, device_name, device_type, data_type, default_privacy_standard, interval, location)"
      " VALUES (" + std::to_string(c_id) +
      "," + _T.get()->quote(device_name) +
      "," + std::to_string(static_cast<int>(device_type)) +
      "," + std::to_string(static_cast<int>(data_type)) +
      "," + std::to_string(default_privacy_standard) +
      "," + std::to_string(interval) +
      "," + _T.get()->quote(location) +
      ");";
    _T.get()->exec(INSERT_DEVICE_INFO);
    _T.get()->commit();
    return true;
  }

  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool DeviceInfoDao::fetch(
    std::string where,
    DeviceInfo &device_info_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_DEVICE_INFO;
    SELECT_DEVICE_INFO = "SELECT id, c_id, device_name, device_type, data_type, default_privacy_standard, interval, location"
      "FROM device_info WHERE "
      + where + ";";
    pqxx::result result_from_db;
    result_from_db =_T.get()->exec(SELECT_DEVICE_INFO);
    if(result_from_db.empty()){
      std::cerr<<"no device info\n";
      return false;
    }
    pqxx::result::iterator itr_result_info;
    itr_result_info = result_from_db.begin();
    device_info_from_db.c_id = itr_result_info["c_id"].as<int>();
    device_info_from_db.d_id = itr_result_info["id"].as<int>();
    device_info_from_db.device_name = itr_result_info["device_name"].as<std::string>();
    device_info_from_db.device_type = static_cast<DEVICETYPE>(itr_result_info["device_type"].as<int>());
    device_info_from_db.data_type = static_cast<DATATYPE>(itr_result_info["data_type"].as<int>());
    device_info_from_db.default_privacy_standard = itr_result_info["default_privacy_standard"].as<int>();
    device_info_from_db.interval = itr_result_info["interval"].as<int>();
    device_info_from_db.location = itr_result_info["location"].as<std::string>();
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
};

bool DeviceInfoDao::update(
    std::string set_attr,
    std::string where){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string UPDATE;
    UPDATE = "UPDATE device_info SET " + set_attr + " WHERE " + where + ";";
    _T.get()->exec(UPDATE);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}
//====================================


//========class VenderInfoDao=======
VenderInfoDao::VenderInfoDao(
    std::string dbname,
    std::string user,
    std::string password)
: DataBase(dbname, user, password){
}

bool VenderInfoDao::put(
    int l_id,
    std::string name,
    std::string phone_num,
    std::string e_mail_addr
    ){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_VENDER_INFO;
    INSERT_VENDER_INFO = "INSERT INTO vender_info"
      "(l_id, name, phone_num, e_mail_addr)"
      " VALUES (" + std::to_string(l_id) +
      "," + _T.get()->quote(name) +
      "," + _T.get()->quote(phone_num) +
      "," + _T.get()->quote(e_mail_addr) +
      ");";
    _T.get()->exec(INSERT_VENDER_INFO);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool VenderInfoDao::fetch(
    std::string where,
    VenderInfo &vender_info_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_VENDER_INFO;
    SELECT_VENDER_INFO = "SELECT id, l_id, name, phone_num, e_mail_addr "
      "FROM vender_info WHERE "
      + where + ";";
    pqxx::result result_from_db;
    result_from_db =_T.get()->exec(SELECT_VENDER_INFO);
    if(result_from_db.empty()){
      std::cerr<<"no vender info\n";
      return false;
    }
    pqxx::result::iterator itr_result_info;
    itr_result_info = result_from_db.begin();
    vender_info_from_db.l_id = itr_result_info["l_id"].as<int>();
    vender_info_from_db.v_id = itr_result_info["id"].as<int>();
    vender_info_from_db.name = itr_result_info["name"].as<std::string>();
    vender_info_from_db.phone_num = itr_result_info["phone_num"].as<std::string>();
    vender_info_from_db.e_mail_addr = itr_result_info["e_mail_addr"].as<std::string>();
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
};

bool VenderInfoDao::update(
    std::string set_attr,
    std::string where){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string UPDATE;
    UPDATE = "UPDATE vender_info SET " + set_attr + " WHERE " + where + ";";
    _T.get()->exec(UPDATE);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

//====================================


//===========ServiceInfoDao============
ServiceInfoDao::ServiceInfoDao(
    std::string dbname,
    std::string user,
    std::string password)
: DataBase(dbname, user, password){
}

bool ServiceInfoDao::put(
    int v_id,
    std::string service_name,
    int required_privacy_standard,
    DATATYPE data_type,
    int interval
    ){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_SERVICE_INFO;
    INSERT_SERVICE_INFO = "INSERT INTO service_info"
      "(v_id, service_name, data_type, required_privacy_standard, interval)"
      " VALUES (" + std::to_string(v_id) +
      "," + _T.get()->quote(service_name) +
      "," + std::to_string(static_cast<int>(data_type)) +
      "," + std::to_string(required_privacy_standard) +
      "," + std::to_string(interval) +
      ");";
    _T.get()->exec(INSERT_SERVICE_INFO);
    _T.get()->commit();
    return true;
  }

  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool ServiceInfoDao::fetch(
    std::string where,
    ServiceInfo &service_info_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_SERVICE_INFO;
    SELECT_SERVICE_INFO = "SELECT id, v_id, service_name, data_type, required_privacy_standard, interval"
      "FROM service_info WHERE "
      + where + ";";
    pqxx::result result_from_db;
    result_from_db =_T.get()->exec(SELECT_SERVICE_INFO);
    if(result_from_db.empty()){
      std::cerr<<"no service info\n";
      return false;
    }
    pqxx::result::iterator itr_result_info;
    itr_result_info = result_from_db.begin();
    service_info_from_db.v_id = itr_result_info["v_id"].as<int>();
    service_info_from_db.s_id = itr_result_info["id"].as<int>();
    service_info_from_db.service_name = itr_result_info["service_name"].as<std::string>();
    service_info_from_db.data_type = static_cast<DATATYPE>(itr_result_info["data_type"].as<int>());
    service_info_from_db.required_privacy_standard = itr_result_info["required_privacy_standard"].as<int>();
    service_info_from_db.interval = itr_result_info["interval"].as<int>();
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
};

bool ServiceInfoDao::update(
    std::string set_attr,
    std::string where){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string UPDATE;
    UPDATE = "UPDATE service_info SET " + set_attr + " WHERE " + where + ";";
    _T.get()->exec(UPDATE);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}
//====================================

//===========RelationshipDao============
RelationshipDao::RelationshipDao(
    std::string dbname,
    std::string user,
    std::string password)
: DataBase(dbname, user, password){
}

bool RelationshipDao::put(
    int d_id,
    int s_id,
    ANONYMITYMETHOD anonymity_method,
    int privacy_standard,
    int interval,
    std::string location
    ){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_RELATIONSHIP;
    INSERT_RELATIONSHIP = "INSERT INTO relationship"
      "(d_id, s_id, anonymity_method, privacy_standard, interval, location)"
      " VALUES (" + std::to_string(d_id) +
      "," + std::to_string(s_id) +
      "," + std::to_string(static_cast<int>(anonymity_method)) +
      "," + std::to_string(privacy_standard) +
      "," + std::to_string(interval) +
      "," + _T->quote(location) +
      ");";
    _T.get()->exec(INSERT_RELATIONSHIP);
    _T.get()->commit();
    return true;
  }

  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool RelationshipDao::fetch(
    std::string where,
    Relationship &relationship_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_RELATIONSHIP;
    SELECT_RELATIONSHIP = "SELECT id, d_id, s_id, anonymity_method, privacy_standard, interval, location"
      "FROM relationship WHERE "
      + where + ";";
    pqxx::result result_from_db;
    result_from_db =_T.get()->exec(SELECT_RELATIONSHIP);
    if(result_from_db.empty()){
      std::cerr<<"no service info\n";
      return false;
    }
    pqxx::result::iterator itr_result_info;
    itr_result_info = result_from_db.begin();
    relationship_from_db.d_id = itr_result_info["d_id"].as<int>();
    relationship_from_db.s_id = itr_result_info["s_id"].as<int>();
    relationship_from_db.r_id = itr_result_info["id"].as<int>();
    relationship_from_db.anonymity_method = static_cast<ANONYMITYMETHOD>(itr_result_info["anonymity_method"].as<int>());
    relationship_from_db.privacy_standard = itr_result_info["privacy_standard"].as<int>();
    relationship_from_db.interval = itr_result_info["interval"].as<int>();
    relationship_from_db.location = itr_result_info["location"].as<std::string>();
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
};

bool RelationshipDao::update(
    std::string set_attr,
    std::string where){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string UPDATE;
    UPDATE = "UPDATE relationship SET " + set_attr + " WHERE " + where + ";";
    _T.get()->exec(UPDATE);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}
//====================================


/*int main(){
  LoginInfoDao login_db("test","testuser","testpass");
  CustomerInfoDao customer_db("test","testuser","testpass");
  char menu;
  std::cout<<"MENU\n";
  std::cout<<"a. register your account\n";
  std::cout<<"b. login\n";
  std::cout<<"c. change password\n";
  std::cout<<"d. change login\n";
  std::cout<<"e. put customerinfo\n";
  std::cout<<"f. fetch customerinfo\n";
  std::cout<<"Enter a menu char: ";
  std::cin>> menu;
  std::string NAME;
  std::string PASS;
  switch(menu){
    case 'a':{
                std::cout<< "Enter new login ID: ";
                std::cin>> NAME;
                PASS=getpass("Enter new password: ");
                std::string salt;
                salt=myhash::genSalt();
                std::string hashed_pass;
                hashed_pass=myhash::mySha256(PASS+salt);
                char con_type;
                std::cout<< "Customer of Vender (please enter 'c' or 'v'): ";
                std::cin>> con_type;
                if(con_type=='c')
                  login_db.put(NAME,hashed_pass,salt, CUSTOMER);
                else
                  login_db.put(NAME,hashed_pass,salt, VENDER);
                break;
             }
    case 'b':{
                std::cout<< "Enter your login ID: ";
                std::cin>> NAME;
                LoginInfo info_from_db;
                if(!login_db.fetch(NAME, info_from_db)){
                  break;
                }
                PASS=getpass("Enter your password: ");
                std::string hashed_in_pass;
                hashed_in_pass = myhash::mySha256(PASS+info_from_db.salt);
                if(hashed_in_pass == info_from_db.hashed_pass){
                  std::cout<<"Hello, "<<info_from_db.login<<"!"<<std::endl;
                  std::cout<<"You are ";
                  info_from_db.user_type == CUSTOMER ? (std::cout<<"a customer."<<std::endl) : (std::cout<<"a vender."<<std::endl);
                }
                else{
                  std::cerr<<"invalid password\n";
                }
                break;
             }
    case 'c':{
                std::cout<< "Enter your login ID: ";
                std::cin>> NAME;
                PASS=getpass("Enter new password: ");
                std::string new_salt;
                new_salt=myhash::genSalt();
                std::string hashed_new_pass;
                hashed_new_pass=myhash::mySha256(PASS+new_salt);
                login_db.update_pass(NAME,hashed_new_pass,new_salt);
                break;
             }
    case 'd':{
                std::cout<< "Enter your login ID: ";
                std::cin>> NAME;
                std::string new_login;
                std::cout<< "Enter new login ID: ";
                std::cin>> new_login;
                login_db.update_login(NAME,new_login);
                break;
             }
    case 'e':{
               std::cout<<"Enter your l_id: ";
               int l_id;
               std::cin>> l_id;
               std::cout<<"Enter your first name: ";
               std::string first_name;
               std::cin>> first_name;
               std::cout<<"Enter your last name: ";
               std::string last_name;
               std::cin>> last_name;
               std::cout<<"Enter your birthday\nMonth(1-12): ";
               std::string birthday;
               int mon;
               std::cin>> mon;
               std::cout<<"Day(1-31): ";
               int day;
               std::cin>> day;
               std::cout<<"Year: ";
               int year;
               std::cin>> year;
               birthday=std::to_string(year)+"-"+std::to_string(mon)+"-"+std::to_string(day);
               std::cout<<"Enter your phone number: ";
               unsigned int phone_num;
               std::cin>> phone_num;
               std::cout<<"Enter your e mail addres: ";
               std::string e_mail_addr;
               std::cin>> e_mail_addr;

               std::cout<<"Registering\n";

               customer_db.put(l_id,last_name,first_name,birthday,phone_num,e_mail_addr);
               std::cout<<"ok\n";
               break;
             }
    case 'f':{
               std::cout<<"Enter your longin id: ";
               int l_id;
               std::cin>> l_id;
               CustomerInfo c_info;
               customer_db.fetch(l_id, c_info);
               std::cout<<c_info.c_id<<c_info.last_name<<c_info.first_name<<c_info.birthday<<c_info.phone_num<<c_info.e_mail_addr<<std::endl;
             }
   default:
      break;
  }
  return 0;
}
*/

