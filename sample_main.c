#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    char fname[30];
    char lname[30];
}name;
typedef struct {
    int day,month,year;
}date;
typedef struct {
    char door_no[10];
    char address_line1[100];
    char city[20];
    char state[20];
}address;
typedef struct {
    char login_name[100];
    char password[100];
}credentials;
typedef struct {
    name s_name;
    address s_address;
    char phone_no[11];

}seller;
typedef struct {
    int u_ID;
    int p_ID;
    int o_ID;
}counters;
counters main_counter={0,0,0};
typedef struct {
    int u_ID;
    name u_name;
    address u_address;
    int prime;
    char phone_no[11];
    char email_id[20];
    char password[20];
    int i;
    int o_ID[100];
}user;
typedef struct{
    int p_ID;
    char p_name[30];
    char descr[100];
    int no_of_products;
    float price;
    float rating;
    int discount;
    seller p_seller;
}product;
typedef struct{
    int o_ID;
    int u_ID;
    int p_ID;
    user o_user;
    product o_product;
    address shipping_address;
}order;

struct user_list{
    user data;
    struct user_list *next;
};

struct user_list *user_front =NULL, *user_end=NULL, *user_temp=NULL;
void write_counters(counters c)
{
    FILE *write = fopen("data/counters.dat","w");
    if(write == NULL)
    {
        printf("File couldn't be created\n");
        exit(EXIT_FAILURE);
    }
    fwrite(&c,sizeof(counters),1,write);
    fclose(write);
}
void read_counters()
{
    FILE *read = fopen("data/counters.dat","r");
    if(read == NULL)
    {
        printf("File doesn't exist\n");
        exit(EXIT_FAILURE);
    }
    fread(&main_counter,sizeof(counters),1,read);
    fclose(read);
}
int login_admin()
{
    char login_name[100],password[100];
    char check_login[100],check_password[100];
    FILE *read_login;
    printf("Enter Login Name: ");
    fflush(stdin);
    gets(login_name);
    printf("Enter Password: ");
    fflush(stdin);
    gets(password);
    if((read_login = fopen("data/admin_login.txt","r")) == NULL)
    {
        printf("Couldn't find Admin details\n");
        exit(EXIT_FAILURE);
    }
    fscanf(read_login,"%s %s",check_login,check_password);
    fclose(read_login);
    if(!strcmp(check_login,login_name) && !strcmp(check_password,password))
        return TRUE;
return FALSE;
}
int login_user()
{
    char login_name[100],password[100];
    int match = 0;
    printf("Enter Email ID: ");
    gets(login_name);
    printf("Enter Password: ");
    fflush(stdin);
    gets(password);
    user_temp = user_front;
    while(user_temp != NULL)
    {
        if(strcmp(user_temp->data.email_id,login_name) == 0 && strcmp(user_temp->data.password,password) == 0)
        {
            match = 1;
            break;
        }
        user_temp = user_temp->next;
    }
    if(match == 1)
        return TRUE;
return FALSE;
}
void insert_user_tolist()
{
    if(user_front == NULL)
    {
        user_front = user_temp;
        user_end = user_temp;
    }
    else
    {
        user_end->next = user_temp;
        user_end = user_temp;
    }
}
void write_user(user u)
{
    FILE *register_user = fopen("data/user_details.dat","a");
    if(register_user == NULL)
    {
        printf("cannot created a file\n");
        exit(EXIT_FAILURE);
    }
    fwrite(&u, sizeof(user),1,register_user);
    fclose(register_user);
}
void user_register()
{
    user usr;
    user_temp = (struct user_list *)malloc(sizeof(struct user_list));
    char password1[20],password2[20];
    //read_counters();
    main_counter.u_ID++;
    usr.u_ID = main_counter.u_ID;
    printf("Enter your Details\n\n");
    printf("First Name: ");
    fflush(stdin);
    gets(usr.u_name.fname);
    fflush(stdin);
    printf("Last Name: ");
    gets(usr.u_name.lname);
    fflush(stdin);
    printf("Address\n");
    printf("Door No: ");
    gets(usr.u_address.door_no);
    fflush(stdin);
    printf("Address line 1: ");
    gets(usr.u_address.address_line1);
    fflush(stdin);
    printf("City: ");
    gets(usr.u_address.city);
    fflush(stdin);
    printf("State: ");
    gets(usr.u_address.state);
    fflush(stdin);
    printf("Enter Email ID: ");
    gets(usr.email_id);
    printf("Enter phone number: ");
    gets(usr.phone_no);
    fflush(stdin);
    reenter_password:
    printf("Password: ");
    gets(password1);
    fflush(stdin);
    printf("Reenter Password: ");
    gets(password2);
    fflush(stdin);
    if(strcmp(password1,password2) != 0)
    {
        printf("Passwords dont match Enter again\n");
        goto reenter_password;
    }
    usr.prime = 0;
    user_temp->data = usr;
    user_temp->next = NULL;
    insert_user_tolist();
    write_counters(main_counter);
    write_user(usr);
    printf("Registration Successful\n");
    system("pause");
}
void load_users()
{
    FILE *load_user=fopen("data/user_details.dat","r");
    int i = main_counter.u_ID;
    user loader;
    while(i>0)
    {
        fread(&loader,sizeof(user),1,load_user);
        user_temp = (struct user_list*)malloc(sizeof(struct user_list));
        user_temp->next = NULL;
        user_temp->data = loader;
        insert_user_tolist();
        i--;
    }
    fclose(load_user);
}
void view_users()
{
    user_temp = user_front;
    printf("USER ID \tUSER NAME \tEMAIL ID\n");
    while(user_temp != NULL)
    {
        printf("%7d\t",user_temp->data.u_ID);
        printf("%9s\t",user_temp->data.u_name.fname);
        printf("%10s\n",user_temp->data.email_id);
        user_temp = user_temp->next;
    }
    system("pause");
}
void manage_users()
{
    while(1)
    {
        int ch;
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1.Add User\n2.View Users\n3.Delete User by ID\n4.View User detail by ID\n5.Set User Priority\n6.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            user_register();
            break;
        case 2:
            view_users();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            return;
        default:
            printf("Wrong Choice entered\n");
        }
;    }
}
void admin_home()
{
    int ch;
    while(1)
    {
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1. Manage Users\n2.Manage Products\nManage Orders\n4.Logout\n\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            manage_users();
            break;
        case 2:
            //manage_products();
            break;
        case 3:
            //manage_orders();
            break;
        case 4:
            return;
        default:
            printf("Wrong option Entered, Try again.\n");

        }
    }
}

