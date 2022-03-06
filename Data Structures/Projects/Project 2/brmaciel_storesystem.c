#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    int ID;                         // (key/value) Unique 4 digit number (0-9999). ignore trailling zeros
    char name[100];
    float store_balance;            // store credit accrued
    float order_total;              // total cost of order
}customer_t;

typedef struct customer_bst{
    customer_t *root;
    struct customer_bst *left, *right;
}customer_bst_t;

int prompt_user(customer_bst_t** customer_bst);
int str_cmp(char* str1, char* str2);
int file_exists(const char *fname);
customer_t* new_customer(int ID, char *name, float store_balance);
customer_bst_t* create_customer_bst();
void add_customer_to_bst(customer_bst_t* customer_bst, customer_t* customer);
customer_t* customer_search(customer_bst_t* customer_bst, int customer_ID);
customer_bst_t* find_smallest_node(customer_bst_t* customer_bst);
customer_bst_t* find_largest_node(customer_bst_t* customer_bst);
customer_bst_t* delete_customer(customer_bst_t* customer_bst, int customer_ID);
void parse_customers(char* str, customer_t* customer);
void parse_orders(char* str, customer_bst_t* custoemr_bst);
int process(FILE *order_file, customer_bst_t* customer_bst);
void print_preorder(customer_bst_t* customer_bst, FILE* fout);
void print_postorder(customer_bst_t* customer_bst, FILE* fout);
void print_inorder(customer_bst_t* customer_bst, FILE* fout);

int main(void){
    char cust_info[1000];
    customer_bst_t* customer_bst = create_customer_bst();
    FILE* fcustomers = fopen("customers.txt", "r");

    // loads everything into system
    while (fgets(cust_info, sizeof(cust_info), fcustomers)){
        customer_t* c_tmp = (customer_t*)malloc(sizeof(customer_t));
        parse_customers(cust_info, c_tmp);
        add_customer_to_bst(customer_bst, c_tmp);
    }
    fclose(fcustomers);

    while(prompt_user(&customer_bst) != 4);

    return 0;
}

