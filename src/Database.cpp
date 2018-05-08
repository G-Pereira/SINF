#include <iostream>
#include "Database.h"

Database::Database() {
  dbconn = PQconnectdb(("host='db.fe.up.pt' user='" + user + "' password='" + password + "'").c_str());
  if (PQstatus(dbconn) == CONNECTION_BAD) {
    printf("Error Connecting to Database :(");
    exit(-1);
  }
  printf("Connection to database successful!");
}

Database::~Database() {
  PQfinish(dbconn);
}

std::vector<std::string> Database::QuerySingle(std::string query) {
  std::vector<std::string> result;
  PGresult *q = PQexec(dbconn, query.c_str());
  if (PQresultStatus(q) == PGRES_TUPLES_OK) {
    int nt = PQntuples(q);
    if (nt != 0) {
      int i;
      for (i = 0; i < nt; i++) {
        result[i] = PQgetvalue(q, i, 1);
      }
    }
  }
  PQclear(q);
  return result;
}

std::vector<std::vector<std::string>> Database::QueryMultiple(std::string query) {
  return std::vector<std::vector<std::string>>();
}
