#include <fstream>
#include <iostream>
#include "Database.h"
#include "Data.h"
#include "Historic.h"
#include "Mote.h"

using namespace std;

void readData(std::string in);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Wrong usage!\nUsage: ./a.out /dev/pts/x /dev/pts/y\n");
    return 0;
  }
  printf("Welcome to HomeAuto!\nSystem Starting up...\n");
  std::ifstream fileIn;
  fileIn.open(argv[1]);
  char reading[100];

  while (1) {
    Historic hist;
    Mote mote;
    fileIn.getline(reading, 100);
    Data data(reading);
    std::string query = "SELECT id,name FROM homeauto.room WHERE name='BATH'";
    printf("%s", query);
    std::string user = "sinfa23";
    std::string password = "eVrzWLCM";
    PGconn *dbconn = PQconnectdb(("host='db.fe.up.pt' user='" + user + "' password='" + password + "'").c_str());
    if (PQstatus(dbconn) == CONNECTION_BAD) {
      printf("Error Connecting to Database :(");
      exit(-1);
    }
    std::vector<std::string> result;
    PGresult *q = PQexec(dbconn, query.c_str());
    if (PQresultStatus(q) == PGRES_TUPLES_OK) {
      //printf("%d\n", PQntuples(q));
      //printf("%s\n", PQgetvalue(q, PQntuples(q), 0));
    }


    PQclear(q);
    //Config conf(mote.CheckRoom(data.moteId));
    //printf("%f\n", conf.temp_max);
    // Get Configs
    // check if actuator exists
    //if so check config
    // define on/off accordinggly
  }

  fileIn.close();

  return 0;
}

