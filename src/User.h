//
// Created by gpereira on 4/30/18.
//

#ifndef SINF_USER_H
#define SINF_USER_H

#include <string>

class User {
public:
  std::string username;
  std::string password;
  int permission;

  User(std::string username, std::string password);

private:

};

#endif //SINF_USER_H
