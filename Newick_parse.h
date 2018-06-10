#define MAXGROUPS 200
#define MAXSPP 200
#define MAXWORD 1000

int *charTable[MAXGROUPS];
int **pptr=charTable; /* Pointer to pointer */
/* for storing parsed taxo groups */
char word[MAXWORD];

void Parse_Newick(int *ptr){
	int charRow[MAXSPP];
	for (int i=0;i++;i<MAXSPP){
		charRow[i]=0;
	}

	char c;
	int i = 0; /* for adding chars to word */
	while (c = getchar() != ')'){
		if (c=='('){
			/* Recursive call here */
			Parse_Newick(*++pptr);
			
			for (int j=0;j<MAXSPP;j++){
				if (*pptr[j]==1 && charRow[j]==0)
					charRow[j]=1;
			}	
		}
		else if (c==','){
			int pos=binsearch(word,vocab,vocab_size);
			charRow[pos]=1;
			i=0;	
		}
		else {
			word[i++]=c;
		}
	}	
	/* Assuming c is ')' here */
	int pos=binsearch(word,vocab,vocab_size);
	charRow[pos]=1;
	ptr=charRow; /* Attach the character row to the character table */	
}
