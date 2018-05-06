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

char* Database::GetRow(int n){
  PGresult *res = PQexec(dbconn, "SELECT VERSION()");
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    printf("No data retrieved\n");
    PQclear(res);
    exit(-1);
  }
  return PQgetvalue(res, n, 0);   //linha -> n, coluna -> 0
}
