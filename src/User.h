//
// Created by gpereira on 4/30/18.
//

#ifndef SINF_USER_H
#define SINF_USER_H


#include <string>
#include <postgresql/libpq-fe.h>

class User {
public:
    std::string username;
    std::string password;
    int permission;

    bool auth(std::string username, std::string password);

private:

};

#endif //SINF_USER_H
