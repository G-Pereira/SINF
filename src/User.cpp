#include "User.h"
#include "Database.h"

User::User(std::string u, std::string p) {
  Database db;
  vector<string> result = db.Select("user", "username='" + u + "'")[0];
  if(p == result[1]){
    username = u;
    password = p;
    permission = stoi(result[2]);
  }
}