// prompts user for options
int prompt_user(customer_bst_t** customer_bst){
    char str_input[100];
    char str_tmp[10], name[100];
    int index, tmp_index, tmp_id;
    float balance;
    index = tmp_index = 0;

    printf("\nPlease choose an option. The paranthesis indicate input values\n");
    printf("\tadd (ID) (name) (balance)\n");
    printf("\tdelete (ID)\n");
    printf("\tprocess (filename)\n");
    printf("\tquit\n");
    printf("input> ");
    scanf(" %[^\n]s", str_input);

    while(str_input[index] != '\0'){
        str_tmp[tmp_index++] = str_input[index++];
        if(str_input[index] == ' ' || str_input[index] == '\0'){
            if(str_cmp(str_tmp, "add")){
                // parse the rest for add

                // first part is ID
                tmp_index = 0;
                while(str_input[++index] != ' '){
                    str_tmp[tmp_index++] = str_input[index];
                    if(str_input[index] == '\0'){
                        printf("Bad add input (maybe ID or name missing)\n");
                        return 0;
                    }
                }
                if(tmp_index != 4){
                    printf("Bad add input (check ID contains 4 digits including 0's)\n");
                    return 0;
                }
                str_tmp[tmp_index] = '\0';
                tmp_id = atoi(str_tmp);

                // second part is name
                tmp_index = 0;
                while(str_input[++index] != ' '){
                    name[tmp_index++] = str_input[index];
                    if(str_input[index] == '\0'){
                        printf("Bad add input (maybe name or balance missing)\n");
                        return 0;
                    }
                }
                name[tmp_index] = '\0';

                // third part is store balance
                tmp_index = 0;
                while(str_input[++index] != '\0'){
                    if(('0' <= str_input[index] && str_input[index] <= '9') || str_input[index] == '.'){
                        // make sure input is a number with decimal
                        str_tmp[tmp_index++] = str_input[index];
                    }
                    else{
                        printf("Bad add input (maybe balance)\n");
                        return 0;
                    }
                }
                str_tmp[tmp_index] = '\0';
                add_customer_to_bst(*customer_bst, new_customer(tmp_id, name, atof(str_tmp)));
                return 1;

            }
            else if(str_cmp(str_tmp, "delete")){
                // parse the rest for delete
                tmp_index = 0;
                while(str_input[++index] != '\0'){
                    str_tmp[tmp_index++] = str_input[index];
                    if(str_input[index] == ' '){
                        printf("Bad delete input (make sure there are no extra spaces)\n");
                        return 0;
                    }
                }
                if(tmp_index != 4){
                    printf("bad delete input (check ID contains 4 digits including 0's)\n");
                    return 0;
                }
                *customer_bst = delete_customer(*customer_bst, atoi(str_tmp));
                str_tmp[tmp_index] = '\0';
            }
            else if(str_cmp(str_tmp, "process")){
                // parse the rest for process
                tmp_index = 0;
                while(str_input[++index] != '\0'){
                    str_tmp[tmp_index++] = str_input[index];
                    if(str_input[index] == ' '){
                        printf("Bad process input (make sure there are no extra spaces)\n");
                        return 0;
                    }
                }
                str_tmp[tmp_index] = '\0';
                if(!file_exists(str_tmp)){
                    // file does not exist
                    printf("Given order text file does not exist.\n");
                    return 0;
                }
                FILE* tmp_file = fopen(str_tmp, "r");
                process(tmp_file, *customer_bst);
            }
            else if(str_cmp(str_tmp, "quit")){
                // quit
                FILE* fout = fopen("newcustomers.txt", "w");
                if(fout == NULL){
                    // could not open fout file
                    printf("could not upen output file.\n");
                    return 0;
                }
                tmp_id = -1;
                while(tmp_id == -1){
                    tmp_id = 0;
                    printf("output> Please enter format: pre, post, or in order\ninput> ");
                    scanf(" %s", str_tmp);

                    if(str_cmp(str_tmp, "pre")){
                        // print out in pre order
                        printf("output> writing to newcustomers.txt in pre-order, shutting down...\n");
                        print_preorder(*customer_bst, fout);
                        printf("Done!\n");
                    }
                    else if(str_cmp(str_tmp, "post")){
                        // print out in post order
                        printf("output> writing to newcustomers.txt in post-order, shutting down...\n");
                        print_postorder(*customer_bst, fout);
                        printf("Done!\n");
                    }
                    else if(str_cmp(str_tmp, "in")){
                        // print out in in order
                        printf("output> writing to newcustomers.txt in in-order, shutting down...\n");
                        print_inorder(*customer_bst, fout);
                        printf("Done!\n");
                    }
                    else{
                        // bad input
                        printf("Bad output format. Please try again.\n");
                        tmp_id = -1;
                    }
                }
                fclose(fout);
                return 4;
            }
            else{
                // bad input
                printf("bad input. Try again.\n");
                return 0;
            }
        }
    }
    str_input[0] = '\0';
    return 1;
}

// compare string
int str_cmp(char* str1, char* str2){
    int index = 0;
    while(str1[index] != '\0' && str2[index] != '\0'){
        if(str1[index] != str2[index]){
            // string not the same
            return 0;
        }
        index++;
    }
    return 1;
}

