#define MAXGROUPS 200
#define MAXSPP 200
#include "vocab_funcs.h"
#include "binsearch.h"

int main(int argc, char *argv[]){
	
	/* Open up the file containing the Newick */
	FILE *fp;
	fp = fopen(argv[1],"r");	

	/* Build vocabulary using binary tree */
	int vocab_size = 0;
	int *count = &vocab_size;
	struct tnode *root;	
	void treeprint(struct tnode *);
	void treesize(struct tnode *,int *);
	void treevocab(struct tnode *, char *[], int *);
	root = build_binTree(fp);
	fclose(fp);
	treesize(root,count);

	/* Get sorted array of the groups from the binary tree */
	char *vocab_array[vocab_size];
	vocab_size = 0;
	treevocab(root,vocab_array,count);

	/* Parse the Newick string, extracting the character Rows */
	void Parse_Newick(int *,char *[],FILE *, char *[], int, char *);
	fp = fopen(argv[1],"r");	

	char *charTable[MAXGROUPS];
	int rowPos = 0;
	int *pptr=&rowPos; /* Pointer to pointer */
	/* for storing parsed taxo groups */
	char word[MAXWORD];
	Parse_Newick(pptr,charTable,fp,vocab_array,vocab_size,word);
	fclose(fp);
	
	int j = 2; /* This excludes the first charRow of the array, which corresponds to all 1 */
	while(charTable[j] != NULL){
		printf("%s \n",(charTable[j++]));
	}

	return 0;

	/* To check vocab_array is populated right 
	   for (int i = 0; i< vocab_size; i++)
		printf("%s \n",vocab_array[i]);	
	*/


	/* Test binsearch in vocab_array
	int found;
	found = binsearch("dog",vocab_array,vocab_size);
	printf("%i\n",found);
	*/
}


void Parse_Newick(int *pptr,char *charTable[], FILE *fp, char *vocab_array[], int vocab_size, char *word){
	char charRow[vocab_size+1];
	for (int i = 0;i < vocab_size;i++){
		charRow[i] = '0';
	}
	charRow[vocab_size] = '\0';

	char c;
	int i = 0; /* for adding chars to word */
	while ((c = getc(fp)) != ')'){
		/* printf("%i \n",*pptr); */
		if (c=='('){
			/* Recursive call here */
			(*pptr)++;
			Parse_Newick(pptr, charTable, fp, vocab_array, vocab_size, word);
			
			for (int j=0;j < vocab_size;j++){
				if (charTable[*pptr][j]=='1' && charRow[j]=='0')
					charRow[j]='1';
			}	
			(*pptr)--;
		}
		else if (c==',' && i != 0){
			word[i]='\0';
			int pos=binsearch(word,vocab_array,vocab_size);
			charRow[pos]='1';
			/* printf("Word: %s at pos %i \n",word,pos); */
			i=0;	
		}
		else if (isalnum(c) || c == '_') {
			word[i++] = c;
		}
		else if (c == EOF)
			return;
	}	
	/* printf("Word end group: %s \n",word); */
	word[i]='\0';
	int pos=binsearch(word,vocab_array,vocab_size);
	charRow[pos]='1';
	i = 0;
	charTable[*pptr]=strdup(charRow); /* Attach the character row to the character table */	
	/* printf("%s \n",charRow); */ 
}


void treeprint(struct tnode *p){
	if (p != NULL) {
		treeprint(p->left);
		printf("%s \n",p->word);
		treeprint(p->right);
	}
}

void treesize(struct tnode *p,int *count){
	if (p != NULL) {
		treesize(p->left,count);
		(*count)++;
		treesize(p->right,count);
	}
}

void treevocab(struct tnode *p, char *vocab_array[], int *count){
	if (p != NULL) {
		treevocab(p->left,vocab_array,count);
		vocab_array[(*count)++] = p->word;
		treevocab(p->right,vocab_array,count);
	}
}
