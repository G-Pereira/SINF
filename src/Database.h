#ifndef SINF_DATABASE_H
#define SINF_DATABASE_H

#include <pqxx/pqxx>
#include <string>
#include <cstdlib>
#include <vector>
#include <string>

using namespace pqxx;
using namespace std;

class Database {
public:
  vector<vector<string>> Select(string table, string filter = "true");

private:
  string user = "sinfa23";
  string password = "eVrzWLCM";
};


#endif //SINF_DATABASE_H
