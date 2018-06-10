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
	void Parse_Newick(char **,FILE *, char *[], int, char *);
	fp = fopen(argv[1],"r");	

	char *charTable[MAXGROUPS];
	char **pptr=charTable; /* Pointer to pointer */
	/* for storing parsed taxo groups */
	char word[MAXWORD];
	Parse_Newick(pptr,fp,vocab_array,vocab_size,word);
	printf("%s \n",charTable[0]);
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


void Parse_Newick(char **pptr, FILE *fp, char *vocab_array[], int vocab_size, char *word){
	char charRow[vocab_size+1];
	for (int i = 0;i < vocab_size;i++){
		charRow[i] = '0';
	}
	charRow[vocab_size+1] = '\0';

	char c;
	int i = 0; /* for adding chars to word */
	while (c = getc(fp) != ')'){
		if (c=='('){
			/* Recursive call here */
			Parse_Newick(++pptr, fp, vocab_array, vocab_size, word);
			
			for (int j=0;j < vocab_size;j++){
				if (*pptr[j]=='1' && charRow[j]=='0')
					charRow[j]='1';
			}	
		}
		else if (c==','){
			int pos=binsearch(word,vocab_array,vocab_size);
			charRow[pos]='1';
			i=0;	
		}
		else {
			printf("Char: %c",c);
			word[i++] = c;
		}
	}	
	/* Assuming c is ')' here */
	int pos=binsearch(word,vocab_array,vocab_size);
	charRow[pos]='1';
	*pptr=charRow; /* Attach the character row to the character table */	
	printf("Word: %s \n",word);
	printf("%s \n",charRow);
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
