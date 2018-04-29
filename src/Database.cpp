#include <libpq-fe.h>
#include "Database.h"

int Database::Connect() {
  PGconn *dbconn;
  dbconn = PQconnectdb(("host='db.fe.up.pt' user='"+ this->user +"' password='"+ this->password +"'").c_str());
}

Database::Database(const std::string user, const std::string password) {
  this->user = user;
  this->password = password;
  Connect();
}
