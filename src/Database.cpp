#include "Database.h"

void Database::Connect() {
  PGconn *dbconn;
  dbconn = PQconnectdb(("host='db.fe.up.pt' user='" + this->user + "' password='" + this->password + "'").c_str());
  if (PQstatus(dbconn) == CONNECTION_BAD) {
    printf("Error Connecting to Database :(");
    exit(-1);
  }
  printf("Connection to database successful!");
}

Database::Database(const std::string user, const std::string password) {
  this->user = user;
  this->password = password;
  Connect();
}
