#ifndef SINF_DATABASE_H
#define SINF_DATABASE_H

#include <libpq-fe.h>
#include <string>

class Database{
public:
  std::string user;
  std::string password;
  Database(std::string user, std::string password);

  int Connect();
};


#endif //SINF_DATABASE_H
