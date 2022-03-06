#include <stdio.h>
#include <stdlib.h>

#define nameLen 30              /* max name char length */
#define M 100                   /* hash table size (max items in inventory) */
#define PRIME 47                /* prime number must follow: PRIME < M */

/* inventory items */
typedef struct inventoryItem{
    int key;                    /* item's identification number */
    char name[nameLen];         /* name of item */
    int threshold;              /* point at which the store needs to order more of that item */
    int stock;                  /* # of items in stock */
    float price;                /* the price of that item  */
}item_t;

/* grocery item */
typedef struct gItems{
    int key;                    /* key that correctly corresponds to the item's key in the inventory */
    int amount;                 /* the number of that item being purchased */
}groceryItem_t;

/* customers in the check-out queue */
typedef struct storeCustomer{
    char name[nameLen];         /* customer's name (does not have to be unique) */
    float cash;                 /* amount of money they have */
    struct storeCustomer *next; /* points to next person in line (queue) */
    groceryItem_t *gItems[M];    /* list of gItems the customer is wanting to buy */
}cust_t;

/* checkout line queue */
typedef struct checkoutLine{
    cust_t *front, *back;       /* cust_t pointer to front and back of line queue */
}line_t;

/* stack used to determine if brackets are balanced */
typedef struct bracketStack{
    char character;             /* bracket character */
    struct bracketStack *next;  /* points to next bracket */
}bs_t;

item_t *parseItemRecord(char itemRecord[]);
int doubleHash(int key, int hashIndex);
void insertInventory(item_t *inventory[], item_t *item);
item_t* findInventory(item_t *inventory[], int key);
void printInventory(item_t *inventory[]);
int promptMainMenu(item_t *inventory[]);
int inventoryMenu(item_t *inventory[]);
int str_cmp(char* str1, char* str2);
void clearBuffer();
void push_ips(bs_t **top, char character);
int pop_ips(bs_t **top);
int isBracketBalanced(char str[1000]);
cust_t *parseCustomerRecord(char customerRecord[]);
line_t *createLine();
void lineCustomer(line_t *line, cust_t *customer);
void removeCustomer(line_t *line);
void processCheckoutLine(FILE *customerFile, item_t *inventory[], line_t *line);
line_t *loadCustomers(char *fcustomer);
void updateItemStock(item_t *inventory[], int key, int amount);
void printWarnings(item_t *inventory[]);
int deleteItem(item_t *inventory[], int key);
void restockAll(item_t *inventory[]);

int main(void){
    item_t* inventory[M];
    for(int i = 0; i < M; i++){
        inventory[i] = NULL;
    }
    char item_record[1000];
    FILE* inventoryFile = fopen("inventory.txt", "r");

    /* loads inventory into system */
    while (fgets(item_record, sizeof(item_record), inventoryFile)){
        item_t *tmp = parseItemRecord(item_record);
        insertInventory(inventory, tmp);
        // printf("%s\n", tmp->name);
    }
    fclose(inventoryFile);

    while(promptMainMenu(inventory));
    // while(inventoryMenu(inventory));

    return 0;   
}

