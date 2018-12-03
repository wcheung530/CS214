#define STDERROR 2
//extern int process_count;

struct Node{
	//the data being compared must either be integer or string
	int intData;
	char* stringData;

	//this is the full string so we can just print it out line by line and output the file
	char* fullString;	
};
void mergeStr(struct Node *arr,int start,int middle,int end, struct Node *temp1, struct Node *temp2);

void mergesortStr(struct Node *arr, int start, int end,struct Node *temp1, struct Node *temp2);


//merge sort for integers
void mergeInt(struct Node *arr,int start,int middle,int end, struct Node *temp1, struct Node *temp2);

void mergesortInt(struct Node *arr, int start, int end,struct Node *temp1, struct Node *temp2);
       


char* formatOutput(char* inputfile, char* inputColumn, char* outputDir);

//this function returns 0 if a file is a valid csv file and returns -1 if invalid file
int checkcsv(char* inputfilepath); 


//handles the sorting of an input file. Returns 0 on sucess, and -1 for failure
int csvfilehandler(char* inputfilepath, char* inputfile, char* inputColumn, char* outputDir);


void listDirectory(char* inputDirectory, char* inputColumn, char* outputDir, int indent); 
