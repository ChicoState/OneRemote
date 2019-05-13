#include "device.h"
#include "rooms.h"


/*
 * Dlist::findDevice
 *
 * This function searches through the list of devices that have been added and
 * compares each name with the name provided. If a match is found, the pointer
 * to the Device is return. If there is no match, nullptr is returned.
 *
 * @param name: name of Device looking for
 *
 * @Return: Pointer to Device in list or nullptr if not there
 *
 */
Device* Dlist::findDevice(char* name)
{
	Device* cur = dev_head;

	while(cur != nullptr)
	{
		if(name == cur->get_name())
		{
			return cur;
		}
		cur = cur->next;
	}
	return nullptr;

}
/**
 *DList::searchDevice
 *
 *This function locates if a device exists in the list or not. 
 *
 *Name to search for
 **/
bool Dlist::searchDevice(char * name){
	Device * dev = dev_head;
	
	while(dev != nullptr)
	{
		if(name == dev->get_name())
		{
			return true;
		}
		dev = dev->next;
	}
	return false;

}

/*
 * Dlist::addDevice
 *
 * This function adds a new device to the list of devices.
 * If there are no devices in the list, the device is just added in.
 * If the list is not empty then the device is added to the front of the list
 *
 * @param name: Name of the device being added
 *
 * @Return: True if button added successfully, False if button already exists
 *
 */
bool Dlist::addDevice(char* name, decode_results *res)
{
	if(searchDevice(name) == false)
	{
		if(dev_head == nullptr)
		{
			dev_head = new Device(name,res);
		}	
		else
		{
			dev_head->prev = new Device(name,res, dev_head,nullptr); // added 'res' as parameter
			dev_head = dev_head->prev;
		}
		return true;
	}
	return false;
}

/*
 * Dlist::searchRoom
 *
 * This function searches through the rooms already created checking if the room passed in 
 * already exists.
 *
 * @Param: name The name of the room searching for.
 *
 * @ Return: True if room exists, False if room doesn't exist
 */
bool Dlist::searchRoom(char* name)
{
	Room* temp = room_head;
	while(temp != nullptr)
	{
		if(temp->rname == name) //changed temp->get_name to temp->rname, moved name to public in rooms.h
			return true;
		temp = temp->next;
	}
	return false;
}

/*
 * Dlist::addRoom
 *
 * This function adds a room to the list of rooms.
 *
 * @Param: name The name of the room to be added.
 *
 * @Return: True if room successfully added, False if not added
 */
bool Dlist::addRoom(char* name)
{
	if(searchRoom(name) == false)
	{
		if(room_head == nullptr)
		{
			room_head = new Room(name);
		}
		else
		{
			room_head->prev = new Room(name,room_head);
			room_head = room_head->prev;
		}
		return true;
	}
	return false;
}

/*
 * Dlist::addQA
 *
 * This function adds/changes a device located in the quick access array/menu.
 *
 * @Param: dev The name of the device to be added to the quickAccess array/menu
 * @Param: spot The spot in the quickAccess array/menu to be swapped out.
 *
 * 
 */
bool Dlist::addQA(char* dev, int spot)
{
	switch(spot)
	{
		case 0:
		case 1:
		case 2:
			quickAccess[spot] = dev;
			break;
		default:
			return false;
	}
	return true;
}



/*
 * Device::get_name
 *
 * @Return: Name of device
 *
 */
char* Device::get_name()
{
	return dname;
}

/*
 * Device::findButton
 *
 * This function searches through the list of buttons that have been added and
 * compares each name with the name provided. If a match is found, the decoded
 * results are returned. If there is no match, nullptr is returned.
 *
 * @param name: name of Button looking for
 *
 * @Return: Decoded results of button or nullptr if not there
 *
 */
decode_results Device::findButton(char* name)
{
	//empty decode_results to allow for null return. 
	decode_results x; 

	Button* cur = but_head;

	while(cur != nullptr)
	{
		if(name == cur->bname)
		{
			return cur->results;
		}
		cur = cur->next;
	}
	return x; /* CHANGE and CHANGE DESCRIPTION*/

}
/**
 *
 *Device::SearchButton
 *
 *Taking the argument of a name, the function searches the list to find if the object exists. 
 **/
bool Device:: searchButton(char *name){
	Button * but =but_head;
	while(but!= nullptr){
		if(name == but->bname){
			return true;
			}
		but=but->next;
		}
	return false;
	}
/*
 * Device::add_button
 *
 * This function adds a new button to the list of buttons for the device.
 * If there are no buttons in the list, the button is just added in.
 * If the list is not empty then the button is added to the front of the list
 *
 * @param name: Name of the button being added
 * @param res: the decoded data for the button
 *
 * @Return: True if button successfully added, False if button already exists
 *
 */
bool Device::add_button(char* name, decode_results res)
{
	if(searchButton(name) == false) /*POSSIBLY CHANGE */
	{
		if(but_head == nullptr)
		{	
			but_head = new Button(name,res,nullptr,nullptr);
		}	
		else
		{
			but_head->prev = new Button(name,res,but_head,nullptr);
			but_head = but_head->prev;
		}
		return true;
	}
	return false;
}






