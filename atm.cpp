#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string>
#include <stdbool.h>

#define FILENAME_SIZE 1000
#define MAX_LINE 2000

// screen1 = Start screen
// screen2 = Log In start screen
// screen3 = Log In menu screen
// screen4 = Log In Withdraw screen
// screen5 = Log in Transfer screen
// screen5 = Don't have an account yet? Create One screen

struct Data{
    int account_number;
    int money;
};

void dash(int n);   // Prints n amount of dash.
int read_file(Data d[100]);   // Reads data.txt every time you go to the main menu and returns number of lines in data.txt + 1.
void update_file(int a, Data d[100], int b);   // Updates data.txt with changed money.
bool check_option(int a, int b, int c);   // Checks whether the option you selected is correct.
int matching_account_number(int a, int b, Data d[100]);   // Checks whether the account number you typed exists in data.txt
                                                          // and returns corresponding line number.
void create_account_number(int a, int b);   // Creates a new account number and deposits money for the first time.
void see_file(int a, Data d[100]);   // Returns all the account numbers and corresponding balances.

int main(void)
{   
    struct Data d[100];

    int start = 1;   // start = 1 means turning on the atm; start = 0 means turning off the atm.
    int line_num = 0;   // number of lines in data.txt  
    int start_menu = 0;

    int my_account_number = 0;   
    int correct = 0;   // line number for corresponding account number
    int login_menu = 0;
    int deposit = 0;   // amount of money you want to deposit
    int money_deposit = 0;   // money + deposit
    int withdraw = 0;   // amount of money you want to withdraw
    int money_withdraw = 0;   // money - withdraw
    int receiver_account_number = 0;
    int receiver = 0;   // line number for corresponding receiver's account number
    int transfer = 0;   // amount of money you want to transfer
    int money_transfer_sender = 0;   // money + transfer
    int money_transfer_receiver = 0;   // money - transfer

    int new_account_number = 0; 
    int new_money = 0; 
    
    int password = 0;   // password for admin
    
    dash(40);
    printf("Welcome to Be Rich bank.\n");
    dash(40);
    printf("Please choose one of the options below.\n");

    screen1:   
        while(start)
        {   
            dash(40);
            printf("1. Log In\n");
            printf("2. Don't have an account yet? Create One\n");
            printf("3. Admin\n");
            printf("4. Shut Down\n");
            dash(40);

            line_num = read_file(d) - 1;

            scanf("%d", &start_menu);  

            if (check_option(start_menu, 1, 4) == false)
            {
                goto screen1;
            }

            switch (start_menu)   
            {
                case 1: 
                {   
                    screen2:
                        printf("Enter your account number.\n");
                        scanf("%d", &my_account_number);

                        if (matching_account_number(line_num, my_account_number, d) != -1)
                        {
                            correct = matching_account_number(line_num, my_account_number, d);
                            goto screen3;
                        }

                        printf("The account number does not exist\n");
                        goto screen2;

                        screen3:
                            printf("Please choose one of the options below.\n");
                            dash(40);
                            printf("1. Check balance\n");
                            printf("2. Deposit\n");
                            printf("3. Withdraw\n");
                            printf("4. Transfer\n");
                            printf("5. Go back to the main menu\n");
                            dash(40);

                            scanf("%d", &login_menu);  

                            if (check_option(login_menu, 1, 5) == false)
                            {
                                goto screen3;
                            }

                            switch (login_menu)   
                            {
                                case 1: 
                                {
                                    printf("Your balance is $%d\n", d[correct].money);
                                    break;
                                }

                                case 2:
                                {
                                    printf("Enter the amount of money you want to deposit.\n");
                                    scanf("%d", &deposit);

                                    money_deposit = d[correct].money + deposit;
                                    
                                    update_file(correct, d, money_deposit);

                                    dash(40);
                                    printf("Now, your balance is $%d\n", money_deposit);
                                    
                                    break;
                                }

                                case 3:
                                {
                                    if (d[correct].money <= 0)
                                    {
                                        printf("You cannot withdraw any money becasue your balance is 0.\n");
                                        goto screen3;
                                    }

                                    screen4:
                                        printf("Enter the amount of money you want to withdraw\n");
                                        printf("(amount of money you can withdraw is $%d)\n", d[correct].money);
                                        scanf("%d", &withdraw);

                                        if(withdraw > d[correct].money)
                                        {
                                            printf("Your withdraw money exceeds your balance.\n");
                                            goto screen4;
                                        }

                                        money_withdraw = d[correct].money - withdraw;

                                        update_file(correct, d, money_withdraw);

                                        dash(40);
                                        printf("Now, your balance is $%d\n", money_withdraw);

                                        break;
                                }

                                case 4:
                                {
                                    printf("Enter the account number that you want to send your money to.\n");
                                    scanf("%d", &receiver_account_number);

                                    if (receiver_account_number == d[correct].account_number)
                                    {
                                        printf("You cannot transfer to the same account number\n");
                                        goto screen3;
                                    }

                                    if (matching_account_number(line_num, receiver_account_number, d) != -1)
                                    {
                                        receiver = matching_account_number(line_num, receiver_account_number, d);
                                        goto screen5;
                                    }

                                    printf("The account number does not exist\n");
                                    goto screen3;
                                    
                                    screen5:
                                        printf("Enter the amount of money you want to transfer.\n");
                                        printf("(amount of money you can transfer is $%d)\n", d[correct].money);
                                        scanf("%d", &transfer);

                                        if(transfer > d[correct].money){
                                            printf("Your transfer money exceeds your balance.\n");
                                            goto screen5;
                                        }

                                        // sender
                                        money_transfer_sender = d[correct].money - transfer;

                                        update_file(correct, d, money_transfer_sender);

                                        // receiver
                                        money_transfer_receiver = d[receiver].money + transfer;

                                        update_file(receiver, d, money_transfer_receiver);

                                        dash(40);
                                        printf("Now, your balance is $%d\n", money_transfer_sender);

                                        break;
                                }

                                case 5:
                                {
                                    break; 
                                }
                            }
                        break;
                }

                case 2: 
                {   
                    screen6:
                        printf("Enter an account number you want to use (5 digits).\n");

                        scanf("%d", &new_account_number);

                        if (check_option(new_account_number, 10000, 99999) == false)
                        {
                            printf("The account number is too short or too long.\n");
                            goto screen6;
                        }
                       
                        if (matching_account_number(line_num, new_account_number, d) != -1)
                        {
                            printf("The account number already exists\n");
                            goto screen1;
                        }

                        create_account_number(new_account_number, new_money);
                        
                        break;
                }
                
                case 3: 
                {
                    printf("Enter the password.\n");
                    scanf("%d", &password);
                    
                    if (password == 9999)   // Admin password = 9999
                    {   
                        dash(40);
                        see_file(line_num, d);
                    }
                    else
                    {
                        printf("Incorrect password.\n");
                    }
                    break;
                }

                case 4: 
                {
                    dash(40);
                    printf("Thank you for using Be Rich bank.\n");
                    dash(40);
                    start = 0;
                    break;
                } 
            }
        }
    return 0;
}

