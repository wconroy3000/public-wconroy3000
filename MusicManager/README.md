Doubly Linked List (DLL)

Stores all songs sorted by song ID. Used exclusively for the show_listen_time command, which requires songs to be printed in ID order. Each node stores a pointer to the same Song object shared across all three structures. Insertion is O(N) since the list must maintain sorted order. Removal is O(1) because each Song object stores a direct pointer back to its own DLL node via myNode, eliminating the need to search the list.

Sorted Vector

Stores all songs sorted alphabetically by title. Used for title-based lookups in the listen and remove commands via binary search. Since the vector is always kept sorted, binary search runs in O(log N). Insertion maintains sorted order by shifting elements, which is O(N) — acceptable since song only requires O(N) overall.

Max Heap

Stores all non-favorited songs keyed by listen time, with the most-listened song always at the root (index 0). Used by the favorite command to find and promote the most-listened song in O(log N). Each Song object stores its current index in the heap via heapIndex, so arbitrary removal during listen and remove runs in O(log N) without needing to scan the heap.


How The Structures Work Together

All three structures store pointers to the same Song objects rather than copies. This means:


Updating a song's listen time anywhere updates it everywhere automatically
Cross-pointers (heapIndex and myNode) allow O(1) direct access to a song's position in the heap and DLL once it is found via the vector
The overall remove operation is O(log N): binary search in the vector finds the song in O(log N), then the heap and DLL both remove in O(log N) and O(1) respectively using the cross-pointers


Instructions:
quit: Exits the program.
song <songid> <artist> <duration> <title>: Adds a new song to the collection.
songid: A unique, non-negative integer.
artist: The name of the artist.
duration: The length of the song in seconds (integer).
title: The title of the song.
Note: If artist names or titles contain whitespace, enclose them in double quotes (e.g., "Taylor Swift").
remove <song-title>: Removes a song from the collection by its title.
listen <song-title> <seconds>: Records that the user has listened to the specified song for a set number of seconds.
Assumes all song titles are unique and seconds is a positive integer.
favorite: Promotes the song with the most accumulated listening time to your favorites list.
Once added to favorites, further listen updates for that song are ignored.
show_listen_time: Displays all songs in the collection, ordered by their unique songid, along with their total recorded listening times.
Usage Notes
Input command fields are delineated by spaces.
The program validates that songid and duration are integers.
The program prevents the use of duplicate songid values.
Duration is entered in seconds but displayed in minutes:seconds format.
