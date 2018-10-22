/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function



//I would like to use an array of this struct in order to sort using mergeSort
struct Node{
	//the data being compared must either be integer or string
	int intData;
	char* stringData;

	//this is the full string so we can just print it out line by line and output the file
	char* fullString;	
};

void mergeStr(struct Node *arr,int start,int middle,int end, struct Node *temp1, struct Node *temp2){
        int arraySize1 = middle-start+1;
        int arraySize2 = end-middle;

        int i;
        for(i=0; i<arraySize1;i++){
                strcpy(temp1[i].stringData,arr[start+i].stringData);
                strcpy(temp1[i].fullString,arr[start+i].fullString);
        }

        int j;
        for(j=0; j<arraySize2;j++){
                strcpy(temp2[j].stringData,arr[middle+1+j].stringData);
		strcpy(temp2[j].fullString,arr[middle+1+j].fullString);
        }


        i=0; j=0;
        int k=start;

        while(i<arraySize1 && j<arraySize2){
                if(strcmp(temp1[i].stringData,temp2[j].stringData) < 0){
                	strcpy(arr[k].stringData,temp1[i].stringData);
			strcpy(arr[k].fullString,temp1[i].fullString);
	                i++;
                }
                else{
                	strcpy(arr[k].stringData,temp2[j].stringData);
			strcpy(arr[k].fullString,temp2[j].fullString);
                    j++;
                }
                k++;
        }

        while(i<arraySize1){
                strcpy(arr[k].stringData,temp1[i].stringData);
		strcpy(arr[k].fullString,temp1[i].fullString);
                i++;k++;
        }

	while(j<arraySize2){
		strcpy(arr[k].stringData,temp2[j].stringData);
		strcpy(arr[k].fullString,temp2[j].fullString);
		j++;k++;
	}

}

void mergesortStr(struct Node *arr, int start, int end,struct Node *temp1, struct Node *temp2){
        if(start<end){
                int middle = (start+end)/2;

                mergesortStr(arr,start,middle,temp1,temp2);
                mergesortStr(arr,middle+1,end,temp1,temp2);
                mergeStr(arr,start,middle,end,temp1,temp2);
        }
}



//merge sort for integers
void mergeInt(struct Node *arr,int start,int middle,int end, struct Node *temp1, struct Node *temp2){
        int arraySize1 = middle-start+1;
        int arraySize2 = end-middle;

        int i;
        for(i=0; i<arraySize1;i++){
                temp1[i].intData = arr[start+i].intData;
                strcpy(temp1[i].fullString,arr[start+i].fullString);
        }
        int j;
        for(j=0; j<arraySize2;j++){
                temp2[j].intData = arr[middle+1+j].intData;
		strcpy(temp2[j].fullString,arr[middle+1+j].fullString);
        }


        i=0; j=0;
        int k=start;

        while(i<arraySize1 && j<arraySize2){
                if(temp1[i].intData<temp2[j].intData){
                        arr[k].intData = temp1[i].intData;
			strcpy(arr[k].fullString,temp1[i].fullString);
                        i++;
                }
                else{
                        arr[k].intData = temp2[j].intData;
			strcpy(arr[k].fullString,temp2[j].fullString);
                        j++;
                }
                k++;
        }

        while(i<arraySize1){
                arr[k].intData=temp1[i].intData;
		strcpy(arr[k].fullString,temp1[i].fullString);
                i++;k++;
        }

	while(j<arraySize2){
		arr[k].intData=temp2[j].intData;
		strcpy(arr[k].fullString,temp2[j].fullString);
		j++;k++;
	}

}

void mergesortInt(struct Node *arr, int start, int end,struct Node *temp1, struct Node *temp2){
        if(start<end){
                int middle = (start+end)/2;

                mergesortInt(arr,start,middle,temp1,temp2);
                mergesortInt(arr,middle+1,end,temp1,temp2);
                mergeInt(arr,start,middle,end,temp1,temp2);
        }
}


