#include "LinkedList.c"

int n_case = 0;
char mLess[1000][50];

void del(char* a)
{
	int i;
	for(i=strlen(a)-1; i>=0; i--)
		a[i] = 0;
}

bool checkWord(char* s, char pre)
{
	if (strlen(s) == 0) return false;
	if ('A' <= s[0] && s[0] <= 'Z' && pre != '.' 
	   && pre != '?' && pre != '!')
		return false;
	int i;
	for (i=0; i<n_case; i++)
	{
		if (strcmp(strlwr(s), mLess[i]) == 0) return false;
	}
	return true;
}

void readMeaningLessWord()
{
	FILE* input = fopen("stopw.txt", "r");
	if (input == NULL) {
		printf("File \"%s\" khong ton tai!\n", "stopw.txt");
		return;
	}
	while (!feof(input))
	{
		fscanf(input," %s", mLess[n_case++]);
	}
	fclose(input);
}

char* readInputFile(char* fin)
{
	FILE* input = fopen(fin, "r");
	if (input == NULL) {
		printf("File \"%s\" khong ton tai!\n", fin);
		return NULL;
	}

	int n;
	char* source = (char*) calloc(n, sizeof(char));

	char c;

	while (fscanf(input, "%c", &c) != EOF)
	{	
		n++;
		source[strlen(source)] = c;
	}
	fclose(input);
	return source;
}
node addNewWord(node head, char* newWord, int currentLine)
{
	node temp = createNode(newWord, currentLine);
	node pre = NULL;
	if (head == NULL) {
		head = temp;
		return head;
	}
	node p = head;
	while (p->next != NULL) {
		int cmp = strcmp(newWord, p->data.word);
		if (cmp == 0) {
			p->data.count++;
			char temp[20];
			sprintf(temp, ",%d", currentLine);
			strcat(p->data.linesAppear, temp);
			return head;
		}
		else if (cmp < 0) {
			if (pre == NULL) {
				temp->next = head;
				return temp;
			}
			else {
				pre->next = temp;
				temp->next = p;
				return head;
			}
		}
		pre = p;
		p = p->next;
	}
	p->next = temp;
	return head;
}

int main()
{
	readMeaningLessWord();
	char* source = readInputFile("vanban.txt");

	node head = NULL;
	char pre = '.';
	char newWord[100] = "";
	int currentLine = 1;
	int i;
	for(i=0; i<=strlen(source); i++)
	{
		if (isalpha(source[i])){
			newWord[strlen(newWord)] = source[i];
		} 
		else {
			if (checkWord(newWord, pre)) {
				head = addNewWord(head, newWord, currentLine);
				pre = source[i];
			}
			if (source[i] == '\n') currentLine++;
			if (pre != '.' || source[i] != ' ')
				pre = source[i];
			del(newWord);
		}
	}
	printResult(head);
}
