#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define AUTOMATA_FILE   "automata2.txt"
// #define PROGRAM_FILE    "test.txt"
#define MAX_SYMBOLS     100
#define SYMBOL_LENGTH   100
#define MAX_STATES      20

/*
    {a, A}                                          // allowed characters
    {1, 2, 3}                                       // number of states
    {1}                                             // starting state
    {2, 3}                                          // final states
    {(1, a, 2), (2, a, 2), (1, A, 3), (3, A, 3)}    // transition states
    {(3, capital), (2, low)}                        // token type
*/

typedef struct def_DFA {
    char states[MAX_STATES][SYMBOL_LENGTH];         /* states */
    char initialState[MAX_STATES][SYMBOL_LENGTH];   /* starting state - element of states */
    char finalStates[MAX_STATES][SYMBOL_LENGTH];    /* final states */
    struct Transition *transitions[MAX_STATES];     /* transition states */
    struct Token *tokens[MAX_STATES];               /* token type */
    char symbols[MAX_SYMBOLS][SYMBOL_LENGTH];       /* allowed symbols (can be string) */
} DFA;

typedef struct Transition {
    char **symbol;                                  /* symbol */
    char **startState;                              /* start state */
    char **endState;                                /* transitioned state */
    // char symbol[2][SYMBOL_LENGTH];                  /* symbol */
    // char startState[2][SYMBOL_LENGTH];              /* start state */
    // char endState[2][SYMBOL_LENGTH];                /* transitioned state */
}transition; 

typedef struct Token {
    char finalState[2][SYMBOL_LENGTH];              /* a final state */
    char token[2][SYMBOL_LENGTH];                    /* token for state */
} token_def;


void parseAutomata(DFA*, char fileName[]);
void parse1DArr(char line[], char symbols[][SYMBOL_LENGTH]);
void parseTransition(char line[], transition *trans[]);
void parseTransHelper(char line[], transition *trans);
void parseTokens(char line[], token_def *tk[]);
void parseTokenHelper(char line[], token_def *tk);
void printAutomata(DFA *def);
void scanner(DFA *def, char tokens[][SYMBOL_LENGTH], char fileName[]);
transition* findTransition(DFA *def, char startingState[SYMBOL_LENGTH], char symbol[SYMBOL_LENGTH]);
char* findToken(DFA *def, char state[SYMBOL_LENGTH]);
int partialSymbolExists(DFA *def, char symbol[], int index);
int symbolExists(DFA *def, char symbol[]);
void printTokenArray(char tokens[][SYMBOL_LENGTH]);

int main(int argc, char *argv[]){
    DFA *def = malloc(sizeof *def);
    char tokens[SYMBOL_LENGTH][SYMBOL_LENGTH];

    if(argc < 3){
        printf("missing input file(s)\n");
        return 0;
    }
    if(argc > 3){
        printf("too many input files\n");
        return 0;
    }

    parseAutomata(def, argv[1]);
    // printAutomata(def);
    scanner(def, tokens, argv[2]);
    printTokenArray(tokens);
 
    // printf("Completed Successfully!\n");
    return 0;
}

/* parse automata from AUTOMATA_FILE to DFA definition*/
void parseAutomata(DFA* def, char fileName[]) {
    FILE *automataFile = fopen(fileName, "r");
    char line[1000];
    
    /* symbols */
    fgets(line, sizeof(line), automataFile);
    // printf("%s\n", line);
    parse1DArr(line, def->symbols);

    /* states */
    fgets(line, sizeof(line), automataFile);
    // printf("%s\n", line);
    parse1DArr(line, def->states);
    
    /* starting state */
    fgets(line, sizeof(line), automataFile);
    // printf("%s\n", line);
    parse1DArr(line, def->initialState);

    /* final states */
    fgets(line, sizeof(line), automataFile);
    // printf("%s\n", line);
    parse1DArr(line, def->finalStates);

    /* transition states */
    fgets(line, sizeof(line), automataFile);
    // printf("%s\n", line);
    parseTransition(line, def->transitions);

    /* token type */
    fgets(line, sizeof(line), automataFile);
    // printf("\n%s\n\n", line);
    parseTokens(line, def->tokens);

    fclose(automataFile);
}

