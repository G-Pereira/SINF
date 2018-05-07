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

private:
  std::string user = "sinfa23";
  std::string password = "eVrzWLCM";
  PGconn *dbconn;
};


#endif //SINF_DATABASE_H
