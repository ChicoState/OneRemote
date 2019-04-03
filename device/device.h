#include <IRrecv.h>

#ifndef DEVICE_H
#define DEVICE_H


class Device {
	public:
		Device() : but_head(nullptr), next(nullptr), prev(nullptr) {};
		Device(char* name,decode_results* dec, Device* n, Device* p) : dname(name),but_head(new Button("Power",dec)), next(n), prev(p) {};
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
		Dlist() : dev_head(nullptr) {};
		bool addDevice(char* name, decode_results *res);
		Device* findDevice(char* name);
		bool searchDevice(char *name);
	private:
		Device* dev_head;

};





#endif