/* parse item record into item_t struct */
item_t *parseItemRecord(char itemRecord[]){
    item_t *item = malloc(sizeof *item);
    int i = 0,              /* dummy index */
    flag = 0;               /* field empty flag */

    /* ignore whitespace */
    while(itemRecord[i] == ' '){
        i++;
    }

    if(itemRecord[i++] != '{'){
        printf("Bad Item input!\n");
        exit(0);
    }


    /* ----------------item->key---------------- */
    /* ignore whitespace */
    while(itemRecord[i] == ' '){
        i++;
    }
    char tmp[5];
    int j = 0;
    /* check key input is correct */
    while('0' <= itemRecord[i] && itemRecord[i] <= '9'){
        tmp[j++] = itemRecord[i++];
        flag = 1;
    }
    if(!flag){
        printf("Empty item key field!\n");
        exit(0);
    }
    flag = 0;
    tmp[j] = '\0';
    item->key = atoi(tmp);

    /* ignore whitespace */
    while(itemRecord[i] == ' '){
        i++;
    }

    /* check commas */
    if(itemRecord[i] != ','){
        printf("Bad Item input!\n");
        exit(0);
    }


    /* ----------------item->name---------------- */
    /* ignore whitespace */
    while(itemRecord[++i] == ' ');

    if(itemRecord[i++] == '\"'){
        j = 0;
        /* check item name is correct */
        while(itemRecord[i] != '\"' && itemRecord[i] != '\0'){
            item->name[j++] = itemRecord[i++];
            flag = 1;
        }
        if(!flag){
            printf("Empty item name field!\n");
            exit(0);
        }
        flag = 0;
    }
    item->name[j] = '\0';

    /* ignore whitespace */
    while(itemRecord[++i] == ' ');

    /* check commas */
    if(itemRecord[i] != ','){
        printf("Bad Item input!\n");
        exit(0);
    }


    /* -------------item->threshold------------- */
    /* ignore whitespace */
    while(itemRecord[++i] == ' ');

    j = 0;
    /* check key input is correct */
    while('0' <= itemRecord[i] && itemRecord[i] <= '9'){
        tmp[j++] = itemRecord[i++];
        flag = 1;
    }
    if(!flag){
        printf("Empty item threshold field!\n");
        exit(0);
    }
    flag = 0;
    tmp[j] = '\0';
    item->threshold = atoi(tmp);

    /* ignore whitespace */
    while(itemRecord[i] == ' '){
        i++;
    }

    /* check commas */
    if(itemRecord[i] != ','){
        printf("Bad Item input!\n");
        exit(0);
    }


    /* ---------------item->stock--------------- */
    /* ignore whitespace */
    while(itemRecord[++i] == ' ');

    j = 0;
    /* check key input is correct */
    while('0' <= itemRecord[i] && itemRecord[i] <= '9'){
        tmp[j++] = itemRecord[i++];
        flag = 1;
    }
    if(!flag){
        printf("Empty item stock field!\n");
        exit(0);
    }
    flag = 0;
    tmp[j] = '\0';
    item->stock = atoi(tmp);

    /* ignore whitespace */
    while(itemRecord[i] == ' '){
        i++;
    }

    /* check commas */
    if(itemRecord[i] != ','){
        printf("Bad Item input!\n");
        exit(0);
    }


    /* ---------------item->price--------------- */
    /* ignore whitespace */
    while(itemRecord[++i] == ' ');

    j = 0;
    /* check key input is correct */
    while(('0' <= itemRecord[i] && itemRecord[i] <= '9') || itemRecord[i] ==  '.'){
        tmp[j++] = itemRecord[i++];
        flag = 1;
    }
    if(!flag){
        printf("Empty item price field!\n");
        exit(0);
    }
    flag = 0;
    tmp[j] = '\0';
    item->price = atof(tmp);

    /* ignore whitespace */
    while(itemRecord[i] == ' '){
        i++;
    }

    /* check close bracket */
    if(itemRecord[i] != '}'){
        printf("Bad Item input!\n");
        exit(0);
    }


    return item;
}

/* double hash method; returns index */
int doubleHash(int key, int hashIndex){
    /* [(key mod TABLE_SIZE) + INDEX(PRIME - (key mod PRIME))] mod TABLE_SIZE */
    /* PRIME < TABLE_SIZE */
    return ((key % M) + hashIndex*(PRIME - (key % PRIME))) % M;
}

/* add item to inventory (hash table) */
void insertInventory(item_t *inventory[], item_t *item){
    /* hash index (increment by 1 if collision occurs) */
    int hashIndex = 1;

    /* index from item->key using double hash */
    int index = doubleHash(item->key, hashIndex);

    /* collision */
    if(inventory[index] != NULL){
        while(1){
            /* new index using new hashIndex in hash function */
            index = doubleHash(item->key, ++hashIndex);

            /* empty spot found (collision avoided) */
            if(inventory[index] == NULL){
                inventory[index] = item;
                return;
            }
        }
    }
    /* no collision */
    else{
        inventory[index] = item;
        return;
    }
}

/* find item in inventory (hash table) */
item_t* findInventory(item_t *inventory[], int key){
    /* hash index (increment by 1 if collision occurs) */
    int hashIndex = 1;

    for(hashIndex = 0; hashIndex < M; hashIndex++){
        if(inventory[hashIndex] == NULL || inventory[hashIndex]->key != key){
            continue;
        }
        return inventory[hashIndex];
    }
    return NULL;

    // /* index from key using double hash */
    // int index = doubleHash(key, hashIndex);

    // /* collision */
    // if(inventory[index]->key != key){
    //     while(1){
    //         /* new index using new hashIndex in hash function */
    //         index = doubleHash(key, ++hashIndex);

    //         /* found key */
    //         if(inventory[index]->key == key){
    //             return inventory[index];
    //         }
    //     }
    // }
    // /* no collision */
    // else{
    //     return inventory[index];
    // }
}

