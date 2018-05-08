#ifndef SINF_DATABASE_H
#define SINF_DATABASE_H

#include <libpq-fe.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <string>

class Database {
public:
  Database();

  ~Database();

  std::vector<std::vector<std::string>> QueryMultiple(std::string query);

  std::vector<std::string> QuerySingle(std::string query);

private:
  std::string user = "sinfa23";
  std::string password = "eVrzWLCM";
  PGconn *dbconn;
};


#endif //SINF_DATABASE_H
