typedef struct db_node{
	char* name;
	char* address;
	char* phone_no;
	double amount;
	int is_private_account;
	int spam_count;
	int is_spam;
}phone_record;

int size = 4;
int curr_index = 0;
phone_record** db = (phone_record**)malloc(4 * sizeof(phone_record*));

int search_by_number(char *p)
{

	if (curr_index == 0)
	{
		struct num* node1 = (struct num*)malloc(sizeof(struct num));
		node1->count = 0;
		node1->end = 0;
		node1->index = -1;
		for (int i = 0; i < 10; i++)
			node1->next[i] = NULL;
		root_num = node1;

	}
	return search_number(p);
}

int search_by_name(char *p)
{
	return search_name(p);
}

void realloc_structure(){

	phone_record** temp = (phone_record**)malloc((size + 5) * sizeof(phone_record*));

	for (int i = 0; i < curr_index; i++){


		temp[i] = db[i];
	}
	size = size + 5;
	free(db);
	db = temp;

}


void load_data(char* name, char* address, char* phone_no){
	if (search_by_number(phone_no) == -1){


		phone_record* record = (phone_record*)malloc(sizeof(phone_record));


		if (size - 1 == curr_index)
			realloc_structure();

		record->name = (char*)malloc(50 * sizeof(char));
		record->phone_no = (char*)malloc(15 * sizeof(char));
		record->address = (char*)malloc(75 * sizeof(char));

		strcpy(record->name, name);
		strcpy(record->phone_no, phone_no);
		strcpy(record->address, address);

		record->is_private_account = 0;
		record->is_spam = 0;
		record->spam_count = 0;
		record->amount = 0;

		db[curr_index] = record;

		if (curr_index == 0)
		{
			struct node* node1 = (struct node*)malloc(sizeof(struct node));
			node1->count = 0;
			node1->end = 0;
			node1->index = -1;
			for (int i = 0; i<26; i++)
				node1->next[i] = NULL;
			root = node1;
		}
		add_number(phone_no, curr_index);
		add_name(name, curr_index);
		curr_index++;
	}
	return;
}

bool update_name(char* name, char* phone_no){


	int index = search_by_number(phone_no);
	printf("\n%d", index);

	if (index != -1){


		strcpy(db[index]->name, name);
		return true;

	}
	return false;

}


bool update_address(char* address, char* phone_no){


	int index = search_by_number(phone_no);

	if (index != -1){


		strcpy(db[index]->address, address);
		return true;

	}
	return false;

}

bool get_spam_status(char* phone_no){


	int index = search_by_number(phone_no);

	if (index != -1){


		if (db[index]->is_spam)
			return true;

		return false;
	}

	return false;
}

void set_spam_status(char* phone_no, bool flag){

	int index = search_by_number(phone_no);

	if (index != -1){

		db[index]->is_spam = flag ? 1 : 0;
	}
}

int get_spam_count(char* phone_no){


	int index = search_by_number(phone_no);

	if (index != -1){

		return db[index]->spam_count;

	}

	return -1;
}

bool is_private(char* phone_no){

	int index = search_by_number(phone_no);

	if (index != -1){


		if (db[index]->is_private_account)
			return true;

		return false;
	}

	return false;
}

void make_private(char* phone_no){

	int index = search_by_number(phone_no);

	if (index != -1){

		db[index]->is_private_account = 1;

	}

}

void make_public(char* phone_no){

	int index = search_by_number(phone_no);

	if (index != -1){

		db[index]->is_private_account = 0;

	}
}



double get_money(char* phone_no){


	int index = search_by_number(phone_no);

	if (index != -1){

		return db[index]->amount;

	}
	return -1;
}

void set_money(char* phone_no, double amount){

	int index = search_by_number(phone_no);

	if (index != -1){

		db[index]->amount = amount;

	}

}

void save_file(){

	FILE* file = fopen("final.txt", "w");

	for (int i = 0; i <curr_index; i++)
		fprintf(file, "%s,%s,%s,%g,%d,%d,%d\n", db[i]->name, db[i]->phone_no, db[i]->address, db[i]->amount, db[i]->is_private_account, db[i]->is_spam, db[i]->spam_count);

	fclose(file);
}


