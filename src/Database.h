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

  void Disconnect();

private:
  std::string user;
  std::string password;
  PGconn *dbconn;
};


#endif //SINF_DATABASE_H
