struct details
{
	char *name;
	char *address;
	char *number;
};

typedef struct details details_tuple;


bool is_name(char* str)
{
	/*
	: str    = The name entered by the user.
	: return = true or false.
	*/

	for (size_t i = 0; i < strlen(str); i++)
	{
		if ((str[i] > 'Z' || str[i] < 'A') && (str[i] > 'z' || str[i] < 'a') && (str[i] != ' '))
		{
			return false;
		}
	}

	return true;
}

bool is_phone_no(char *phone_no)
{
	/*
	: phone_no  = the phone number.
	: return    = true or false.
	*/
	int len = strlen(phone_no);
	int flag = 0;
	if (len == 10)
	{
		for (int current_char = 0; current_char < len; current_char++)
		{
			if (phone_no[current_char] <= '9' && phone_no[current_char] >= '0')
			{
				continue;
			}
			else
			{
				flag = 1;
				break;
			}
		}
	}
	if (!flag) return true;
	else return false;
}

char* capitalize(char *str)
{
	/*
	: str    = The input string.
	: return = The capitalized string.
	*/

	char *res = (char*)calloc(100, sizeof(char));

	for (size_t i = 0; i < strlen(str); i++)
	{
		if (i == 0 && (str[0] <= 'z' && str[0] >= 'a'))
		{
			res[i] = str[i] - abs('A' - 'a');
		}
		else
		{
			res[i] = str[i];
		}
	}

	return res;
}

bool check_special_chars(char c)
{
	char *special_chars = "~`!@#$%^*()_+=?><;\"'{}[]\\|";
	for (size_t i = 0; i < strlen(special_chars); i++)
	{
		if (c == special_chars[i])
		{
			return true;
		}
	}
	return false;
}

bool is_address(char* address)
{
	/*
	: str    = The address entered by the user.
	: return = true or false.
	*/

	for (size_t i = 0; i < strlen(address); i++)
	{
		if ((address[i] > 'Z' || address[i] < 'A') && (address[i] > 'z' || address[i] < 'a') && (address[i] != ' ') && (address[i] != '\\'))
		{
			return false;
		}
	}
	return true;
}

char* to_lower(char* str)
{
	/*
	: str    = an input string.
	: return = the string passed with all small letters.
	*/

	char * res = (char*)calloc(strlen(str), sizeof(char));

	size_t i = 0;

	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			res[i] = str[i] + abs('A' - 'a');
		}
		else
		{
			res[i] = str[i];
		}
	}

	res[i] = '\0';

	return res;
}

int check_file(char  *filename)
{
	/*
	Checks if the file is a csv file or txt file or not.
	Also the file must contains the data in comma seperated values
	params:
	filename: name of the file from which contacts are to be imported
	returns:
	csv or not:bool (0/1)
	*/
	if (!(strstr(filename, ".csv") || strstr(filename, ".txt")))
		return 0;
	else
		return 1;
}

FILE *open_file(char *filename)
{
	/*
	Opens a contacts file by checking it's type.
	params:
	filename: a string for denoting the filename
	returns:
	file pointer to the file specified by the filename
	*/
	if (!check_file(filename))
		return NULL;
	FILE *csv_file = fopen(filename, "r");
	if (filename)
		return csv_file;
	else
		return NULL;
}

int is_valid_csv(FILE *contacts_file)
{
	/*
	Checks the columns in the csv/txt file for validness.
	Columns must be name, number and address.
	params:
	contacts_file: a file pointer to the contacts csv/txt file
	*/
	char *columns = (char *)calloc(1024, sizeof(char));
	fgets(columns, 1024, contacts_file);
	if (strcmp("name", to_lower(strtok(columns, ","))) != 0)
		return 0;
	if (strcmp("number", to_lower(strtok(NULL, ","))) != 0)
		return 0;
	if (strcmp("address\n", to_lower(strtok(NULL, ","))) != 0)
		return 0;
	return 1;
}

details_tuple parse_details(char *contact_details)
{
	/*
	Gets the details i.e., name, number and address from a single string.
	params:
	contact_details: a single string which contains values in the form of name, number and address.
	returns:
	tuple: a structure that stores name, number and address.
	*/
	char *token = (char *)calloc(1024, sizeof(char));
	details_tuple tuple;
	token = strtok(contact_details, ",");
	tuple.name = token;
	token = strtok(NULL, ",");
	tuple.number = token;
	token = strtok(NULL, ",");
	sscanf(token, "%[^\n]s", token);
	tuple.address = token;
	return tuple;
}

