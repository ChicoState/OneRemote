
#ifndef ROOMS_H
#define ROOMS_H

class Room {
	public:
		Room() : next(nullptr), prev(nullptr), num_devices(0) {};
		Room(char* name) : next(nullptr), prev(nullptr), rname(name) {};
		Room(char* name,Room* next) : next(next), prev(nullptr),rname(name), num_devices(0) {};
		Room* next;
		Room* prev;
		char* rname;
		char* get_name();
		bool addDevicetoRoom(char* name);
		bool device_check(char* name);
	private:
		//char* rname;
		char* devices[100];
		int num_devices;
		

};

#endif
