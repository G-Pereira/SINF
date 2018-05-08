//
// Created by gpereira on 4/29/18.
//

#include "Mote.h"
#include "Database.h"

int Mote::CheckRoom(int m_id) {
  Database db;
  return stoi(db.Query("SELECT * FROM homeauto.mote WHERE mote_id=" + m_id)[0][1]);
}
