#include "parse.h"
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>


char *getsubstr(char *s, regmatch_t *pmatch) {
    static char buf[100] = {0};
    memset(buf, 0, sizeof (buf));
    memcpy(buf, s + pmatch -> rm_so, pmatch -> rm_eo - pmatch -> rm_so);
    return buf;
}

void split(char* s, const char** name, const char** value, char delim) {
    char* token;
    token = strtok(s, &delim); 
    if (token != NULL) {
        *name = token; 
        token = strtok(NULL, &delim); 
        if (token != NULL) {
            *value = token;
        }
    }
}

void print(const char* str) {
    printf("%s\n", str);
}

int
parse_query_string(char* url, struct query_parameter** out)
{
	/* TODO */

    regmatch_t pmatch;
    regex_t reg;
    const char *pattern = "([^?&]+)=([^?&]+)";
    char* buf = url;
        
    regcomp(&reg, pattern, REG_EXTENDED);
    int offset = 0;

    int maxlength = 10;  // json max size
        
    struct query_parameter* arr = (struct query_parameter*)malloc(maxlength * sizeof(struct query_parameter));
    
    *out = arr;

    int pos = 0;

    while (offset < strlen(buf)) {
        int status = regexec(&reg, buf + offset, 1, &pmatch, 0);
        if (status == REG_NOMATCH) {
            puts("No Match");
        } else if (pmatch.rm_so != -1) {
            // Match
            char* p = getsubstr(buf + offset, &pmatch);
            
            const char* name;
            const char* value;
            
			char token = '=';
			split(p, &name, &value, token);
            
            
            arr[pos].name = strdup(name);
            arr[pos].value = strdup(value);
            /*
            print(arr[pos].name);
            print(arr[pos].value);
            */
            pos ++ ;
        }
        offset += pmatch.rm_eo;
    }
    

    // printf("%d\n", pos); 
    
    /*
    for (int i = 0; i < pos; i ++ ) {
        print((*out)[i].name);
        print((*out)[i].value);
    }
    */

    regfree(&reg);

    return pos;
}
