//
// Created by gpereira on 4/29/18.
//

#include "Mote.h"
#include "Database.h"

int Mote::CheckRoom(int m_id) {
  Database db;
  return stoi(db.Select("mote", "id = " + to_string(m_id))[0][1]);
}