/* parse a one-dimensional array */
void parse1DArr(char line[], char twoDArr[][SYMBOL_LENGTH]){
    char tmp[SYMBOL_LENGTH] = "";
    int i = 0, x = 0, s = 0;

    while(line[i] != '\n' || line[i] != '\0'){

        /* ignore whitespace */
        while (line[i] == ' '){
            i++;
        }

        /* start symbol array */
        if(line[i] == '{' || line[i] == '('){
            i++;
        }
        /* closing bracket */
        else if(line[i] == '}' || line[i] == ')'){
            i++;

            /* ignore whitespace */
            while (line[i] == ' '){
                i++;
            }
            
            if(line[i] == '\n' || line[i] == '\0'){
                // printf("%s\n", tmp);
                twoDArr[++s][0] = '\0';

                return;
            }

            /* error in symbol input - exit program */
            printf("ERROR - Invalid symbol array \"%s\"\n.", line);
            exit(1);
        }
        /* comma - start new symbol */
        else if(line[i] == ','){
            i++;

            // printf("%s ", tmp);

            /* start new symbol - clear tmp */
            for(x = 0; x < 10; x++){
                tmp[x] = '\0';
            }
            x = 0;
            s++;
        }
        /* symbols */
        else{
            /* append to symbol */
            twoDArr[s][x] = line[i];
            tmp[x++] = line[i];

            i++;
        }
    }
}

/* main parser for transition array */
void parseTransition(char line[], transition *trans[]){
    char tmp[SYMBOL_LENGTH] = "";
    int i = 0, x = 0, t = 0;


    trans[t] = malloc(sizeof trans[t]);


    while(line[i] != '\n'){

        /* ignore whitespace */
        while (line[i] == ' '){
            i++;
        }

        /* start symbol array */
        if(line[i] == '{'){
            i++;
        }
        /* closing bracket */
        else if(line[i] == '}'){
            i++;

            /* ignore whitespace */
            while (line[i] == ' '){
                i++;
            }
            
            /* error in symbol input - exit program */
            if(line[i] == '\n' || line[i] == '\0'){
                trans[++t] = NULL;

                return ;
            }

            printf("ERROR - Invalid symbol array \"%s\"\n.", line);
            exit(1);
        }
        /* comma - start new symbol */
        else if(line[i] == ','){
            i++;
            t++;
            trans[t] = malloc(sizeof trans[t]);

            /* start new symbol - clear tmp */
            for(x = 0; x < 10; x++){
                tmp[x] = '\0';
            }
            x = 0;
        }
        /* symbols */
        else{

            /* append to symbol */
            while(line[i] != ')'){
                tmp[x++] = line[i++];
            }
            tmp[x] = ')';
            tmp[++x] = '\0';

            // printf("%s\n", tmp);

            parseTransHelper(tmp, trans[t]);

            i++;
        }
    }
}

