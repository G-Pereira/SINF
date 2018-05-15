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
  void Insert(string table, string fields, string values);

private:
  string user = "";
  string password = "";
};


#endif //SINF_DATABASE_H