bool add_contact(char *name, char *number, char *address)
{
	if (is_name(name) && is_phone_no(number) && is_address(address))
	{
		load_data(name, address, number);
		return true;
	}
	return false;
}

int export_contacts(char * file_name)
{
	/*
	Read contacts from the file and write them to db.
	params:
	contacts_file: a file pointer to the file
	returns:
	count: number of contacts that have been written to db.
	*/
	FILE *contacts_file = open_file(file_name);
	if (contacts_file == NULL)
		return false;

	if (!is_valid_csv(contacts_file))
		return 0;
	char *contact_details = (char *)calloc(1024, sizeof(char));
	int count = 0;
	while (fgets(contact_details, 1024, contacts_file))
	{
		details_tuple tuple = parse_details(contact_details);
		add_contact(tuple.name, tuple.number, tuple.address);
		count++;
	}
	return count;
}

bool balance_check(char *number, int amount)
{
	/*
	Checks  the curernt balance of the user to check if the user is eligible for transaction.
	params:
	number: mobile no. of the user
	amount: expected value for amount to transfer
	returns:
	valid transaction or not: bool (0/1)
	*/
	double current_balance = get_money(number);
	if (amount < current_balance)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int add_money(char *number, double amount)
{
	/*
	Adds money to a user's wallet.
	params:
	number: phone number of the user
	amount: the amount of money that is to be added
	returns:
	added or not: bool (0/1)
	*/
	if (amount <= 0)
		return 0;
	edit_amount(number, amount);
	return 1;
}

int send_money(char *from_number, char *to_number, double amount)
{
	/*
	: return      = -1/-2/1 (low-balance / numbers are not valid / successful)
	*/
	if (amount <= 0)
		return -1;
	if (!(search_number(from_number) && (search_number(from_number))))
		return -2;
	debit_amount(from_number, amount);
	credit_amount(to_number, amount);
	return 1;
}

char *fetch_details_by_number(char *number)
{
	/*
	Gets the details of a contact by number, provided
	*/
	if (!is_phone_no(number))
		return NULL;
	else
	{
		int index = search_number(number);
		return db[index]->name;
	}
}

char *fetch_details_by_name(char* name)
{
	if (!is_name(name))
		return NULL;
	else
	{
		int index = search_name(name);
		return db[index]->phone_no;
	}
}

bool edit_profile_status(char *number, int status)
{
	/*
	: number = The phone number.
	: status = private/public (0/1).
	: return = successfull/not-successfull (true/false).
	*/

	if (is_phone_no(number) && (status == 1 || status == 0))
	{
		bool current_status = is_private(number);

		if (current_status != (bool)status)
		{
			if (status == 0)
			{
				make_private(number);
			}
			else
			{
				make_public(number);
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool edit_spam_status(char *number, bool spam_status)
{
	/*
	: number      = The phone number.
	: spam_status = spam/not-spam. (+1/ -1)
	: return      = successfull/not-successful (1/0)
	*/

	if (is_phone_no(number) && ((int)spam_status == 1 || spam_status == -1))
	{
		bool number_present = search_number(number);
		if (number_present)
		{
			int current_spam_count = get_spam_count(number);
			if (spam_status == 0 && current_spam_count != 0)
			{
				int updated_spam_count = current_spam_count + -1;
				if (updated_spam_count == 9)
				{
					set_spam_status(number, false);
				}
			}
			else
			{
				int updated_spam_count = current_spam_count + 1;
				if (updated_spam_count >= 10)
				{
					set_spam_status(number, true);
				}
			}
			return true;
		}
	}
	return false;
}

bool edit_address(char *number, char* addr)
{
	/*
	: number = the phone number.
	: addr   = the new address string.
	: return = successfull/not-successfull (true/false).
	*/

	if (is_phone_no(number) && is_address(addr))
	{
		update_address(addr, number);
	}
	else
	{
		return false;
	}
	return true;
}

bool edit_name(char *number, char* name)
{
	/*
	: number = The phone number.
	: name   = The new name.
	: return = successfull/not-successfull (true/false).
	*/

	if (is_phone_no(number) && is_name(name))
	{
		update_name(name, number);
	}
	else
	{
		return false;
	}
	return true;
}

int get_balance(char * number)
{
	if (!is_phone_no(number))
		return 0;
	
	int res = search_number(number);
	if (res == -1)
		return 0;

	return get_money(number);

}