/* helps parseTransition() with transition parsing */
void parseTransHelper(char line[], transition *trans){
    char tmp[SYMBOL_LENGTH] = "";
    int i = 0, x = 0, c = 0;

    trans->symbol = malloc(2 * sizeof(char*));
    for(int j = 0; j < 2; j++){
      trans->symbol[j] = malloc(100 * sizeof(char));
    }
    trans->startState = malloc(2 * sizeof(char*));
    for(int j = 0; j < 2; j++){
      trans->startState[j] = malloc(100 * sizeof(char));
    }
    trans->endState = malloc(2 * sizeof(char*));
    for(int j = 0; j < 2; j++){
      trans->endState[j] = malloc(100 * sizeof(char));
    }


    while(line[i] != '\n' || line[i] != '\0'){

        /* ignore whitespace */
        while (line[i] == ' '){
            i++;
        }

        /* start symbol array */
        if(line[i] == '{' || line[i] == '('){
            i++;
        }
        /* closing bracket */
        else if(line[i] == '}' || line[i] == ')'){
            i++;

            /* ignore whitespace */
            while (line[i] == ' '){
                i++;
            }
            
            if(line[i] == '\n' || line[i] == '\0'){
                trans->startState[1][0] = '\0';
                trans->symbol[1][0] = '\0';
                trans->endState[1][0] = '\0';

                return;
            }

            /* error in symbol input - exit program */
            printf("ERROR - Invalid symbol array \"%s\"\n.", line);
            exit(1);
        }
        /* comma - start new symbol */
        else if(line[i] == ','){
            i++;

            /* startState */
            if(c == 0){
                trans->symbol[0][x] = '\0';
                // printf("startState - %s\n", trans->startState[0]);
            }
            /* symbol */
            else if(c == 1){
                trans->symbol[0][x] = '\0';
                // printf("symbol - %s\n", trans->symbol[0]);
            }
            /* endState */
            else if(c == 2){
                trans->endState[0][x] = '\0';
                // printf("endState - %s\n", trans->endState[0]);
            }

            /* start new symbol - clear tmp */
            for(x = 0; x < 10; x++){
                tmp[x] = '\0';
            }
            x = 0;
            c++;
        }
        /* symbols */
        else{
            /* append to symbol */

            /* startState */
            if(c == 0){
                trans->startState[0][x] = line[i];
                // printf("startState - %s\n", trans->startState[0]);
            }
            /* symbol */
            else if(c == 1){
                trans->symbol[0][x] = line[i];
                // printf("symbol - %s\n", trans->symbol[0]);
            }
            /* endState */
            else if(c == 2){
                trans->endState[0][x] = line[i];
                // printf("endState - %s\n", trans->endState[0]);
            }
            
            tmp[x++] = line[i];

            i++;
        }
    }
}

/* main parser for token array */
void parseTokens(char line[], token_def *tk[]){
    char tmp[SYMBOL_LENGTH] = "";
    int i = 0, x = 0, t = 0;

    tk[t] = malloc(sizeof tk[t]);

    while(line[i] != '\n'){

        /* ignore whitespace */
        while (line[i] == ' '){
            i++;
        }

        /* start symbol array */
        if(line[i] == '{'){
            i++;
        }
        /* closing bracket */
        else if(line[i] == '}'){
            i++;

            /* ignore whitespace */
            while (line[i] == ' '){
                i++;
            }
            
            /* error in symbol input - exit program */
            if(line[i] == '\n' || line[i] == '\0'){
                tk[++t] = NULL;

                return ;
            }

            printf("ERROR - Invalid symbol array \"%s\"\n.", line);
            exit(1);
        }
        /* comma - start new symbol */
        else if(line[i] == ','){
            i++;
            t++;
            tk[t] = malloc(sizeof tk[t]);

            /* start new symbol - clear tmp */
            for(x = 0; x < 10; x++){
                tmp[x] = '\0';
            }
            x = 0;
        }
        /* symbols */
        else{

            /* append to symbol */
            while(line[i] != ')'){
                tmp[x++] = line[i++];
            }
            tmp[x] = ')';
            tmp[++x] = '\0';

            // printf("test - %s\tt = %d\n", tmp, t);

            parseTokenHelper(tmp, tk[t]);

            i++;
        }
    }
}

/* helps praseTokens() with token parsing */
void parseTokenHelper(char line[], token_def *tk){
    char tmp[SYMBOL_LENGTH] = "";
    int i = 0, x = 0, c = 0;

    while(line[i] != '\n' || line[i] != '\0'){

        /* ignore whitespace */
        while (line[i] == ' '){
            i++;
        }

        /* start symbol array */
        if(line[i] == '{' || line[i] == '('){
            i++;
        }
        /* closing bracket */
        else if(line[i] == '}' || line[i] == ')'){
            i++;

            /* ignore whitespace */
            while (line[i] == ' '){
                i++;
            }
            
            if(line[i] == '\n' || line[i] == '\0'){
                tk->finalState[1][0] = '\0';
                tk->token[1][0] = '\0';
                return;
            }

            /* error in symbol input - exit program */
            printf("ERROR - Invalid symbol array \"%s\"\n.", line);
            exit(1);
        }
        /* comma - start new symbol */
        else if(line[i] == ','){
            i++;

            /* finalState */
            if(c == 0){
                tk->finalState[0][x] = '\0';
                // printf("startState - %s\n", trans->startState[0]);
            }
            /* token */
            else if(c == 1){
                tk->token[0][x] = '\0';
                // printf("symbol - %s\n", trans->symbol[0]);
            }

            /* start new symbol - clear tmp */
            for(x = 0; x < 10; x++){
                tmp[x] = '\0';
            }
            x = 0;
            c++;
        }
        /* symbols */
        else{
            /* append to symbol */

            /* finalState */
            if(c == 0){
                tk->finalState[0][x] = line[i];
                // printf("startState - %s\n", trans->startState[0]);
            }
            /* token */
            else if(c == 1){
                tk->token[0][x] = line[i];
                // printf("symbol - %s\n", trans->symbol[0]);
            }
            tmp[x++] = line[i];

            i++;
        }
    }
}