/* print hash table */
void printInventory(item_t *inventory[]){
    /* loop through index of inventory table */
    for(int i = 0; i < M; i++){
        /* index empty */
        if(inventory[i] == NULL){
            /* skip */
            continue;
        }
        /* print item */
        printf("%d - %-4d %-15s %d\t%d\t%.2f\n", i, inventory[i]->key, inventory[i]->name, inventory[i]->threshold, inventory[i]->stock, inventory[i]->price);
    }
}

/* main menu prompt */
int promptMainMenu(item_t *inventory[]){
    char option[50];
    printf("\nPlease choose an option. The paranthesis indicate input values\n");
    printf("\tcheckout (filename.txt)\n");
    printf("\tinventory\n");
    printf("\tquit\n");
    printf("> ");
    scanf(" %s", option);

    if(str_cmp(option, "checkout")){
        /* checkout filename input */
        scanf(" %s", option);
        clearBuffer();

        /* ------------------process checkout line------------------ */
        /* load customers to check out line */
        line_t *line = loadCustomers(option);
        printf(" 1 test %p\n", line);
        if(line == NULL){
            printf("2 test\n");
            printf("File name %s does not exist!\n", option);
            return 1;
        }

        /* print receipt */
        FILE *customerFile = fopen("receipt.txt", "w");
        while(line->front != NULL){
            processCheckoutLine(customerFile, inventory, line);
            removeCustomer(line);
        }
        fclose(customerFile);
        printf("Checked out successfully!\n");

        /* print any items below threshold */
        printWarnings(inventory);
        
        return 1;
    }
    else if(str_cmp(option, "inventory")){
        clearBuffer();
        while(inventoryMenu(inventory));
        return 1;
    }
    else if(str_cmp(option, "quit")){
        clearBuffer();
        printf("quitting...!\n");
        return 0;
    }
    clearBuffer();
    printf("Unknown action. Try again!\n");
    return 1;
}

/* display inventory submenu */
int inventoryMenu(item_t *inventory[]){
    char option[10];

    printf("\n\tSelect from the inventory submenu\n");
    printf("\t\tadd (key) (name) (threshold) (stock) (price)\n");
    printf("\t\tdelete (key)\n");
    printf("\t\trestock (key) (amount)\n");
    printf("\t\trestock all\n");
    printf("\t\treturn to main menu\n\t> ");
    scanf(" %s", option);


    if(str_cmp(option, "add")){
        item_t *tmp = malloc(sizeof *tmp);
        scanf(" %d %s %d %d %f", &(tmp->key), tmp->name, &(tmp->threshold), &(tmp->stock), &(tmp->price));
        clearBuffer();
        // printf("\t%d %s %d %d %.2f\n", tmp->key, tmp->name, tmp->threshold, tmp->stock, tmp->price);

        /* adds item to inventory */
        insertInventory(inventory, tmp);

        printf("\tItem added successfully!\n");
        return 1;
    }
    else if(str_cmp(option, "delete")){
        int key = -1;
        scanf(" %d", &key);
        clearBuffer();

        /* todo: delete key */
        if(!deleteItem(inventory, key)){
            printf("\tItem with key (%-.3d) does not exist\n", key);
            return 1;
        }
        printf("\tItem deleted successfully!\n");

        return 1;
    }
    else if(str_cmp(option, "restock")){
        scanf(" %s", option);
        if(str_cmp(option, "all")){
            clearBuffer();

            restockAll(inventory);

            printf("\trestocking all\n");
            return 1;
        }
        else{
            /* amount */
            int amount;
            scanf(" %d", &amount);
            clearBuffer();
            if (!findInventory(inventory, atoi(option))){
                printf("\tItem (%-.3d) does not exist! Item not restocked!\n", atoi(option));
                return 1;
            }
            updateItemStock(inventory, atoi(option), amount);
            
            printf("\tRestocked item successfully!\n");
            return 1;
        }
    }
    else if(str_cmp(option, "return")){
        clearBuffer();
        /* todo: return to main menu */

        return 0;
    }

    clearBuffer();
    printf("\tUnknown action. Try Again!\n");
    return 1;
}