int simpleCSVsorter(char* inputfile, char* inputColumn){
	

	//must be a valid columnName from the movie_metadata

	if( (strcmp(inputColumn,"director_name")!=0)&&(strcmp(inputColumn,"num_critic_for_reviews")!=0)&&(strcmp(inputColumn,"duration")!=0)&&(strcmp(inputColumn,"director_facebook_likes")!=0)&&(strcmp(inputColumn,"actor_3_facebook_likes")!=0)&&(strcmp(inputColumn,"actor_2_name")!=0)&&(strcmp(inputColumn,"actor_1_facebook_likes")!=0)&&(strcmp(inputColumn,"gross")!=0)&&(strcmp(inputColumn,"genres")!=0)&&(strcmp(inputColumn,"actor_1_name")!=0)&&(strcmp(inputColumn,"movie_title")!=0)&&(strcmp(inputColumn,"num_voted_users")!=0)&&(strcmp(inputColumn,"cast_total_facebook_likes")!=0)&&(strcmp(inputColumn,"actor_3_name")!=0)&&(strcmp(inputColumn,"facenumber_in_poster")!=0)&&(strcmp(inputColumn,"plot_keywords")!=0)&&(strcmp(inputColumn,"movie_imdb_link")!=0)&&(strcmp(inputColumn,"num_user_for_reviews")!=0)&&(strcmp(inputColumn,"language")!=0)&&(strcmp(inputColumn,"country")!=0)&&(strcmp(inputColumn,"content_rating")!=0)&&(strcmp(inputColumn,"budget")!=0)&&(strcmp(inputColumn,"title_year")!=0)&&(strcmp(inputColumn,"actor_2_facebook_likes")!=0)&&(strcmp(inputColumn,"imdb_score")!=0)&&(strcmp(inputColumn,"aspect_ratio")!=0)&&(strcmp(inputColumn,"movie_facebook_likes")!=0) ){
		printf("error, your third argument is not a valid column name\n");
		return 0;
	}

	//is column we are sorting int? this int is 0 if false, 1 if true
	int isInt=0;

	if((strcmp(inputColumn,"num_critic_for_reviews")==0)||(strcmp(inputColumn,"duration")==0)||(strcmp(inputColumn,"director_facebook_likes")==0)||(strcmp(inputColumn,"actor_3_facebook_likes")==0)||(strcmp(inputColumn,"actor_1_facebook_likes")==0)||(strcmp(inputColumn,"gross")==0)||(strcmp(inputColumn,"num_voted_users")==0)||(strcmp(inputColumn,"cast_total_facebook_likes")==0)||(strcmp(inputColumn,"facenumber_in_poster")==0)||(strcmp(inputColumn,"num_user_for_reviews")==0)||(strcmp(inputColumn,"budget")==0)||(strcmp(inputColumn,"title_year")==0)||(strcmp(inputColumn,"actor_2_facebook_likes")==0)||(strcmp(inputColumn,"imdb_score")==0)||(strcmp(inputColumn,"aspect_ratio")==0)||(strcmp(inputColumn,"movie_facebook_likes")==0)){
		isInt = 1;
	}

	FILE *myFile;
	
	myFile = fopen(inputfile, "r");

        if(myFile == NULL){
                printf("Failed to open and read the file.\n");
		return 0;
        }

	int c;

	//this buf String will hold the whole row
	int bufSize = 64;
	char* buf = (char *)malloc(bufSize*sizeof(char));
	int temp = bufSize;

	//this String only holds the desired data from column being compared
	char* compareC = (char *)malloc(bufSize*sizeof(char));
	//int y is indexing for compareC
	int y=0;	

	int charIndex = 0;

	//counts number of commas in current line
	int commaCount=0;

	//keeps count of line number in original file
	int lineCount=0;
	
	//tells how many commas have passed until it htis the field that wants to be sorted
	int commaColSort=-1;


	//array of Nodes so that list can be sorted
	struct Node* myArray = malloc(1024*1024*sizeof(struct Node));
	

	//this one only exists to stop if statement from running
	int tempbreak = 0;

	//counts total chars to be able to realloc
	int totalChar=0;	

	//this int will be the conditional to tell stringData to take in ',' if its part of the value being compared
	int takeComma = 0;
	
	//read to end of file
	while((c=fgetc(myFile))!=EOF){

		
		if(totalChar<bufSize){
			buf[charIndex] = c;
		}

		if(totalChar == bufSize){
			char *hold = realloc(buf, 2*bufSize);
			if(hold == NULL){
				printf("realloc() error: memory was not correctly allocated\n");
				return 0;
			}
			buf=hold;
			bufSize*=2;

			buf[charIndex]=c;
		}

		//this set of conditionals finds how many commas passes before the matched column is found
		if((lineCount==0)&&((c==',')||(c=='\n'))){
			
			//columnName found, store # commas we must parse before getting the wanted field
			if((strstr(buf,inputColumn)!=NULL)&&(tempbreak==0)){
				commaColSort = commaCount;
				tempbreak = 1;
			}

			if(c==','){
				++commaCount;
			}
			
			//columnName we are sorting cannot be found
			if((strstr(buf,inputColumn)==NULL)&&(c=='\n')){
				printf("The indicated column can not be found, please put valid column name\n");
				return 0;
			}
		}

		//this is for the condition where we have " " for values with commas in them
	        if(c=='"'){
                        if(takeComma==0){
        	                takeComma=1;
                        }
                        else{
                                takeComma=0;
                        }
	        }

		//past the 1st line, check whats in the selected column and store that data
		if(lineCount>0){

			//if we passed correct number of commas, we can start passing in this part of string
			if(commaColSort == commaCount){
				if((c!=' ')&&(c!='\n')){

					if(y==temp){
						char *hold2 = realloc(compareC, 2*temp);
						if(hold2 == NULL){
							printf("realloc() error: memory was not correctly allocated\n");
							return 0;
						}
						compareC = hold2;
						temp*=2;
					}
					if(c!='"'){
						compareC[y] = c;
						y++;
					}
				}
				//this situation takes care of the last column field
				if(c=='\n'){
					compareC[y]='\0';
				}
			}


			//we have passed the portion where we want to compare, so stop passing string in
			if(commaColSort<commaCount){
				compareC[y-1] = '\0';
			}

			if((c==',')&&(takeComma==0)){
				++commaCount;
			}

		}



		++totalChar;
		++charIndex;

		//end of the line, completes the string with \0 and stores the whole string
		if(c=='\n'){
			--charIndex;
			buf[charIndex]='\0';
		
			myArray[lineCount].fullString = malloc(charIndex*sizeof(struct Node));
			strcpy(myArray[lineCount].fullString,buf);
			
			//if column being compared is chars
			if(isInt==0){
				myArray[lineCount].stringData = malloc(charIndex*sizeof(struct Node));
				strcpy(myArray[lineCount].stringData,compareC);
			}

			//if column being compared is int, need to trim whats being compared
			if(isInt==1){
				myArray[lineCount].intData = atoi(compareC);
			}

			charIndex=0;

			//printf("Current line:%i; stored portion:%s; whole line:%s\n",lineCount,compareC,myArray[lineCount].fullString);
			//printf("Current line:%i; stored portion:%i; whole line:%s\n",lineCount,myArray[lineCount].intData,myArray[lineCount].fullString);

			++lineCount;
			commaCount = 0;
			tempbreak=0;
			y=0;
		}

	}
        struct Node* temp1=malloc(lineCount*sizeof(struct Node));
        struct Node* temp2=malloc(lineCount*sizeof(struct Node));
	
	int j;
	for(j=0;j<lineCount;j++){
		temp1[j].fullString = malloc(bufSize*sizeof(struct Node));
		temp2[j].fullString = malloc(bufSize*sizeof(struct Node));
	}


	free(buf);
	free(compareC);

	if(isInt==1){
		mergesortInt(myArray,1,lineCount-1,temp1,temp2);
	}

	if(isInt==0){
		int f;
		for(f=0;f<lineCount;f++){
			temp1[f].stringData = malloc(bufSize*sizeof(struct Node));
			temp2[f].stringData = malloc(bufSize*sizeof(struct Node));
		}
		mergesortStr(myArray,1,lineCount-1,temp1,temp2);
	}

	
	///////formatting output to "<inputfile>-sorted-<inputColumn>.csv"

	char* csvSuffix = ".csv";
	char* sortedstring = "-sorted-";
	char* tempinputColumn = (char*)malloc(100*sizeof(char));
	char* outputfilename = (char*)malloc(1000*sizeof(char));

	strcpy(outputfilename, inputfile);

	char *ptr;
	ptr = strchr(outputfilename, '.');
	if (ptr != NULL) {
    	*ptr = '\0';
	}

	strcpy(tempinputColumn, inputColumn);
	strcat(outputfilename, sortedstring);
	strcat(outputfilename, tempinputColumn);
	strcat(outputfilename, csvSuffix);

	////////end of formatting output

	FILE* output = fopen(outputfilename, "w");

	fprintf(output,"%s\n",myArray[0].fullString);

	int z;
	for(z=1;z<lineCount;z++){
		//printf("%i\n",myArray[z].intData);
		//printf("%s\n",myArray[z].stringData);
		fprintf(output,"%s\n",myArray[z].fullString);
	}

	free(temp1);
	free(temp2);
	free(tempinputColumn);
	free(outputfilename);
	pclose(myFile);
	pclose(output);

	return 0;
}
