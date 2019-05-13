#include "../src/IRrecv.h"
#include "rooms.h"
#include <stdio.h>

#ifndef DEVICE_H
#define DEVICE_H


class Device {
	public:
		Device() : next(nullptr), prev(nullptr),but_head(nullptr) {};
		Device(char* name,decode_results* dec, Device* n, Device* p) : next(n), prev(p), but_head(new Button("Power",dec)),dname(name) {};
		bool add_button(char* name,decode_results res);
		bool searchButton(char *name);
		char* get_name();
		decode_results findButton(char* name);
		Device* next;
		Device* prev;
		class Button {
			public:
				Button() : next(nullptr), prev(nullptr) {};
				//constructor for name 
				Button(char *name, decode_results *result){
					bname = name;
					results = *result; 
					next = nullptr;
					prev = nullptr;
					}
				Button(char* name, decode_results res, Button* n, Button* p) : bname(name), results(res), next(n), prev(p) {};
				char* bname;

				decode_results results;
				Button* next;
				Button* prev;
		};
	public:
		Device(char *name,decode_results* dec){
			but_head= new Button("Power",dec);
			dname =name; 
			next = nullptr;
			prev = nullptr;
			}
	private: 
		Button* but_head;
		char* dname;

};


class Dlist {
	public:
		Dlist() : dev_head(nullptr), room_head(nullptr) {};
		bool addDevice(char* name, decode_results *res);
		Device* findDevice(char* name);
		bool searchDevice(char *name);
		bool searchRoom(char *name);
		bool addRoom(char* name);
		bool addQA(char* dev, int spot = -1);
	private:
		Device* dev_head;
		Room* room_head; //points to list of rooms
		char* quickAccess[3];

};





#endif
