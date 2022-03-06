#include <stdio.h>
#include <stdlib.h>

typedef struct Grocery_Item{
    char item_name[100];        /*  */
    double price;               /* the marked item_price (in dollars) of one item */
    int quantity;               /* the number of said items in one customer’s list - quantity*/
    /* first - first item; last - last item; next_item - item after first and so on */
    struct Grocery_Item *next_item;
}item_t;

typedef struct Customer{
    char name[100];
    double balance;             /* Amount of cash they have on them */
    int total_items;            /* total amount of items in their inventory */
    double total_cost;          /* total cost of items */
    item_t *first_item, *last_item;     /* items in inventory */
    struct Customer *next;      /* next person in line */
}customer_t;

typedef struct line_queue{
    customer_t *front, *rear;   /* declare front and end nodes to store people at the front and end(rear) of the line */
}line_t;

line_t* create_line();
void next_item(customer_t*);
void add_person_to_line(line_t* , char* , double);
void add_item_to_last_person(line_t*, char*, double, int);
void parse_text_line(line_t*, char*);
void remove_front_line_person(line_t*);
void process_checkout_line(line_t*, FILE*);

int main(void){
    /* open input file for read only */
    FILE* input = fopen("input.txt", "r");
    if(input == NULL){
        printf("No such file as %s\n", "input.txt");
    }
    char text[1000];
    line_t* line = create_line();                   /* Create shopping line */
    while (fgets(text, sizeof(text), input)){
        parse_text_line(line, text);
    }
    fclose(input);

    FILE* output = fopen("output.txt", "w");
    process_checkout_line(line, output);
    fclose(output);

    return 0;
}

line_t* create_line(){
    line_t* line = (line_t*)malloc(sizeof(line_t));
    line->front = line->rear = NULL;
    return line;
}

void next_item(customer_t* person){
    if(person == NULL){
        return;
    }
    item_t* tmp = person->first_item;
    person->first_item = person->first_item->next_item;

    if(person->first_item == NULL){
        person->last_item = NULL;
    }
    free(tmp);
}

void add_person_to_line(line_t* line, char* customer_name, double balance){
    /* allocates space for a new person to join the line */
    customer_t* tmp = (customer_t*)malloc(sizeof(customer_t));

    int i;
    for(i = 0; customer_name[i] != '\0'; i++){
        tmp->name[i] = customer_name[i];
    }
    tmp->name[i] = '\0';
    tmp->balance = balance;
    tmp->next = NULL;
    tmp->first_item = NULL;

    /* if the end(rear) of the line is empty(NULL) then the only person must be at the front and end(rear) of the line */
    if(line->rear == NULL){
        line->front = line->rear = tmp;
        return;
    }

    /* insert the next person(tmp) after the last person(line->rear->next) then have line->rear point to the new rear  */
    line->rear->next = tmp;     /* line->rear-> is just an pointer so that's why it doesn't change... */
    line->rear = tmp;           /* ...this */
}

void add_item_to_last_person(line_t* line, char item_name[20], double item_price, int item_units){
    if(line->rear == NULL){
        /* no person in line */
        return;
    }

    item_t* tmp = (item_t*)malloc(sizeof(item_t));
    int i;
    /* fill in variables with item information */
    for(i = 0; item_name[i] != '\0'; i++){
        tmp->item_name[i] = item_name[i];
    }
    tmp->price = item_price;
    tmp->quantity = item_units;
    
    tmp->next_item = NULL;
    if(line->rear->first_item == NULL){
        line->rear->first_item = line->rear->last_item = tmp;
        return;
    }
    line->rear->last_item->next_item = tmp;
    line->rear->last_item = tmp;
}

