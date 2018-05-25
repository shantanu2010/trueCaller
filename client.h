#define NAME_SIZE 50
#define ADDRESS_SIZE 100
#define FILE_NAME_SIZE 50

void add_contact()
{
	char * name = (char*)calloc(50, sizeof(char));
	char * phone_no = (char*)calloc(15, sizeof(char));
	char * address = (char*)calloc(500, sizeof(char));
	printf(" Name     : ");
	scanf("%s", name);
	fflush(stdin);
	printf(" Phone no : ");
	scanf("%s", phone_no);
	fflush(stdin);
	printf(" Address  : ");
	scanf("%[^\n]s", address);
	fflush(stdin);
	int res = add_contact(name, phone_no, address);
	if (res == 1)
		printf("Successful.\n");
	else
		printf("unSuccessful.\n");
	return;
}

void report_spam()
{
	char * number = (char*)calloc(50, sizeof(char));
	printf(" Phone no : ");
	scanf("%s", number);
	bool res = edit_spam_status(number, 1);
	if (res == true)
	{
		printf("Successful.\n");
	}
	else
	{
		printf("Unsuccessful.\n");
	}
	return;
}

void export_contacts_from_file()
{
	char *file_name = (char*)calloc(100, sizeof(char));
	printf("File Name : ");
	scanf("%s", file_name); 
	fflush(stdin);
	int res = export_contacts(file_name);
	if (res == 0)
	{
		printf("Unsuccessful.\n");
	}
	else
	{
		printf("Successful.\n");
		printf(" %d records created.\n", res);
	}
	return;
}

void money_transfer()
{
	char *from = (char*)calloc(15, sizeof(char));
	char *to = (char*)calloc(15, sizeof(char));
	double amount = 0;

	printf("Source number      : ");
	scanf("%s", from);
	printf("Destination number : ");
	scanf("%s", to);
	printf("Amount             : ");
	scanf("%lf", &amount);

	int res = send_money(from, to, amount);
	if (res == false)
	{
		printf("Unsuccessful.\n");
	}
	else
	{
		printf("%lf transfered from %s to %s.\n", amount, from, to);
		printf("Successful.\n");
	}
	return;
}

void report_balance()
{
	char *no = (char*)calloc(15, sizeof(char));
	printf("Phone number : ");
	scanf("%s", no);
	double res = get_balance(no);
	if (res == -1)
	{
		printf("Unsuccessful.\n");
	}
	else
	{
		printf("Balance = %lf\n", res);
	}
	return;
}

void add_money_to_account()
{
	char *number = (char*)calloc(15, sizeof(char));
	double amount = 0;
	printf("Number : ");
	scanf("%s", number);
	printf("Amount : ");
	scanf("%lf", &amount);
	int res = add_money(number, amount);
	if (res == 0)
	{
		printf("Unsuccessful.\n");
	}
	else
	{
		printf("Successful.\n");
	}
}

void set_number_private()
{
	char *no = (char*)calloc(15, sizeof(char));
	printf("Phone number : ");
	scanf("%s", no);
	
	if (edit_profile_status(no, 0))
	{
		printf("Successful.\n");
	}
	else
	{
		printf("Unsuccesful.\n");
	}
	return;
}

int driver(){
	int option = -1;
	int num;
	char* temp = (char*)malloc(50 * sizeof(char));
	while (1){
		printf("\t 1. Add new contact.\n");
		printf("\t 2. Mark spam.\n");
		printf("\t 3. Export contacts from a file.\n");
		printf("\t 4. Transfer Amount.\n");
		printf("\t 5. Get balance.\n");
		printf("\t 6. Add money to account.\n");
		printf("\t 7. Set private status.\n");
		printf("\t 8.Search a Number.\n");
		printf("\t 9.Update Name.\n");
		printf("\nEnter your choice : ");
		scanf("%d", &option);
		switch (option)
		{
		case 1: //Inserting a single contact.
			add_contact();
			break;
		case 2: //report spam.
			report_spam();
			break;
		case 3: //export contackts.
			export_contacts_from_file();
			break;
		case 4: // transfer ammount.
			money_transfer();
			break;
		case 5: // print balance.
			report_balance();
			break;
		case 6: // add money
			add_money_to_account();
			break;
		case 7: //set number private
			set_number_private();
			break;
		case 8:
			printf("\nEnter The Number : ");
			scanf(" %s", temp);
			num = search_by_number(temp);
			if (num != -1){

				printf("\nNumber belongs to %s\n", db[num]->name);
			}
			else{

				printf("\nNumber doesnot exists\n");
			}
			break;
		case 9:
			
			printf("\nEnter The Number : ");
			scanf(" %s", temp);
			num = search_by_number(temp);
			if (num != -1){

				printf("\nEnter the new name : ");
				scanf(" %s", temp);
				strcpy(db[num]->name, temp);
				printf("\nNumber Changed\n");
			}
			else{

				printf("\nNumber doesnot exists\n");
			}
			break;

		default: printf("Recheck the query!!\n");
		}
	}

	free(temp);
	return 0;
}