#include "Database.h"

Database::Database() {
  dbconn = PQconnectdb("host='db.fe.up.pt' user='sinfa23' password='eVrzWLCM'");
  if (PQstatus(dbconn) == CONNECTION_BAD) {
    printf("Error Connecting to Database :(");
    exit(-1);
  }
  printf("Connection to database successful!");
}

Database::~Database() {
  PQfinish(dbconn);
}
