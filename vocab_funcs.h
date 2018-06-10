#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "getword.h"
#define MAXWORD 1000

int getword(char *,FILE *,int);
/* char *strdup(char *s); */
/*int strcmp(const char *cs,const char *ct);*/
struct tnode *talloc(void);

struct tnode{
	char *word;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *,char *);


struct tnode *build_binTree(FILE *fp){
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;

	while (getword(word,fp,MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root,word);
	
	return root;
	}

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w,p->word)) < 0)
		p->left = addtree(p->left,w);
	else if (cond > 0)
		p->right = addtree(p->right,w);
	return p;
}



struct tnode *talloc(void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}
/*
char *strdup(char *s){
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p,s);
	return p;
}
*/
