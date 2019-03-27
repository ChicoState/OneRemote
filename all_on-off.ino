



void all_on_off()
{
	Device* cur = dev_head;
	while(cur != nullptr)
	{
		send_sig(cur->get_name(), "Power");
		cur = cur->next;
	}


}
