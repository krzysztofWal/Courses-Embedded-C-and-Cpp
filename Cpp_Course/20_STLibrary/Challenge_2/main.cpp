// Section 20
// Challenge 2
//  Lists

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <fstream>

class Song {
    friend std::ostream &operator<<(std::ostream &os, const Song &s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
            : name{name}, artist{artist}, rating{rating} {}
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }
    
    bool operator<(const Song &rhs) const  {
        return this->name < rhs.name;
    }
    
    bool operator==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s) {
    os << std::setw(20) << std::left << s.name
       << std::setw(30) << std::left << s.artist
       << std::setw(2) << std::left << s.rating;
       return os;
}

void display_menu() {
    std::cout << "F - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
	std::cout << "M - Display menu one more time" << std::endl;
	std::cout << "Q - quit the programme" << std::endl;
    std::cout << "===============================================" << std::endl;
}
void play_current_song(const Song &song) {
    // This function should display 
    // Playing: followed by the song that is playing
    std::cout << "Now playing:" << std::endl << song << std::endl; 
	std::cout << std::endl;
//    std::cout << "You implement this function"<< std::endl;
}
std::string stringToUpper(std::string selection) {
	for (char &element : selection)
		element = toupper(element);
	return selection;
}

void handleFirstSong(std::list<Song> &playlist, std::list<Song>::iterator &current_song) {
	current_song = playlist.begin();
	play_current_song(*current_song);
}
void handleNextSong(std::list<Song> &playlist, std::list<Song>::iterator &current_song) {
	if (current_song == --playlist.end()) 
		current_song = playlist.begin();
	else 
		std::advance(current_song, 1);
	play_current_song(*current_song);
}
void handlePreviousSong(std::list<Song> &playlist, std::list<Song>::iterator &current_song){
	if (current_song == playlist.begin()) 
		current_song = --playlist.end();
	else 
		std::advance(current_song, -1);
	play_current_song(*current_song);
}
void handleAdd(std::list<Song> &playlist, std::list<Song>::iterator &current_song) {
	std::string title;
	std::string author;
	int rating{};
	std::string ratingEntry{};
	bool done{false};
	
	std::cout << "Enter the title: ";
	getline(std::cin, title);
			
	std::cout << "Enter the artist: ";
	getline(std::cin, author);

	std::cout << "Enter your rating (number between 1 and 10): ";
			
	do {
		std::cin.clear();
		std::cin >> ratingEntry;
		std::istringstream validator {ratingEntry};
		
		if (validator >> rating) {
			if (rating >= 1 && rating <= 10) {
				done = true;
			} else {
				std::cout << "Type in rating again: ";
			}
		} else {
			std::cout << "Type in rating again: ";
		}
			
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discards the things that may remain in the buffer
		} while (!done);
			
	playlist.insert(++current_song, {title, author, rating});
	std::advance(current_song, -1);
	std::cout << std::endl;
	play_current_song(*current_song);
}
void handleList(const std::list<Song> &playlist, const std::list<Song>::iterator &current_song) {
	for (const auto &song : playlist)
		std::cout << song << std::endl;
	std::cout << std::endl;
	play_current_song(*current_song);
}
void handleQuit() {
    std::cout << "Thanks for listening!" << std::endl;
}
void handleError() {
	std::cout << "Try to choose again" << std::endl << std::endl;
}
void readFromFile (std::list<Song> &playlist) {
	std::ifstream in_file;
	in_file.open("../playlist.txt");
	char c1{};
	std::string line;
	std::string name;
	std::string artist;
	std::string catchRating;
	int rating{};
	
	if (!in_file) {
		std::cerr << "Problem with opening of the file" << std::endl;
	}
	
	while (!in_file.eof()) {
		//"putting"" the line into a stringstream
		std::getline(in_file, line);
		std::istringstream ss {line};
		//"reading" from the stringstream
		while (c1 != ';') {
			ss.get(c1);
			if (c1 != ';')
				name += c1;
		}
		c1 = 'a';
		while (c1 != ';') {
			ss.get(c1);
			if (c1 != ';')
				artist += c1;
		}
		c1 = 'a';
		while (c1 != ';') {
			ss.get(c1);
			if (c1 != ';')
				catchRating += c1;
		}
		c1 = 'a';
				
		rating = std::stoi(catchRating,0,0);

		playlist.push_back({name,artist,rating});

		name.clear();
		artist.clear();
		catchRating.clear();
	}
	
	in_file.close();
}
void saveToFile (std::list<Song> &playlist) {
	std::ofstream out_file;
	out_file.open("../playlist.txt");
	
	if (!out_file) {
		std::cerr << "Problem opening the file" << std::endl;
	}
	
	for (const auto &song : playlist) {
		out_file << song.get_name() << ";" << song.get_artist() << ";" << song.get_rating() << ";" << std::endl;
	}
	
	out_file.close();
}

int main() {

	std::list<Song> playlist;
//    std::list<Song> playlist{
//            {"Fist Song",        "Drake",                      5},
//            {"Never Be The Same", "Camila Cabello",            5},
//            {"Pray For Me",       "The Weekend and K. Lamar",  4},
//            {"The Middle",        "Zed*d, Maren Morris & Grey", 5},
//            {"Wait",              "Maroone 5",                 4},
//            {"Last Song", "Imagine Dragons",				   3}          
//    };
  
	readFromFile(playlist);
	std::list<Song>::iterator current_song = playlist.begin();
	std::string selection{};

	display_menu();
	do {
		std::cout << "Enter a selection: ";
		getline(std::cin, selection);
		std::cout << std::endl;
		if (stringToUpper(selection) == "F") {
			handleFirstSong(playlist, current_song);			
		} else if (stringToUpper(selection) == "N") {
			handleNextSong(playlist, current_song);
		} else if (stringToUpper(selection) == "P") {
			handlePreviousSong(playlist, current_song);
		} else if (stringToUpper(selection) == "A") {
			handleAdd(playlist, current_song);
		} else if (stringToUpper(selection) == "L") {
			handleList(playlist, current_song);
		} else if (stringToUpper(selection) == "Q") {
			handleQuit();
		} else if (stringToUpper(selection) == "M") {
			display_menu();
		} else
			handleError();
	} while (stringToUpper(selection) != "Q");

	saveToFile(playlist);
    return 0;
}