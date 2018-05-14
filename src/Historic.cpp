//
// Created by gpereira on 4/30/18.
//

#include "Historic.h"
#include "Database.h"

void Historic::Submit() {
  Database db;
  db.Insert("historic", "mote_id, room_id, timestamp, temp, hum, lum, infra, ac, blinds, dehum, lights", to_string(mote_id)+", "+to_string(room_id)+", to_timestamp("+timestamp+"), "+to_string(temp)+", "+to_string(hum)+", "+to_string(lum)+", "+to_string(infra)+", "+to_string(ac)+", "+to_string(blinds)+", "+to_string(dehum)+", "+to_string(lights));
}