/* compare two strings */
int str_cmp(char* str1, char* str2){
    int index = 0;
    while(str1[index] != '\0' && str2[index] != '\0'){
        if(str1[index] != str2[index]){
            /* strings are not the same */
            return 0;
        }
        index++;
    }
    if(str1[index] == '\0' && str2[index] == '\0'){
        return 1;
    }
    return 0;
}

/* clear scanf buffer */
void clearBuffer(){
    while(getchar() != '\n');
}

/* push character onto bracketStack */
void push_ips(bs_t **top, char character){

    /* dynamically allocate new node and initialize data */
    bs_t *tmp = malloc(sizeof *tmp);
    tmp->character = character;

    /* push new node on top of current stack */
    tmp->next = (*top);
    (*top) = tmp;
}

/* pop character from bracketStack */
int pop_ips(bs_t **top){

    /* bracketStack is empty (cannot pop) */
    if(*top == NULL){
        return 0;
    }
    
    bs_t *tmp;

    /* pop top */
    tmp = *top;
    *top = (*top)->next;

    /* free (deallocate) previous top */
    free(tmp);

    return 1;
}

/* check if brackets are balanced */
int isBracketBalanced(char str[1000]){
    /* declare and initialize charStack */
    bs_t *tmp = NULL;

    /* loop through entire string */
    for(int i = 0; str[i] != '\0'; i++){

        /* open bracket */
        if(str[i] == '{' || str[i] == '['){
            /* push currcent char to bracket stack */
            push_ips(&tmp, str[i]);
        }

        /* closing bracket */
        if(str[i] == '}' || str[i] == ']'){
            /* bracketStack has corresponding open bracket i.e. [] or {} AND NOT [} or {] */
            if((tmp != NULL) && ((tmp->character == '{' && str[i] == '}' ) || (tmp->character == '[' && str[i] == ']'))){
                /* pop bracket */
                pop_ips(&tmp);
            }
            else{
                /* unbalanced */
                return 0;
            }
        }
    }
    /* balanced */
    return 1;
}