void parse_text_line(line_t* line, char *str){
    int i, x, str_index, position;
    str_index = position = 0;
    char temp[30];

    /* item variables */
    char item_name[20];
    double item_price;
    int quantity;

    /* person variables */
    char person_name[20];
    double balance;

    /* while loop until end character(\0) is reached */
    while(str[str_index] != '\0'){
        /* waits for first open bracket to be encountered */
        if(str[str_index] == '{'){
            /* waits for closing bracket to be found */
            while(str[str_index] != '}'){
                /* gets person name and item name from inside the quotation marks ("") */
                if(str[str_index] == '\"'){
                    str_index++;
                    i = 0;
                    while(str[str_index] != '\"'){
                        /* position 0 is the first spot in the array therefore it must be the name */
                        if(position == 0){
                            person_name[i] = str[str_index];
                            i++;
                        }
                        /* positions greater than 0 must be the item name(only enters while loop if inside quotation marks) */
                        else if(position % 2 == 0){
                            item_name[i] = str[str_index];
                            i++;
                        }
                        else{
                            if(position < 2){
                                return;
                            }
                            else{
                                return;
                            }
                        }
                        str_index++;
                        if(str[str_index] == '\0'){
                            add_person_to_line(line, "emtpy", -1);
                            return;
                        }
                    }
                    if(position == 0){
                        person_name[i] = '\0';
                        position++;
                    }
                    else if(position % 2 == 0){
                        item_name[i] = '\0';
                        position++;
                    }
                    else{
                        if(position < 2){
                            // printf("person name not valid\n");
                            return;
                        }
                        else{
                            // printf("item name not valid\n");
                            return;
                        }
                        // break;
                    }
                }
                /* gets BALANCE or ITEM PRICE from input string(or second position from inside the {}) */
                if(str[str_index] == ','){
                    str_index++;
                    i = 0;
                    while(str[str_index] != ','){
                        if(position == 1){
                            temp[i] = str[str_index];
                            i++;
                        }
                        else if(position % 2 == 1){
                            temp[i] = str[str_index];
                            i++;
                        }
                        else{
                            if(position < 3){
                                // printf("invalid balance\n");
                                if(line->rear->name != person_name){
                                    add_person_to_line(line, "no customer", 0);
                                }
                                line->rear->balance = -1;
                                return;
                            }
                            else{
                                line->rear->first_item->price = -1;
                                return;
                            }
                            break;
                        }
                        if(str[str_index] == '}' && position < 2){
                            add_person_to_line(line, person_name, balance);
                            line->rear->total_items = 0;
                            return;
                        }
                        str_index++;
                        if(str[str_index] == '\0'){
                            add_person_to_line(line, "emtpy", -1);
                            return;
                        }
                    }
                    /* second position(1) must be the balance */
                    if(position == 1){
                        temp[i] = '\0';
                        balance = atof(temp);
                        add_person_to_line(line, person_name, balance);
                        line->rear->total_items = 0;
                        line->rear->total_cost = 0;
                        position++;
                    }
                    /* any other position would be the item's price */
                    else if(position % 2 == 1){
                        temp[i] = '\0';
                        item_price = atof(temp);
                        position++;
                    }
                    else{
                        if(position < 3){
                            // printf("invalid balance\n");
                            line->rear->balance = -1;
                            return;
                        }
                        else{
                            // printf("invalid price\n");
                            line->rear->first_item->price = -1;
                            return;
                        }
                        // printf("invalid input\n");
                        // break;
                    }
                }
                /* final position would be person's inventory of items(this gets ignore hence position>3) or the quantity of the item */
                if(str[str_index] == ',' && position > 3){
                    x = str_index;
                    x++;
                    i = 0;
                    while(str[x] != '}'){
                        temp[i] = str[x];
                        i++;
                        x++;
                        if(str[str_index] == '\0'){
                            line->rear->balance = -1;
                            return;
                        }
                    }
                    temp[i] = '\0';
                    quantity = atoi(temp);
                    line->rear->total_cost += (double)quantity * item_price;
                    line->rear->total_items += quantity;
                    /* adds an item to the last person in line */
                    add_item_to_last_person(line, item_name, item_price, quantity);
                }
                if(str[str_index] == '}' && position < 3){
                    line->rear->total_items = -1;
                    return;
                }
                str_index++;
                if(str[str_index] == '\0'){
                    add_person_to_line(line, "emtpy", -1);
                    return;
                }
            }
        }
        str_index++;
    }
}

void remove_front_line_person(line_t* line){
    if(line == NULL){
        return;
    }

    customer_t* tmp = line->front;
    line->front = line->front->next;

    if(line->front == NULL){
        line->rear = NULL;
    }

    free(tmp);
}

void process_checkout_line(line_t* line, FILE* output){
    while(line->front != NULL){
        /* process person at the front line */
        if(line->front->balance == -1){
            fprintf(output, "check input\n");
        }
        else if(line->front->total_items == 0){
            fprintf(output, "%s does not have any items.\n", line->front->name);
        }
        else if(line->front->first_item->price == -1){
            fprintf(output, "check item input for %s\n", line->front->name);
        }
        else if((line->front->balance - line->front->total_cost) < 0){
            if(line->front->total_items <= 10){
                fprintf(output, "%s was rejected at the express register\n", line->front->name);
            }
            else{
                fprintf(output, "%s was rejected at the regular register\n", line->front->name);
            }
        }
        else{
            fprintf(output, "%s paid $%.2lf for ", line->front->name, line->front->total_cost);
            while(line->front->first_item !=  NULL){
                fprintf(output, "%d %s", line->front->first_item->quantity, line->front->first_item->item_name);
                next_item(line->front);
                if(line->front->first_item != NULL){
                    fprintf(output, ", ");
                }
            }
            if(line->front->total_items < 10){
                fprintf(output, " at the express register\n");
            }
            else{
                fprintf(output, " at the regular register\n");
            }
        }
        remove_front_line_person(line);
    }
}