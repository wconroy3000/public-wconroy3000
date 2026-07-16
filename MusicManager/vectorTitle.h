#pragma once
#include <vector>
#include <string>
#include "song.h"

class vectorTitle {

 private:

  std::vector<song*> songTitles;

 public:

  void insert(song* newSong);
  song* listen(std::string title, int secs);
  song* remove(std::string title);

};
