#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 
#include "songList.h"
#include "song.h"
#include "dllNode.h"
#include "heap.h"
#include "vectorTitle.h"




int main()
{
    std::string command;
    std::string root;
    int ip1;
    int ip2;
    std::string sp1;
    std::string sp2;
    songList idSort;
    heap listenSort; 
    vectorTitle titleSort;

    while(getline(std::cin, command))
    {
        root = "";
        sp1 = "";
        sp2 = "";
        ip1 = -1;
        ip2 = -1;
        std::stringstream s(command);
        s >> root;
        //exit progrm
        if(root == "quit")
        {
            break;
        }
        //add new song to lists
        else if(root == "song")
        {
            //song <id> <artist> <duration> <title>
            s >> ip1;
            s >> std::quoted(sp1);
            s >> ip2;
            s >> std::quoted(sp2);
            if(ip1 != -1 && sp1 != "" && ip2 != -1 && sp2 != "")
            {
                //create new song pointer and add it to appropriate lists
                song* temp = new song(ip1, sp1, ip2, sp2);
                
                //checks for duplicate ids
                song* dup = idSort.findById(ip1);
                if(dup != nullptr) {
                    std::cout << "song id " << ip1 << " already used for " << dup->title << " by " << dup->artist << std::endl;
                    delete temp;
                }            
                else {        
                    idSort.insert(temp);
                    titleSort.insert(temp);
                    listenSort.insert(temp);
                    std::cout << "new song " << ip1 << " " << sp2 << " by " << sp1 << " " << temp->minutes << ":" << std::setfill('0') << std::setw(2) << temp->seconds << std::endl;
                }
            }
            else
            {
                std::cout << "Improper syntax: should be\n" << root << " <id> <artist> <duration> <title>" << std::endl;
            }
        }
        //remove songs from lists
        else if(root == "remove")
        {
            s >> std::quoted(sp1);
            if(sp1 != "")
            {
                //returns song* for heap and dll removal and removes from vector
                song* found = titleSort.remove(sp1);
                if(found == nullptr) continue;
                listenSort.remove(found);
                idSort.remove(found);
                std::cout << "Removed song " << found->id << " " << found->title << " from your songs" << std::endl;
                delete found;

            }
            else
            {
                std::cout << "Improper syntax: should be\n" << root << " <title>" << std::endl;
            }
        }
        //print songs sorted by id and display listen time
        else if(root == "show_listen_time")
        {
            idSort.print();
        }
        
        //adds the song with most listening time to favorites 
        else if(root == "favorite") {
            song* top = listenSort.getMax();
            if(top == nullptr)
            {
                std::cout << "No songs available to favorite." << std::endl;
            }
            else
            {
                listenSort.remove(top);
                top->fav = true;
                std::cout << "Song " << top->title << " added to list of favorites (Listened for " << top->time << " seconds)" << std::endl;
            }
        }

	//increments the seconds a song is listened to; nothing if it is on the favorites list
	else if (root == "listen") {
	  
	  int secs;

	  s >> std::quoted(sp1);
	  s >> secs;

	  if (sp1 != "") {

	    song* incremented = titleSort.listen(sp1, secs);

	    if (incremented != nullptr && !incremented->fav) {

	      listenSort.remove(incremented);
	      listenSort.insert(incremented);

	    }

	    else if (incremented == nullptr) {

	      std::cout << "Song not found!" << std::endl;

	    }
	    
	  }

	  else {

	    std::cout <<  "Improper syntax: should be\n" << root << " <title> <seconds>" << std::endl;
	    
	  }

	}
				 
	

        else
        {
            std::cout << "Unknown command, check README for help" << std::endl;
        }
    }
}
