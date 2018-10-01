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
    char check_login[100],check_password[100];
    FILE *read_login;
    credentials input;
    printf("Enter Login Name: ");
    gets(login_name);
    printf("Enter Password: ");
    fflush(stdin);
    gets(password);
    user_temp = user_front;

    if((read_login = fopen("data/user_login.dat","r")) == NULL)
    {
        printf("Couldn't find User Database\n");
        exit(EXIT_FAILURE);
    }
    while(fread(&input,sizeof(credentials), 1, read_login))
    {
        if(!strcmp(input.login_name,login_name) && !strcmp(input.password,password))
        {
            fclose(read_login);
            return TRUE;
        }
    }
    fclose(read_login);
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
    user_temp->data = usr;
    user_temp->next = NULL;
    insert_user_tolist();
    write_counters(main_counter);
    write_user(usr);
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
        scanf("%d",&ch1);
        switch(ch1)
        {
        case 1:
            admin_login_again:
            if(login_admin())
            {
                admin_wrong_login = 0;
                //admin_home();
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
                printf("1.Login\n2.Sign up\n3.Logout\n\n");
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
    return 0;
}
