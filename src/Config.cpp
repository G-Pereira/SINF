#include "Config.h"


bool Config::updateConfigs(User user, int room_id, std::string timestamp, int) {
  PGresult *query;
  query = PQexec(dbconn, "select * from people");


  return false;
}
