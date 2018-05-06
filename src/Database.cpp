#include "Database.h"

void Database::Connect() {
  dbconn = PQconnectdb(("host='db.fe.up.pt' user='" + user + "' password='" + password + "'").c_str());
  if (PQstatus(dbconn) == CONNECTION_BAD) {
    printf("Error Connecting to Database :(");
    exit(-1);
  }
  printf("Connection to database successful!");
}

Database::Database(const std::string u, const std::string p) {
  user = u;
  password = p;
}

void Database::Disconnect() {
  PQfinish(dbconn);
}
