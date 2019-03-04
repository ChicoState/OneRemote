#include <IRrecv.h>

#ifndef DEVICE_H
#define DEVICE_H


class Device {
	public:
		Device() : but_head(nullptr), next(nullptr), prev(nullptr) {};
		Device(char* name,Device* n, Device* p) : dname(name), next(n), prev(p), but_head(nullptr) {};
		void add_button(char* name,decode_results res);
		char* get_name();
		decode_results findButton(char* name);
		Device* next;
		Device* prev;
	private:
		class Button {
			public:
				Button() : next(nullptr), prev(nullptr) {};
				Button(char* name, decode_results res, Button* n, Button* p) : bname(name), results(res), next(n), prev(p) {};
				char* bname;
				decode_results results;
				Button* next;
				Button* prev;
		};
		Button* but_list;
		char* dname;

};


class Dlist {
	public:
		Dlist() : dev_head(nullptr) {};
		void addDevice(char* name);
		Device* findDevice(char* name);
	private:
		Device* dev_head;

};





#endif
