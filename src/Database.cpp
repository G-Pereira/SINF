#include <iostream>
#include "Database.h"

vector<vector<string>> Database::Select(string table, string filter) {
  string query = "SELECT * FROM homeauto." + table + " WHERE " + filter;
  connection C(
    "dbname = sinfa23 user = " + user + " password = " + password + " hostaddr = 192.168.50.131 port = 5432");
  vector<vector<string>> res;

  nontransaction N(C);

  result R(N.exec(query));

  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    vector<string> row;
    int i;
    for (i = 0; i < c.size(); i++) {
      row.push_back(c[i].as<string>());
    }
    res.push_back(row);
  }
  C.disconnect();
  return res;
}
