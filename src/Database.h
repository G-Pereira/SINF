#ifndef SINF_DATABASE_H
#define SINF_DATABASE_H

#include <postgresql/libpq-fe.h>
#include <string>
#include <cstdlib>

class Database {
public:
  Database(std::string user, std::string password);

  void Connect();
  void Disconnect();

    char* GetRow(int n);     //retorna o valor da linha n, nao sei se a linha e cada exemplo e as colunas sao os parametros, e facil de mudar


private:
  std::string user;
  std::string password;
  PGconn *dbconn;
};


#endif //SINF_DATABASE_H