/* parse customer record into cust_t struct */
cust_t *parseCustomerRecord(char customerRecord[]){
    /* brackets unbalanced */
    if(!isBracketBalanced(customerRecord)){
        /* quit program */
        printf("Bad Customer record input!\n");
        exit(0);
    }

    /* begin parse */
    /* format:  {"NAME", CASH, [GROCERY_LIST: {KEY, AMOUNT}]} */
    /* example: {"Karen", 3.00, [{102, 3}, {216, 1}]} */
    cust_t *tmpCustomer = malloc(sizeof *tmpCustomer);
    int i = 0,              /* dummy index */
    flag = 0;               /* empty field flag */

    /* ignore whitespace */
    while(customerRecord[i] == ' '){
        i++;
    }

    if(customerRecord[i++] != '{'){
        printf("Bad Item input!\n");
        exit(0);
    }


    /* ----------------tmpCustomer->name---------------- */
    /* ignore whitespace */
    while(customerRecord[i] == ' '){
        i++;
    }
    
    char tmp[5];
    int j = 0;

    if(customerRecord[i++] == '\"'){
        j = 0;
        /* check item name is correct */
        while(customerRecord[i] != '\"' && customerRecord[i] != '\0'){
            tmpCustomer->name[j++] = customerRecord[i++];
            flag = 1;
        }
        if(!flag){
            printf("Empty item name field!\n");
            exit(0);
        }
        flag = 0;
    }
    tmpCustomer->name[j] = '\0';

    /* ignore whitespace */
    while(customerRecord[++i] == ' ');

    /* check commas */
    if(customerRecord[i] != ','){
        printf("Bad Customer input!\n");
        exit(0);
    }


    /* ----------------tmpCustomer->cash---------------- */
    /* ignore whitespace */
    while(customerRecord[++i] == ' ');

    j = 0;
    /* check cash input is correct */
    while(('0' <= customerRecord[i] && customerRecord[i] <= '9') || customerRecord[i] ==  '.'){
        tmp[j++] = customerRecord[i++];
        flag = 1;
    }
    if(!flag){
        printf("Empty customer price field!\n");
        exit(0);
    }
    flag = 0;
    tmp[j] = '\0';
    tmpCustomer->cash = atof(tmp);

    /* ignore whitespace */
    while(customerRecord[i] == ' '){
      i++;
    }

    /* check close bracket */
    if(customerRecord[i] != ','){
        printf("Bad customer input!\n");
        exit(0);
    }

    /* ----------------tmpCustomer->gitems[M]---------------- */
    /* {"Karen", 3.00, [{102, 3}, {216, 1}]} */

    groceryItem_t *itm = NULL;
    int numItems = 0;

    /* ignore whitespace */
    while(customerRecord[++i] == ' ');

    if(customerRecord[i] != '['){
        printf("Bad Item input!\n");
        exit(0);
    }

    while(customerRecord[i] != '\0'){
        /* allocate space for grocery item */
        itm = malloc(sizeof *itm);
        /* -----------------------itm->key----------------------- */

        /* ignore whitespace */
        while(customerRecord[++i] == ' ');

        if(customerRecord[i] != '{'){
            printf("Bad Item input!\n");
            exit(0);
        }

        /* ignore whitespace */
        while(customerRecord[++i] == ' ');

        j = 0;
        /* check key input is correct */
        while('0' <= customerRecord[i] && customerRecord[i] <= '9'){
            tmp[j++] = customerRecord[i++];
            flag = 1;
        }
        if(!flag){
            printf("Empty customer item key field!\n");
            exit(0);
        }
        flag = 0;
        tmp[j] = '\0';
        itm->key = atoi(tmp);

        /* ignore whitespace */
        while(customerRecord[i] == ' '){
            i++;
        }

        /* check comma */
        if(customerRecord[i] != ','){
            printf("Bad customer input!\n");
            exit(0);
        }


        /* ----------------------itm->amount--------------------- */

        /* ignore whitespace */
        while(customerRecord[++i] == ' ');

        j = 0;
        /* check amount input is correct */
        while('0' <= customerRecord[i] && customerRecord[i] <= '9'){
            tmp[j++] = customerRecord[i++];
            flag = 1;
        }
        if(!flag){
            printf("Empty customer grocery item amount field!\n");
            exit(0);
        }
        flag = 0;
        tmp[j] = '\0';
        itm->amount = atoi(tmp);

        /* ignore whitespace */
        while(customerRecord[i] == ' '){
            i++;
        }

        /* check close bracket */
        if(customerRecord[i] != '}'){
            printf("Bad customer input!\n");
            exit(0);
        }

        /* ignore whitespace */
        while(customerRecord[++i] == ' ');

        /* done parsing */
        if(customerRecord[i] == ']'){
            // printf("%s %d %d\n", tmpCustomer->name, itm->key, itm->amount);
            tmpCustomer->gItems[numItems] = itm;
            tmpCustomer->gItems[++numItems] = NULL;
            break;
        }

        /* check comma */
        if(customerRecord[i] != ','){
            printf("Bad customer input!\n");
            exit(0);
        }
        
        /* add item to customer's grocery list */
        tmpCustomer->gItems[numItems++] = itm;

        // printf("%s %d %d\n", tmpCustomer->name, itm->key, itm->amount);
    }

    return tmpCustomer;

}

/* create customer checkout line */
line_t *createLine(){
    line_t *newLine = malloc(sizeof *newLine);
    newLine->front = newLine->back = NULL;
    return newLine;
}

/* add customer to checkout line */
void lineCustomer(line_t *line, cust_t *customer){
    /* line (queue) is empty */
    if(line->front == NULL){
        /* front and back of line are the same customer */
        line->front = line->back = customer;
        return;
    }
    // printf("test %d\n", (*line)->front->gItems[0]->amount);

    line->back->next = customer;
    line->back = customer;
}

/* remove(dequeue) front customer from line (queue) */
void removeCustomer(line_t *line){
    if(line->front == NULL){
        return;
    }

    cust_t* tmp = line->front;
    line->front = line->front->next;

    if(line->front == NULL){
        line->back = NULL;
    }

    free(tmp);
}