/* prints automata definition */
void printAutomata(DFA *def){
    int i = 0;
    while(def->symbols[i][0] != '\0'){
        printf("%d - %s\n", i, def->symbols[i]);
        i++;
    }
    printf("\n");

    i = 0;
    while(def->states[i][0] != '\0'){
        printf("%d - %s\n", i, def->states[i]);
        i++;
    }
    printf("\n");

    i = 0;
    while(def->initialState[i][0] != '\0'){
        printf("%d - %s\n", i, def->initialState[i]);
        i++;
    }
    printf("\n");

    i = 0;
    while(def->finalStates[i][0] != '\0'){
        printf("%d - %s\n", i, def->finalStates[i]);
        i++;
    }
    printf("\n");

    i = 0;
    while(def->transitions[i] != NULL){
        printf("%s -- %s --> %s\n", def->transitions[i]->startState[0], def->transitions[i]->symbol[0], def->transitions[i]->endState[0]);
        i++;
    }
    printf("\n");

    i = 0;
    while(def->tokens[i] != NULL){
        printf("%s --> %s\n", def->tokens[i]->finalState[0], def->tokens[i]->token[0]);
        i++;
    }
}

/* scans tokens from PROGRAM_FILE */
void scanner(DFA *def, char tokens[][SYMBOL_LENGTH], char fileName[]){
    FILE *program = fopen(fileName, "r");
    transition *trans = malloc(sizeof *trans);
    int c, i = 0, count = 0;

    /* holds current state */
    char currentState[SYMBOL_LENGTH], tmpState[SYMBOL_LENGTH];
    strcpy(currentState, def->initialState[0]);

    /* holds symbol */
    char symbol[SYMBOL_LENGTH];
    char tmpSym[SYMBOL_LENGTH];
    fpos_t lookAhead, comment;

    fgetpos(program, &lookAhead);
    c = fgetc(program);
    while (c != EOF){
        /* ignore next line */
        if(c == '\n' || c == ' '){
            c = fgetc(program);
            continue;
        }

        /* ignore comments */
        if(c == '/'){
            // printf("%c", fgetc(program));
            if(fgetpos(program, &comment), c = fgetc(program), (char) c == '*'){
                while(c = fgetc(program), c != EOF){
                    if((char) c == '*'){
                        if(c = fgetc(program), (char) c == '/'){
                            c = fgetc(program);
                            break;
                        }
                    }
                }
                if(c == EOF){
                    printf("error.\n");
                    exit(1);
                }
                continue;
            }
            else{
                fsetpos(program, &comment);
            }
        }

        symbol[i++] = (char) c;
        symbol[i] = '\0';

        /* longest possible token */
        while(partialSymbolExists(def, symbol, i-1) >= 0){
            // printf("symbol - %s\n", symbol);
            /* ignore next line */
            if(c == '\n' || c == ' '){
                symbol[i-1] = '\0';
                // printf("\tcurrent state - %s\tsymbol - %s\n", currentState, symbol);
                
                break;
            }

            /* ignore comments */
            if(c == '/'){
                // printf("%c", fgetc(program));
                if(fgetpos(program, &comment), c = fgetc(program), (char) c == '*'){
                    while(c = fgetc(program), c != EOF){
                        if((char) c == '*'){
                            if(c = fgetc(program), (char) c == '/'){
                                c = fgetc(program);
                                break;
                            }
                        }
                    }
                    if(c == EOF){
                        printf("error.\n");
                        exit(1);
                    }
                    // printf("symbol = %s\n", symbol);
                    continue;
                }
                else{
                    fsetpos(program, &comment);
                }
            }

            /* pops char from symbol and restores fgetc last position */
            if(partialSymbolExists(def, symbol, i-1) == 0){
                fsetpos(program, &lookAhead);
                symbol[i-1] = '\0';
                break;
            }

            /* reached end of file while looking ahead */
            if(fgetpos(program, &lookAhead), c = fgetc(program), c == EOF){
                if(symbolExists(def, symbol)){
                    break;
                }
                printf("error.\n");
                exit(1);
            }
            symbol[i++] = (char) c;
            symbol[i] = '\0';
        }
        
        /* symbol does not exist - exit program */
        if(!symbolExists(def, symbol)){
            printf("error.\n");
            exit(1);
        }
        // printf("symbol - %s\n", symbol);

        trans = findTransition(def, currentState, symbol);
        /* transition not found - append to symbol */
        if(trans == NULL){

            if(findToken(def, currentState) != NULL){
                strcpy(tokens[count++], findToken(def, currentState));
            }
            
            /* reset state to initial state */
            strcpy(currentState, def->initialState[0]);
            trans = findTransition(def, currentState, symbol);
        }

        // printf("\n%s --- %s ---> %s\n", trans->startState[0], trans->symbol[0], trans->endState[0]);

        /* transition found */
        strcpy(currentState, trans->endState[0]);
        i = 0;
        c = fgetc(program);
    }

    if(findToken(def, currentState) != NULL){
        // printf("token - %s\n", findToken(def, currentState));
        strcpy(tokens[count++], findToken(def, currentState));
    }
    tokens[count][0] = '\0';

    /* close PROGRAM_FILE */
    fclose(program);
}

