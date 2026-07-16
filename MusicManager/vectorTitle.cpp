#include "vectorTitle.h"
#include <iostream>

void vectorTitle::insert(song* newSong) {

  if (newSong == nullptr) {

    return;

  }

  int insert = 0;
  int size = (int)songTitles.size();

  while (insert < size && songTitles[insert]->title < newSong->title) {
    
    insert++;
	
  }

  songTitles.resize(size + 1);

  for (int i = size; i > insert; i--) {

    songTitles[i] = songTitles[i - 1];
    
  }

  songTitles[insert] = newSong;

}

song* vectorTitle::listen(std::string title, int secs) {

  int low = 0;
  int high = (int)songTitles.size() - 1;
  song* found = nullptr;

  while (low <= high) {

    int mid = low + (high - low) / 2;

    if (songTitles[mid]->title == title) {

      found = songTitles[mid];
      break;

    }

    if (songTitles[mid]->title < title) {

      low = mid + 1;

    }

    else {

      high = mid - 1;

    }

  }

  if (found == nullptr) {

    return nullptr;

  }


  if (found->fav) {

    std::cout << "Song " << found->title << " is already a favorite." << std::endl;
    return found;

  }

  found->time += secs;

  std::cout << "Listened to " << found->title << " for " << secs << " seconds." << std::endl;

  return found;
  
}


song* vectorTitle::remove(std::string title) {
  int size = (int)songTitles.size();
  int target = -1;

  for (int i = 0; i < size; i++) {

    if (songTitles[i]->title == title) {

      target = i;
      break;

    }

  }

  if (target == -1) {
    std::cout << "Song " << title << " not found." << std::endl;
    return nullptr;

  }

  if (songTitles[target]->fav) {
    std::cout << "Error: Cannot remove favorited songs" << std::endl;
    return nullptr;
  }


  song* found = songTitles[target];

  for (int i = target; i < size - 1; i++) {

    songTitles[i] = songTitles[i + 1];
    
  }

  songTitles.resize(size - 1);

  return found;

}