/* process customer checkout file */
void processCheckoutLine(FILE *customerFile, item_t *inventory[], line_t *line){
    /* print customer's name to receipt file */
    fprintf(customerFile, "Customer - %s\n\n", line->front->name);

    float totalCost = 0;
    int item = 0;

    /* get customer in front of line */
    cust_t *currentCustomer = line->front;

    /* loops through all grocery items in customer's grocery list */
    while(1){
        /* temp item being processed */
        item_t *dummyItem = findInventory(inventory, currentCustomer->gItems[item]->key);
        if(dummyItem == NULL){
            fprintf(customerFile, "item with key (%-.3d) does not exist.\n", currentCustomer->gItems[item]->key);
            item++;
            continue;
        }

        /* totalCost += AMOUNT * ITEM_COST */
        totalCost += (currentCustomer->gItems[item]->amount) * (dummyItem->price);

        /* print items to receipt file */
        fprintf(customerFile, "%s x%d @ $%.2f\n", dummyItem->name, currentCustomer->gItems[item]->amount, dummyItem->price);

        /* reached end of grocery list */
        if(currentCustomer->gItems[++item] == NULL){
            /* print customer's total cost of items to receipt file */
            fprintf(customerFile, "\nTotal: $%.2f\n", totalCost);

            /* customer does not have sufficient funds */
            if(totalCost > currentCustomer->cash){
                fprintf(customerFile, "Customer did not have enough money and was REJECTED\n");
                item = 0;
                while(1){
                    /* de-allocate item (remove item from customer's grocery list) */
                    free(currentCustomer->gItems[item]);
                    currentCustomer->gItems[item] = NULL;

                    /* reached end of grocery list */
                    if(currentCustomer->gItems[++item] == NULL) break;
                }   
            }
            /* sufficient funds, remove from stock */
            else{
                item = 0;
                while(1){
                    /* update item's stock according to purchase amount */
                    updateItemStock(inventory, currentCustomer->gItems[item]->key, -(currentCustomer->gItems[item]->amount));

                    /* de-allocate item (remove item from customer's grocery list) */
                    free(currentCustomer->gItems[item]);
                    currentCustomer->gItems[item] = NULL;

                    /* reached end of grocery list */
                    if(currentCustomer->gItems[++item] == NULL) break;
                }    
            }
            fprintf(customerFile, "Thank you, come back soon!\n-------------------------------------------------------\n\n");
            break;
        }
    }
}

/* load customers in file to line */
line_t *loadCustomers(char *fcustomer){
    FILE *customerFile = fopen(fcustomer, "r");
    if(!customerFile){
        printf("No such file as %s\n", fcustomer);
        return NULL;
    }

    line_t *newLine = createLine();

    char customerRecord[1000];

    /* loads customers into system */
    while (fgets(customerRecord, sizeof(customerRecord), customerFile)){
        cust_t *cust = parseCustomerRecord(customerRecord);
        cust->next = NULL;
        lineCustomer(newLine, cust);
    }
    fclose(customerFile);

    return newLine;
}

/* update item's stock */
void updateItemStock(item_t *inventory[], int key, int amount){
    /* find item in inventory */
    item_t *tmp = findInventory(inventory, key);

    /* item was not found */
    if(tmp == NULL){
        return;
    }

    /* update stock by amount */
    tmp->stock += amount;

    /* stock is negative */
    if(tmp->stock < 0){
        /* update stock to 0 */
        tmp->stock = 0;
    }
}

/* print item's who's stock is below their threshold value */
void printWarnings(item_t *inventory[]){
    int warning = 0;
    /* loop through index of inventory table */
    for(int i = 0; i < M; i++){
        /* index empty */
        if(inventory[i] == NULL){
            /* skip */
            continue;
        }
        if(inventory[i]->stock < inventory[i]->threshold){
            if(warning == 0){
                printf("\nWarning! The following Item(s) may need to be restocked:\n");
                warning++;
            }
            printf("%3.3d (%s): %d remain in stock, replenishment threshold is %d\n", inventory[i]->key, inventory[i]->name, inventory[i]->stock, inventory[i]->threshold);
        }
    }
}

/* remove item from inventory (hash table) */
int deleteItem(item_t *inventory[], int key){
    for(int i = 0; i < M; i++){
        if(inventory[i] == NULL){
            continue;
        }
        if(inventory[i]->key == key){
            free(inventory[i]);
            inventory[i] = NULL;
            return 1;
        }
    }
    return 0;
}

/*  */
void restockAll(item_t *inventory[]){
    for(int i = 0; i < M; i++){
        if(inventory[i] == NULL){
            continue;
        }

        if(inventory[i]->threshold > inventory[i]->stock){
            updateItemStock(inventory, inventory[i]->key, inventory[i]->threshold - inventory[i]->stock);
            printf("\t%s (key: %-.3d) restocked! Threshold = %d\tStock = %d\n", inventory[i]->name, inventory[i]->key, inventory[i]->threshold, inventory[i]->stock);
        }

    }
}


/*  */


/*  */