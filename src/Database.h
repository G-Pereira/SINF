#ifndef SINF_DATABASE_H
#define SINF_DATABASE_H

#include <libpq-fe.h>
#include <string>

class Database {
public:
  Database(std::string user, std::string password);

  void Connect();
  void Disconnect();

private:
  std::string user;
  std::string password;
  PGconn *dbconn;
};


#endif //SINF_DATABASE_H