void dash(int n){
    for (int i = 0; i < n; i++){
        printf("-");
    }
    printf("\n");
}

int read_file(Data d[100]){
    int n = 0;

    FILE *f = fopen("data.txt", "r");

    while (!feof(f)) {
        fscanf(f, "%d %d", &d[n].account_number, &d[n].money);
        n++;
    }
    fclose(f);

    return n;
}

void update_file(int a, Data d[100], int b){
    char account_number[100];
    char money[100];
    char temp_f[FILENAME_SIZE];
    char buffer[MAX_LINE];
    char replace[MAX_LINE];
    int replace_line_num = 0;
    bool keep_reading = true;
    int current_line = 1;

    strcpy(temp_f, "temp");
    strcat(temp_f, "data.txt");

    replace_line_num = a + 1;

    fflush(stdin);

    sprintf(account_number, "%d", d[a].account_number);   // convert int to str
    sprintf(money, "%d", b);   // convert int to str
                    
    strcpy(replace, strcat(strcat((strcat(account_number, " ")),money),"\n"));   // concatenate strs

    FILE *f = fopen("data.txt", "r");
    FILE *t = fopen(temp_f, "w");

    do 
    {
        fgets(buffer, MAX_LINE, f);   // read file into buffer
        
        if (feof(f)){
            keep_reading = false;   // at the end of data.txt, stop reading
        } 
        else if (replace_line_num == current_line){   // when you it reaches the replace line, write the replace in temp_f
            fputs(replace, t);
        }
        else{
            fputs(buffer, t);   // otherwise, write the line in temp_f
        } 
        current_line++;
    } while (keep_reading);

    fclose(f);
    fclose(t);

    remove("data.txt");
    rename(temp_f, "data.txt");
}

bool check_option(int a, int b, int c){
    if (a < b || a > c )   
    {
        return false;   // when the option is out of range, it returns false.
    }
    return true;
}

int matching_account_number(int a, int b, Data d[100]){
    for (int n = 0; n < a; n++)
    {
        if (b == d[n].account_number)
        {
            return n;
        }
    }
    return -1;   // when there is no matching account number, it returns -1.
}

void create_account_number(int a, int b){
    FILE *f = fopen("data.txt", "a+");

    fprintf(f, "%d ", a);   

    printf("Enter the amount of money you want to deposit.\n");
    scanf("%d", &b);

    fprintf(f, "%d", b);

    char next_line[100] = "\n";   // next line
    fprintf(f, "%s", next_line);

    fclose(f);
}

void see_file(int a, Data d[100]){
    for (int n = 0; n < a; n++)
    {
        printf("Account number : %d, balance : $%d\n", d[n].account_number, d[n].money);
    }
}