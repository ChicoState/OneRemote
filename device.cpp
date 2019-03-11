#include <device.h>


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
 */`
bool Dlist::addDevice(char* name)
{
	if(findDevice(name) == nullptr)
	{
		if(dev_head == nullptr)
		{
			dev_head = new Device(name,nullptr,nullptr);
		}	
		else
		{
			dev_head->prev = new Device(name,dev_head,nullptr);
			dev_head = dev_head->prev;
		}
		return true;
	}
	return false;
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
	Button* cur = but_head;

	while(cur != nullptr)
	{
		if(name == cur->bname)
		{
			return cur->results;
		}
		cur = cur->next;
	}
	return nullptr; /* CHANGE and CHANGE DESCRIPTION*/

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
 */`
bool Device::add_button(char* name, decode_results res)
{
	if(findButton(name) == nullptr) /*POSSIBLY CHANGE */
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







