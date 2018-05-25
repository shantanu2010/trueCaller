int edit_amount(char *phone_no, double amount)
{
	int index = search_number(phone_no);
	if (index > -1)
	{
		set_money(phone_no, amount);
		return 1;
	}
	return 0;
}

int debit_amount(char *phone_no, double amount)
{
	int index = search_number(phone_no);
	if (index)
	{
		set_money(phone_no, amount);
		return 1;
	}
	return 0;
}

int credit_amount(char *phone_no, double amount)
{
	int index = search_number(phone_no);
	if (index)
	{
		set_money(phone_no, amount);
		return 1;
	}
	return 0;
}