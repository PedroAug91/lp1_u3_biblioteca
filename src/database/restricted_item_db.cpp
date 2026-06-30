#include "../item/include/RestrictedItem.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

static const int NUM_DAYS = 5;
static const int NUM_SLOTS = 3;

static char visitStatusToChar(VisitStatus vs) {
  return static_cast<char>(vs);
}

static VisitStatus charToVisitStatus(char c) {
  switch (c) {
    case 'S': return VisitStatus::SCHEDULED;
    case 'U': return VisitStatus::UNAVAILABLE;
    default:  return VisitStatus::AVAILABLE;
  }
}

static void writeAppointments(std::ofstream &file, Visit appointments[5][3]) {
  for (int s = 0; s < NUM_SLOTS; ++s) {
    file << "appt=";
    for (int d = 0; d < NUM_DAYS; ++d) {
      file << visitStatusToChar(appointments[d][s].visitState);
    }
    file << "\n";
  }
  for (int d = 0; d < NUM_DAYS; ++d) {
    for (int s = 0; s < NUM_SLOTS; ++s) {
      if (appointments[d][s].visitState == VisitStatus::SCHEDULED) {
        file << "attendee_" << d << "_" << s << "="
             << appointments[d][s].attendeeName << ","
             << appointments[d][s].attendeeMatricula << "\n";
      }
    }
  }
}

static void readAppointmentLine(RestrictedItem *item, const std::string &value, int slotIdx) {
  for (int d = 0; d < NUM_DAYS && d < (int)value.size(); ++d) {
    item->AccessAppointments[d][slotIdx].visitState = charToVisitStatus(value[d]);
  }
}

bool RestrictedItem::create(Person *) {
  std::string path = "library_db/" + std::to_string(this->id) + ".rst";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  writeAppointments(file, AccessAppointments);
  return true;
}

bool RestrictedItem::read(std::string item_id) {
  std::string path = "library_db/" + item_id + ".rst";
  std::ifstream file(path);
  if (!file.is_open()) return false;
  int apptLine = 0;
  std::string line;
  while (std::getline(file, line)) {
    auto eq = line.find('=');
    if (eq == std::string::npos) continue;
    std::string key = line.substr(0, eq);
    std::string value = line.substr(eq + 1);
    if (key == "id") {
      id = std::stoul(value);
    } else if (key == "name") {
      name = value;
    } else if (key == "appt") {
      if (apptLine < NUM_SLOTS) {
        readAppointmentLine(this, value, apptLine);
        apptLine++;
      }
    } else if (key.rfind("attendee_", 0) == 0) {
      std::string rest = key.substr(9);
      auto us = rest.find('_');
      if (us != std::string::npos) {
        int d = std::stoi(rest.substr(0, us));
        int s = std::stoi(rest.substr(us + 1));
        if (d >= 0 && d < NUM_DAYS && s >= 0 && s < NUM_SLOTS) {
          auto comma = value.find(',');
          if (comma != std::string::npos) {
            AccessAppointments[d][s].attendeeName = value.substr(0, comma);
            AccessAppointments[d][s].attendeeMatricula = std::stoul(value.substr(comma + 1));
          }
        }
      }
    }
  }
  return true;
}

bool RestrictedItem::update(std::string item_id) {
  std::string path = "library_db/" + item_id + ".rst";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  writeAppointments(file, AccessAppointments);
  return true;
}

bool RestrictedItem::remove(std::string item_id) {
  std::string path = "library_db/" + item_id + ".rst";
  return std::remove(path.c_str()) == 0;
}
