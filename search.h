struct num
{
	int count;
	int end;
	int index;
	struct num *next[10];
}*root_num;
typedef struct num num;

struct node
{
	int count;
	int end;
	int index;
	struct node *next[26];
}*root;
typedef struct node node;

void add_name(char *n, int ind)
{
	int i, j;
	node *temp = root;
	temp->count = temp->count + 1;
	temp->end = 0;
	temp->index = -1;
	int l = strlen(n);
	for (i = 0; i < l; i++)
	{
		if (temp->next[n[i] - 'a'] == NULL)
		{
			struct node* node1 = (struct node*)malloc(sizeof(struct node));
			node1->count = 0;
			node1->end = 0;
			node1->index = -1;
			for (j = 0; j < 26; j++)
				node1->next[j] = NULL;
			temp->next[n[i] - 'a'] = node1;
		}
		temp = temp->next[n[i] - 'a'];
		temp->count = temp->count + 1;
	}
	temp->end += 1;
	temp->index = ind;
}

int search_name(char *p)
{
	node *temp = root;
	int l = strlen(p);
	for (int i = 0; i < l; i++)
	{
		if (temp->next[p[i] - 'a'] == NULL)
			return -1;
		temp = temp->next[p[i] - 'a'];
	}
	//return temp->count;
	if (temp->end > 0)
	{
		return temp->index;
	}
	else
		return -1;
}

void add_number(char *n, int ind)
{
	int i, j;
	num *temp = root_num;
	temp->count++;
	temp->end = 0;
	temp->index = -1;
	int l = strlen(n);
	for (i = 0; i < l; i++)
	{
		if (temp->next[n[i] - '0'] == NULL)
		{
			struct num* node1 = (struct num*)malloc(sizeof(struct num));
			node1->count = 0;
			node1->end = 0;
			node1->index = -1;
			for (j = 0; j < 10; j++)
				node1->next[j] = NULL;
			temp->next[n[i] - '0'] = node1;
		}
		temp = temp->next[n[i] - '0'];
		temp->count = temp->count + 1;
	}
	temp->end += 1;
	temp->index = ind;
}

int search_number(char *p)
{
	num *temp = root_num;
	int l = strlen(p);
	for (int i = 0; i < l; i++)
	{
		if (temp->next[p[i] - '0'] == NULL)
			return -1;
		temp = temp->next[p[i] - '0'];
	}
	if (temp->end > 0)
	{
		return temp->index;
	}
	else
		return -1;
}