transition* findTransition(DFA *def, char startingState[SYMBOL_LENGTH], char symbol[SYMBOL_LENGTH]){
    int i = 0;
    while(def->transitions[i] != NULL){

        /* transition found - matched starting state and symbol */
        if(!strcmp(def->transitions[i]->startState[0], startingState) && !strcmp(def->transitions[i]->symbol[0], symbol)){
            return def->transitions[i];
        }
        i++;
    }
    return NULL;    
}

char* findToken(DFA *def, char state[SYMBOL_LENGTH]){
    int i = 0; 

    while(def->tokens[i] != NULL){
        if(!strcmp(def->tokens[i]->finalState[0], state)){
            return def->tokens[i]->token[0];
        }
        i++;
    }

    return NULL;
}

/* count number of symbols that start with input symbol */
int partialSymbolExists(DFA *def, char symbol[], int index){
    /*check if token is in token array */
    int i = 0, count = 0, x = 0;
    // printf("index - %d\n", index);
    while(def->symbols[i][0] != '\0'){
        // printf("test[%d] - %c == %c\n", index, def->symbols[i][index], symbol[index]);
        /* token exists */
        // if(!strcmp(def->symbols[i], symbol))
        if(def->symbols[i][index] == symbol[index]){
            // printf("testing2\n");
            count++;
        }
        i++;
    }
    // printf("exist - count = %d\n", count);

    /* token doesn't exist */
    return count;
}

int symbolExists(DFA *def, char symbol[]){
    /*check if token is in token array */
    int i = 0;
    while(def->symbols[i][0] != '\0'){
        // printf("test[%d] - %s == %s\n", i, def->symbols[i], symbol);
        /* token exists */
        if(!strcmp(def->symbols[i], symbol)){
            // printf("testing2\n");
            return 1;
        }
        i++;
    }

    /* token doesn't exist */
    return 0;
}

/* prints token array  */
void printTokenArray(char tokens[][SYMBOL_LENGTH]){
    int i = 0;
    printf("\n{");
    while(tokens[i][0] != '\0'){
        printf("%s", tokens[i]);
        i++;
        if(tokens[i][0] != '\0'){
            printf(", ");
        }
    }
    printf("}\n\n");
}