// check file exists
int file_exists(const char *fname){
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

// create new customer struct given ID, NAME, and STORE_BALANCE
customer_t* new_customer(int ID, char *name, float store_balance){
    // allocate memory for new customer
    customer_t* tmp_customer = (customer_t*)malloc(sizeof(customer_t));
    int i = 0;

    // fill new customer information
    tmp_customer->ID = ID;
    while(name[i] != '\0'){
        tmp_customer->name[i] = name[i];
        i++;
    }
    tmp_customer->name[i] = '\0';
    tmp_customer->store_balance = store_balance;
    tmp_customer->order_total = 0;

    return tmp_customer;
}

// create customer binary search tree
customer_bst_t* create_customer_bst(){
    // allocate memory for customer binary search tree
    customer_bst_t* customer_bst = (customer_bst_t*)malloc(sizeof(customer_bst_t));
    
    // set root and left and right nodes of root to NULL
    customer_bst->root = NULL;
    customer_bst->left = NULL;
    customer_bst->right = NULL;

    return customer_bst;
}

// add customer to binary search tree
void add_customer_to_bst(customer_bst_t* customer_bst, customer_t* customer){
    if(customer_bst == NULL){
        printf("Please allocate space for bst first. \n");
        return;
    }

    if(customer_bst->root == NULL){
        // customer bst is NULL (empty), set customer bst root to customer
        customer_bst->root = customer;
        customer_bst->left = customer_bst->right = NULL;
        return;
    }
    else if(customer->ID < customer_bst->root->ID){
        // customer's ID being added is LESS than root's ID, so customer is added to the left
        if(customer_bst->left == NULL){
            // allocate space in root's left child if empty
            customer_bst->left = (customer_bst_t*)malloc(sizeof(customer_bst_t));
            customer_bst->left->root = NULL;
        } 
        add_customer_to_bst(customer_bst->left, customer);
    }
    else if(customer->ID > customer_bst->root->ID){
        // customer's ID being added is GREATER than root's ID, so customer is added to the right
        if(customer_bst->right == NULL){
            // allocate space in root's right child if empty
            customer_bst->right = (customer_bst_t*)malloc(sizeof(customer_bst_t));
            customer_bst->right->root = NULL;
        }
        add_customer_to_bst(customer_bst->right, customer);
    }
    else{
        if(customer->ID == customer_bst->root->ID){
            printf("Error: ID %.4d is already taken.\n", customer->ID);
            return;
        }
        printf("Error: could not add customer to system (ID: %.4d\tName: %s)\n", customer->ID, customer->name);
    }
}

// search for customer in the binary search tree using customer ID
customer_t* customer_search(customer_bst_t* customer_bst, int customer_ID){
    if(customer_bst == NULL || customer_bst->root == NULL){
        // customer ID not found in binary search tree
        // printf("Customer ID %d not found in customer binary search tree.\n", customer_ID);
        return NULL;
    }

    if(customer_bst->root->ID == customer_ID){
        // empty customer binary search tree
        return customer_bst->root;
    }
    else if(customer_ID < customer_bst->root->ID){
        // searches LEFT side of binary search tree
        return customer_search(customer_bst->left, customer_ID);
    }
    else if(customer_ID > customer_bst->root->ID){
        // searches RIGHT side of binary search tree
        return customer_search(customer_bst->right, customer_ID);
    }
    else{
        // error occurred
        return NULL;
    }

}

//find the node with the smallest ID
customer_bst_t* find_smallest_node(customer_bst_t* customer_bst){
    if(customer_bst == NULL){
        // customer bst is empty
        printf("Customer bst is empty.\n");
        return NULL;
    }
    
    if(customer_bst->left != NULL){
        return find_smallest_node(customer_bst->left);
    }
    else{
        return customer_bst;
    }
}

// find the node with the largest ID
customer_bst_t* find_largest_node(customer_bst_t* customer_bst){
    if(customer_bst == NULL){
        // customer bst is empty
        printf("Customer bst is empty.\n");
        return NULL;
    }

    if(customer_bst->right != NULL){
        return find_largest_node(customer_bst->right);
    }
    else{
        return customer_bst;
    }
    
}

// delete customer from the customer binary search tree using ID
customer_bst_t* delete_customer(customer_bst_t* customer_bst, int customer_ID){
    if(!customer_search(customer_bst, customer_ID)){
        // customer cannot be deleted because it does not exist
        printf("Deletion failed! Customer with ID %d does not exist in BST.\n", customer_ID);
        return customer_bst;
    }

    if(customer_ID < customer_bst->root->ID){
        // left
        customer_bst->left = delete_customer(customer_bst->left, customer_ID);
    }
    else if(customer_ID > customer_bst->root->ID){
        // right
        customer_bst->right = delete_customer(customer_bst->right, customer_ID);
    }
    else if(customer_bst->left != NULL && customer_bst->right != NULL){
        // customer found (has both children)
        customer_bst_t* tmp = find_largest_node(customer_bst->left);
        customer_t* cust_tmp = customer_bst->root;
        customer_bst->root = tmp->root;
        free(cust_tmp);
        customer_bst->left = delete_customer(customer_bst->left, tmp->root->ID);
    }
    else{
        // customer found (has no children or one child)
        customer_bst_t* tmp = customer_bst;
        if(customer_bst->left == NULL && customer_bst->right == NULL){
            // no left or right child
            // point to NULL
            customer_bst->root =  NULL;
            return customer_bst;
        }
        else if(customer_bst->left != NULL){
            // no left child but has right child
            // replace bst with right bst child
            customer_bst =  customer_bst->left;
        }
        else{
            // no right child but has left child
            // replace bst with left bst child
            customer_bst = customer_bst->right;
        }
        // de allocate space given for the bst
        free(tmp);
    }
    return customer_bst;
}

// parse customer text file
void parse_customers(char* str, customer_t* customer){
    int str_len, index, tmp_index;
    char letter, tmp[100];
    index = tmp_index = 0;

    while(str[index] != '\0'){
        if(str[index] == '{'){
            // start of parse
            index++;

            // first part is ID
            while(str[index] == ' '){
                // ignore white space
                index++;
            }
            while('0' <= str[index] && str[index] <= '9'){
                // make sure first item is a number
                tmp[tmp_index] = str[index];
                index++;
                tmp_index++;
            }
            if(tmp_index != 4){
                printf("Bad Customer input (maybe ID)\n");
                return;
            }
            tmp[tmp_index] = '\0';
            customer->ID = atoi(tmp);
            // printf("ID: %.4d\n", customer->ID);
            
            // second part is name
            while(str[index] == ' '){
                // ignore white space
                index++;
            }
            if(str[index] == ','){
                // comma is found
                index++;
                while(str[index] == ' '){
                    // ignore white space
                    index++;
                }
                if(str[index] == '\"'){
                    // first quotations found, start of name
                    index++;
                    tmp_index = 0;
                    while(str[index] != '\"'){
                        tmp[tmp_index] = str[index];
                        tmp_index++;
                        index++;
                        if(str[index] == '\0'){
                            // end of string
                            printf("Bad customer input (maybe customer name)\n");
                            return;
                        }
                    }
                    tmp[tmp_index] = '\0';
                    tmp_index = 0;
                    while(tmp[tmp_index] != '\0'){
                        customer->name[tmp_index] = tmp[tmp_index];
                        tmp_index++;
                    }
                    customer->name[tmp_index] = '\0';
                    // printf("Name: %s\n", customer->name);
                }
                else{
                    printf("Bad Customer input (maybe customer name)\n");
                    return;
                }
            }
            // third part is store balance
            index++;
            while(str[index] == ' '){
                // ignore white space
                index++;
            }
            if(str[index] == ','){
                index++;
                while(str[index] == ' '){
                    // ignore white space
                    index++;
                }
                tmp_index = 0;
                while(('0' <= str[index] && str[index] <= '9') || str[index] == '.'){
                    // make sure first item is a number
                    tmp[tmp_index] = str[index];
                    index++;
                    tmp_index++;
                }
                tmp[tmp_index] = '\0';
                customer->store_balance = atof(tmp);
                // printf("Store Balance: %.2f\n\n", customer->store_balance);
            }
        }
        if(str[index] != '\0'){
            index++;
        }
    }

}

// parse order text line
void parse_orders(char* str, customer_bst_t* customer_bst){
    int str_len, index, tmp_index, ID;
    char letter, tmp[100];
    index = tmp_index = 0;

    while(str[index] != '\0'){
        if(str[index] == '{'){
            // start of parse
            index++;

            // first part is ID
            while(str[index] == ' '){
                // ignore white space
                index++;
            }
            while('0' <= str[index] && str[index] <= '9'){
                // make sure first item is a number
                tmp[tmp_index] = str[index];
                index++;
                tmp_index++;
            }
            if(tmp_index != 4){
                printf("Bad order input (maybe ID)\n");
                return;
            }
            tmp[tmp_index] = '\0';
            ID = atoi(tmp);
            customer_t* tmp_cst = customer_search(customer_bst, ID);
            if(tmp_cst == NULL){
                // customer does not exist
                printf("Could not process order, ID %.4d does not exist.\n", ID);
                return ;
            }
            
            // second part is order total
            while(str[index] == ' '){
                // ignore white space
                index++;
            }
            if(str[index] == ','){
                index++;
                while(str[index] == ' '){
                    // ignore white space
                    index++;
                }
                tmp_index = 0;
                while(('0' <= str[index] && str[index] <= '9') || str[index] == '.'){
                    // make sure first item is a number
                    tmp[tmp_index] = str[index];
                    index++;
                    tmp_index++;
                }
                if(tmp_index != 5){
                    printf("Bad order input (maybe store balance)\n");
                    return;
                }
                tmp[tmp_index] = '\0';
                tmp_cst->order_total = atof(tmp);
            }
            
            // process order
            if(tmp_cst->store_balance >= tmp_cst->order_total){
                // store balance can fully cover order total
                printf("Customer %.4d, %s, payed $%.2f from their store balance and $%.2f at the register, $%.2f remaining store balance\n", tmp_cst->ID, tmp_cst->name, tmp_cst->order_total, 0.0, tmp_cst->store_balance - tmp_cst->order_total);
                tmp_cst->store_balance = tmp_cst->store_balance - tmp_cst->order_total;
            }
            else{
                // store balance cannot fully cover order total (cash is needed)
                printf("Customer %.4d, %s, payed $%.2f from their store balance and $%.2f at the register, $%.2f remaining store balance\n", tmp_cst->ID, tmp_cst->name, tmp_cst->store_balance, tmp_cst->order_total - tmp_cst->store_balance, 0.0);
                tmp_cst->store_balance = 0.0;
            }
        }
        if(str[index] != '\0'){
            index++;
        }
    }

}

// process order file
int process(FILE *order_file, customer_bst_t* customer_bst){
    if(customer_bst->root == NULL || customer_bst == NULL){
        // customer bst is empty
        printf("Could not process order file, customer database is empty.\n");
        return 1;
    }
    char txt_line[1000];
    while (fgets(txt_line, sizeof(txt_line), order_file)){
        parse_orders(txt_line, customer_bst);
    }
    return 0;
}

// print pre order (root, left, right) from customer bst
void print_preorder(customer_bst_t* customer_bst, FILE* fout){
    if(customer_bst == NULL || customer_bst->root == NULL){
        // end of customer bst or empty
        return;
    }

    fprintf(fout, "{%.4d, \"%s\", %.2f}\n", customer_bst->root->ID, customer_bst->root->name, customer_bst->root->store_balance);  
    print_preorder(customer_bst->left, fout);   
    print_preorder(customer_bst->right, fout); 
}

// print post order (left, right, root) from customer bst
void print_postorder(customer_bst_t* customer_bst, FILE* fout){
    if(customer_bst == NULL || customer_bst->root == NULL){
        // end of customer bst or empty
        return;
    }

    print_postorder(customer_bst->left, fout);
    print_postorder(customer_bst->right, fout);
    fprintf(fout, "{%.4d, \"%s\", %.2f}\n", customer_bst->root->ID, customer_bst->root->name, customer_bst->root->store_balance);
}
  
// print in order (left, root, right) from customer bst
void print_inorder(customer_bst_t* customer_bst, FILE* fout){
    if(customer_bst == NULL || customer_bst->root == NULL){
        // end of customer bst or empty
        return ;
    }

    print_inorder(customer_bst->left, fout);
    fprintf(fout, "{%.4d, \"%s\", %.2f}\n", customer_bst->root->ID, customer_bst->root->name, customer_bst->root->store_balance);
    print_inorder(customer_bst->right, fout);
}