int main()
{
    int ch1,ch2,user_wrong_login=0,admin_wrong_login=0;
    FILE *load_impt = fopen("data/counters.dat","r");
    if(load_impt == NULL)
    {
        write_counters(main_counter);
    }
        fclose(load_impt);
    read_counters();
    load_users();
    while(1)
    {
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1.Admin Login\n2.User Login/Register\n3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&ch1);
        switch(ch1)
        {
        case 1:
            admin_login_again:
            if(login_admin())
            {
                admin_wrong_login = 0;
                admin_home();
            }
            else
            {
                printf("Login Credentials are wrong. Enter again\n");
                admin_wrong_login++;
                if(admin_wrong_login <= 3)
                    goto admin_login_again;
            }
            break;
        case 2:
            while(1)
            {
                system("cls");
                printf("1.Login\n2.Sign up\n3.Exit\n\n");
                printf("Enter your choice: ");
                scanf("%d",&ch2);
                switch(ch2)
                {
                case 1:
                    user_login_again:
                    if(login_user())
                    {
                        user_wrong_login = 0;
                        //user_home();
                    }
                    else
                    {
                        printf("Login credentials are wrong. Enter again\n");
                        user_wrong_login++;
                        if(user_wrong_login <= 3)
                            goto user_login_again;
                    }
                    break;
                case 2:
                    user_register();
                    break;
                case 3:
                    goto exit_loop;
                    break;
                default:
                    printf("Wrong Option entered. Try again\n");
                }
            }
            exit_loop:
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Wrong option Entered\n");
        }

    }
    free(user_front);
    free(user_temp);
    free(user_end);
    return 0;
}
