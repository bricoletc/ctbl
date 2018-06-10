#include <ctype.h>
#include <stdio.h> /* defines EOF */
#define BUFSIZE 1000

/* Page 136 of K&R book */
int getword(char *word, FILE *fp,int lim){
	int c, getch(void);
	void ungetch(int);
	char *w=word;

	while (isspace(c = tolower(getc(fp))))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}	
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = tolower(getc(fp))) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

/* Page 79 of K&R book */
char buf[BUFSIZE];
int bufp = 0;

int getch(void){
	return (bufp>0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
