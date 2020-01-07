#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEBUFFER 2048

typedef struct tag_arglist {
    char *key;
    char *value;
    struct tag_arglist *next;
} ARGLIST;

/*
* ws_addarg
*
*/
int ws_addarg(ARGLIST *root, char *key, char *fmt, ...) {
	// expected: key="HTTP_USER", fmt=<username>
	char *newkey;
	va_list ap;
	char value[MAX_LINEBUFFER];
	
	va_start(ap,fmt);
	vsnprintf(value,sizeof(value),fmt,ap);
	// display
	// printf("\nvsnprintf: %s\n", value);
	va_end(ap);
	
	newkey=strdup(key);
	
	// some more stuff...
	
	return 0;
}

int main(int argc, char ** argv) {
	
	// ws_decodepassword(auth,&username,&password);
	
	// username is decoded from base64 ...
	char username[MAX_LINEBUFFER];
	printf("DEBUG %x\n", (int) username);

	fgets(username, MAX_LINEBUFFER-1, stdin);
	username[strcspn(username, "\n")] = 0;
	
	// if (auth_handler(username,password))
	//	can_dispatch=1;
	ws_addarg(NULL,"HTTP_USER",username);
	// ws_addarg(&pwsc->request_vars,"HTTP_PASSWD",password);
	//free(password);
	
	return 0;
}
