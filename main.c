#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#define TRUE 1
#define FALSE 0

typedef struct {
    char fname[30];
    char lname[30];
}name;

typedef struct {
    int day,month,year;
}dat;

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
    int o_p_ID;
}counters;

counters main_counter={0,0,0,0};

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
    int nooforders;
}user;

typedef struct{
    int p_ID;
    char p_name[30];
    char descr[100];
    int no_of_products;
    float price;
    float rating;
    int daystodeliver;
   // int discount;
    seller p_seller;
}product;

typedef struct{
    int o_ID;
    int u_ID;
    int p_ID;
    user o_user;
    product o_product;
    dat o_date;
}order;

struct product_list{
    product data;
    struct product_list *next;
    struct product_list *prev;
};

struct order_list{
    order data;
    struct order_list *next;
    struct order_list *prev;
};

user currentusr;

typedef struct order_list ORDER;
ORDER *order_front =NULL, *order_end = NULL, *order_temp = NULL;
ORDER *order_p_front = NULL, *order_p_end = NULL, *order_p_temp = NULL;

int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};
typedef struct product_list PRODUCT;
PRODUCT *product_front =NULL, *product_end=NULL, *product_temp=NULL;
dat curdate;
time_t t = time(NULL);
struct tm tm = *localtime(&t);

curdate.day = tm.tm_mday;
curdate.month = tm.tm_mon+1;
curdate.year = tm.tm_year + 1900;
void insert_product_tolist()
{
    if(product_front == NULL)
    {
        product_front = product_temp;
        product_end = product_temp;
    }
    else
    {
        product_end->next = product_temp;
        product_temp->prev = product_end;
        product_end = product_temp;
    }
}

struct user_list{
    user data;
    struct user_list *next;
    struct user_list *prev;
};

typedef struct user_list USER;

USER* get_user()
{
    USER *temp;
    temp = (USER*)malloc(sizeof(USER));
    if(temp == NULL)
    {
        printf("Insufficient memory\n");
        exit(EXIT_FAILURE);
    }
    return temp;
};

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

USER *user_front =NULL, *user_end=NULL, *user_temp=NULL;

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
        user_temp->prev = user_end;
        user_end = user_temp;
    }
}
void write_order_file()
{
    FILE *orders = fopen("data/order_details.dat","w");
    order t;
    order_temp = order_front;
    while(order_temp!=NULL)
    {
        t = order_temp->data;
        fwrite(&t,sifeof(order),1,orders);
        order_temp = order_temp->next;
    }
    fclose(orders);
}
void load_users()
{
    FILE *load_user=fopen("data/user_details.dat","r");
    int i = main_counter.u_ID;
    user loader;
    while(i>0)
    {
        fread(&loader,sizeof(user),1,load_user);
        user_temp = (USER*)malloc(sizeof(USER));
        user_temp->next = NULL;
        user_temp->prev = NULL;
        user_temp->data = loader;
        insert_user_tolist();
        i--;
    }
    fclose(load_user);
}

void load_products()
{
    FILE *load_product=fopen("data/product_details.dat","r");
    int i = main_counter.p_ID;
    product loader;
    while(i>0)
    {
        fread(&loader,sizeof(product),1,load_product);
        product_temp = (PRODUCT*)malloc(sizeof(PRODUCT));
        product_temp->next = NULL;
        product_temp->prev = NULL;
        product_temp->data = loader;
        insert_product_tolist();
        i--;
    }
    fclose(load_product);
}
int count_leap_years(dat d)
{
    int years = d.year;
    if(d.month<=2)
        years--;
    return years/4-years/100+years/400;
}
int difference(dat date, int daystodeliver)
{
    int i,dif;
    unsigned long int n1,n2;
    n1 = date.year*365 + date.day
    for(i=0;i<date.month-1;i++)
        n1+= monthDays[i];
    n1 += count_leap_years(date);

    n2 = curdate.year*365 + curdate.day;
    for(i=0;i<curdate.month-1;i++)
        n2+=monthDays[i];
    n2+= count_leap_years(curdate);
    dif = n2-n1;
    if(dif >= daystodeliver)
        return 0;
    else
        return daystodeliver-diff;

}
void load_orders()
{
    FILE *load_order=fopen("data/order_details.dat","r");
    int i = main_counter.o_ID,noofdays;
    order loader;
    while(i>0)
    {
        fread(&loader,sizeof(order),1,load_order);
        order_temp = (ORDER*)malloc(sizeof(ORDER));
        if(loader.o_product.daystodeliver > 0)
        {
            noofdays = difference(loader.o_date,loader.o_product.daystodeliver);
            loader.o_product.daystodeliver = noofdays;
        }
        loader.o_user = updated_user(loader.o_user);
        order_temp->next = NULL;
        order_temp->prev = NULL;
        order_temp->data = loader;
        insert_order_tolist();
        i--;
    }
    fclose(load_product);
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
            currentusr = user_temp->data;
            break;
        }
        user_temp = user_temp->next;
    }

    if(match == 1)
        return TRUE;

    return FALSE;
}

void write_user(user u)
{
    FILE *register_user = fopen("data/user_details.dat","a");

    if(register_user == NULL)
    {
        printf("cannot create a file\n");
        exit(EXIT_FAILURE);
    }
    fwrite(&u, sizeof(user),1,register_user);
    fclose(register_user);
}

void user_register()
{
    user usr;
    user_temp = (USER *)malloc(sizeof(USER));
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
    usr.nooforders = 0;

    if(strcmp(password1,password2) != 0)
    {
        printf("Passwords dont match Enter again\n");
        goto reenter_password;
    }
    usr.prime = 0;
    user_temp->data = usr;
    user_temp->next = NULL;
    user_temp->prev = NULL;
    insert_user_tolist();
    write_counters(main_counter);
    write_user(usr);
    printf("Registration Successful\n");
    system("pause");
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

void displayele(USER *ptr)
{
    printf("DETAILS\n");
    printf("-------\n");
    printf("User ID: %d\n",ptr->data.u_ID);
    printf("User Name: %s %s\n",ptr->data.u_name.fname, ptr->data.u_name.lname);
    printf("Email ID: %s\n",ptr->data.email_id);
    printf("Address: %s %s %s %s\n",ptr->data.u_address.door_no, ptr->data.u_address.address_line1, ptr->data.u_address.address_line1,ptr->data.u_address.address_line1);
    printf("Phone Number: %s\n",ptr->data.phone_no);
    printf("\n");
}

int deleteinlist(int uid)
{
    char ch;
    user_temp = user_front;

    if(user_front == NULL)
        return FALSE;
    else if(user_front->next == NULL)
    {
        if(user_front->data.u_ID == uid)
        {
            displayele(user_front);
            printf("Do you wanna delete the above user(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch == 'Y' || ch =='y')
            {
                user_front = NULL;
                user_end = NULL;
                free(user_temp);
                return TRUE;
            }
        }
    }
    else
    {
        if(user_front->data.u_ID == uid)
        {
            displayele(user_front);
            printf("Do you wanna delete the above user(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);

            if(ch=='Y' || ch=='y')
            {
                user_temp = user_front;
                user_front = user_front->next;
                user_front->prev = NULL;
                free(user_temp);
                return TRUE;
            }

        }
        else if(user_end->data.u_ID == uid)
        {
            displayele(user_end);
            printf("Do you wanna delete the above user(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch == 'Y' || ch=='y')
            {
                user_temp = user_end;
                user_end = user_end->prev;
                user_end->next = NULL;
                free(user_temp);
                return TRUE;
            }
        }
        else
        {
            while(user_temp!=NULL)
            {
                if(user_temp->data.u_ID == uid)
                {
                    displayele(user_temp);
                    printf("Do you wanna delete the above user(Y/N)");
                    fflush(stdin);
                    scanf("%c",&ch);
                    if(ch == 'Y' || ch =='y')
                    {
                        user_temp->prev->next = user_temp->next;
                        user_temp->next->prev = user_temp->prev;
                        free(user_temp);
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

void deleteinfile(int uid)
{
    FILE *user_data = fopen("data/user_details.dat","w");
    USER *temporary;
    user t2;
    temporary = user_front;

    while(temporary!= NULL)
    {
        t2 = temporary->data;
        fwrite(&t2,sizeof(user),1,user_data);
        temporary = temporary->next;
    }
    fclose(user_data);
}

void write_product(product p)
{
    FILE *register_product = fopen("data/product_details.dat","a");

    if(register_product == NULL)
    {
        printf("cannot created a file\n");
        exit(EXIT_FAILURE);
    }
    fwrite(&p, sizeof(product),1,register_product);
    fclose(register_product);
}

void product_register()
{
    product pd;
    product_temp = (struct product_list *)malloc(sizeof(struct product_list));
    char password1[20],password2[20];
    //read_counters();
    main_counter.p_ID++;
    pd.p_ID = main_counter.p_ID;
    printf("Enter your Details\n\n");
    printf("Product Name: ");
    fflush(stdin);
    gets(pd.p_name);
    printf("Describe the Product\n");
    fflush(stdin);
    gets(pd.descr);
    printf("Product Remaining: ");
    fflush(stdin);
    scanf("%d",&pd.no_of_products);
    printf("Enter the Price of Product: ");
    fflush(stdin);
    scanf("%f",&pd.price);
    printf("Enter number of days to deliver: ");
    fflush(stdin);
    scanf("%d",&pd.daystodeliver);
    pd.rating=0.0;
    printf("Enter the Seller First Name: ");
    fflush(stdin);
    gets(pd.p_seller.s_name.fname);
    fflush(stdin);
    printf("Enter the Seller Last Name: ");
    gets(pd.p_seller.s_name.lname);
    fflush(stdin);
    printf("Enter the Seller Address\n");
    printf("Door No: ");
    gets(pd.p_seller.s_address.door_no);
    fflush(stdin);
    printf("Address line 1: ");
    gets(pd.p_seller.s_address.address_line1);
    fflush(stdin);
    printf("City: ");
    gets(pd.p_seller.s_address.city);
    fflush(stdin);
    printf("State: ");
    gets(pd.p_seller.s_address.state);
    fflush(stdin);
    printf("Enter phone number: ");
    gets(pd.p_seller.phone_no);
    fflush(stdin);
    product_temp->data = pd;
    product_temp->next = NULL;
    product_temp->prev = NULL;
    insert_product_tolist();
    write_counters(main_counter);
    write_product(pd);
    printf("Product Adding Successful\n");
    system("pause");
}

void view_product()
{
    product_temp = product_front;
    printf("Product ID \tProduct NAME \tRemaining Product \tPrice \tRating \n");

    while(product_temp != NULL)
    {
        printf("%7d\t",product_temp->data.p_ID);
        printf("%9s\t",product_temp->data.p_name);
        printf("%4d\t",product_temp->data.no_of_products);
        printf("%9f\t",product_temp->data.price);
        printf("%5f\t",product_temp->data.rating);
        product_temp = product_temp->next;
    }
    system("pause");
}

void displayele(PRODUCT *ptr)
{
    printf("DETAILS\n");
    printf("-------\n");
    printf("Product ID: %d\n",ptr->data.p_ID);
    printf("Product Name: %s \n",ptr->data.p_name);
    printf("Price: %f\n",ptr->data.price);
    printf("Seller Name: %s %s \n",ptr->data.p_seller.s_name.fname,ptr->data.p_seller.s_name.lname);
    //need to show descp ,rating
    //seller details?
    printf("\n");
}

int deleteinlist(int pid)
{
    char ch;
    product_temp = product_front;

    if(product_front == NULL)
        return FALSE;
    else if(product_front->next == NULL)
    {
        if(product_front->data.p_ID == pid)
        {
            displayele(product_front);
            printf("Do you wanna delete the above Product(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch == 'Y' || ch =='y')
            {
                product_front = NULL;
                product_end = NULL;
                free(product_temp);
                return TRUE;
            }
        }

    }
    else
    {
        if(product_front->data.p_ID == pid)
        {
            displayele(product_front);
            printf("Do you wanna delete the above Product(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch=='Y' || ch=='y')
            {
                product_temp = product_front;
                product_front = product_front->next;
                product_front->prev = NULL;
                free(product_temp);
                return TRUE;
            }

        }
        else if(product_end->data.p_ID == pid)
        {
            displayele(user_end);
            printf("Do you wanna delete the above Product(Y/N)");
            fflush(stdin);
            scanf("%c",&ch);
            if(ch == 'Y' || ch=='y')
            {
                product_temp = product_end;
                product_end = product_end->prev;
                product_end->next = NULL;
                free(product_temp);
                return TRUE;
            }
        }
        else
        {
            while(product_temp!=NULL)
            {
                if(product_temp->data.p_ID == pid)
                {
                    displayele(product_temp);
                    printf("Do you wanna delete the above Product(Y/N)");
                    fflush(stdin);
                    scanf("%c",&ch);
                    if(ch == 'Y' || ch =='y')
                    {
                        product_temp->prev->next = product_temp->next;
                        product_temp->next->prev = product_temp->prev;
                        free(product_temp);
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

void deleteinfile(int pid)
{
    FILE *product_data = fopen("data/product_details.dat","w");
    USER *temporary;
    user t2;
    temporary = product_front;

    while(temporary!= NULL)
    {
        t2 = temporary->data;
        fwrite(&t2,sizeof(product),1,product_data);
        temporary = temporary->next;
    }
    fclose(product_data);
}

void manage_users()
{
    while(1)
    {
        int ch,uid,res;
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1. Add User\n2. View Users\n3. Delete User by ID\n4. View User detail by ID\n5. Set User Priority\n6. Exit\n\n");
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
                printf("Enter your ID to Delete: ");
                scanf("%d",&uid);
                res = deleteinlist(uid);

                if(res)
                {
                    printf("Deleted User\n");
                    deleteinfile(uid);
                    main_counter.u_ID--;
                    write_counters(main_counter);
                }
                else
                {
                    printf("Couldn't delete the above user\n");
                }
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
    }
}

void manage_products()
{
    while(1)
    {
        int ch,pid,res;
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1. Add Products\n2. View Products\n3. Delete Products by Name\n4. View Products detail by Name\n5. Exit\n");
        printf("Enter your choice: ");
        fflush(stdin);
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                product_register();
                break;
            case 2:
                view_product();
                break;
            case 3:
                printf("Enter your ID to Delete: ");
                scanf("%d",&pid);
                res = deleteinlist(pid);

                if(res)
                {
                    printf("Deleted User\n");
                    deleteinfile(pid);
                    main_counter.p_ID--;
                    write_counters(main_counter);
                }
                else
                {
                    printf("Couldn't delete the above Product\n");
                }
                break;
            case 4:
                break;
            case 5:
                return;
            default:
                printf("Wrong Choice entered\n");
        }
    }
}

void admin_home()
{
    int ch;

    while(1)
    {
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1. Manage Users\n2. Manage Products\n3. Manage Orders\n4. Logout\n\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                manage_users();
                break;
            case 2:
                manage_products();
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

product return_product(int p_id)
{
    product_temp = product_front;

}
void update_current_user(int o_id)
{
    currentusr.nooforders++;
    currentusr.prime = currentusr.nooforders/6;
    user_temp = user_front;
    while(user_temp!= NULL)
    {
        if(user_temp->data.u_ID == currentusr.u_ID)
        {
            user_temp->data.o_ID[user_temp->data.nooforders] = o_id;
            user_temp->data.nooforders++;
            user_temp->data.prime = currentusr.prime;
        }
        user_temp = user_temp->next;
    }
}
void write_user_file()
{
    FILE *users = fopen("data/user_details.dat","w");
    user t;
    user_temp = user_front;
    while(user_temp!=NULL)
    {
        t = user_temp->data;
        fwrite(&t,sifeof(user),1,users);
        user_temp = user_temp->next;
    }
    fclose(users);
}
void write_order(order o)
{
    FILE *register_orders = fopen("data/order_details.dat","a");
    if(register_orders = NULL)
    {
        printf("cannot create a file\n");
        exit(EXIT_FAILURE);
    }
    fwrite(&o,sizeof(order),1,register_orders);
    fclose(register_orders);
}
void insert_order_tolist()
{
    if(order_front == NULL)
    {
        order_front = order_temp;
        order_end = order_temp;
    }
    else
    {
        order_end->next = order_temp;
        order_temp->prev = order_end;
        order_end = order_temp;
    }
}
int check_product(int p_id)
{
    product_temp = product_front;
    while(product_temp!=NULL)
    {
        if(product_temp->data.p_ID == p_id)
            return TRUE;
        product_temp = product_temp->next;
    }
    return FALSE;
}
product return_product(int p_id)
{
    product t;
    product_temp = product_front;
    while(product_temp!=NULL)
    {
        if(product_temp->data.p_ID == p_id)
        {
            t = product_temp->data;
            return t;
        }
        product_temp = product_temp->next;
    }
}
void writefilepq()
{
    order temppq;
    FILE *orderpq = fopen("data/priority_order.dat","w");
    if(orderpq == NULL)
    {
        printf("File can't be created.\n");
        exit(EXIT_FAILURE);
    }
    order_p_temp = order_p_front;
    while(order_p_temp!= NULL)
    {
        temppq = order_p_temp->data;
        fwrite(&temppq, sizeof(order), 1, orderpq);
        order_p_temp = order_p_temp->next;
    }
    fclose(orderpq);
}
void write_p_order(order opq)
{
    FILE *writeopq = fopen("data/priority_order.dat","a");
    if(writeopq == NULL)
    {
        printf("File couldn't be created");
        exit(EXIT_FAILURE);
    }
    fwrite(&opq, sizeof(order), 1, writeopq);
    fclose(writeopq);
}
void write_p_q()
{
    ORDER ot;
    if(order_p_front == NULL)
    {
        order_p_front = order_p_temp;
        order_p_end = order_p_temp;
    }
    else
    {
        ot = order_p_front;
        while(ot != NULL && ot->data.o_user.prime >= order_p_temp->data.o_user.prime)
            ot = ot->next;
        if(ot == order_p_front)
        {
            order_p_front->prev = order_p_temp;
            order_p_temp->next = order_p_front;
            order_p_front = order_p_temp;
        }
        else if(ot!= NULL)
        {
            ot->prev->next = order_p_temp;
            order_p_temp->prev = ot->prev;
            order_p_temp->next = ot;
            ot->prev = order_p_temp;
        }
        else
        {
            order_p_end->next = order_p_temp;
            order_p_temp->prev = order_p_end;
            order_p_end = order_p_temp;
        }
    }
    write_p_order(ot->data);
    main_counter.o_p_ID++;
    write_counters(main_counter);
}
void insert_opq_tolist()
{
    if(order_p_front == NULL)
    {
        order_p_front = order_p_temp;
        order_p_end = order_p_temp;
    }
    else
    {
        order_p_end->next = order_p_temp;
        order_p_temp->prev = order_p_end;
        order_p_end = order_p_temp;
    }
}
int checkorder(order test)
{
    int dif;
    dif = difference(test.d, )
}
void load_p_orders()
{
    FILE *load_order = fopen("data/priority_order.dat","r");
    int i = main_counter.o_p_ID;
    order loader;
    while(i>0)
    {
        fread(&loader, sizeof(order), 1, load_order);
        if(checkorder(loader))
        {
            order_p_temp = (ORDER*)malloc(sizeof(ORDER));
            order_p_temp->data = loader;
            order_p_temp->next = NULL;
            order_p_temp->prev = NULL;
            insert_poq_tolist();
        }
        i--;
    }
    fclose(load_order);

}
void place_order()
{
    int p_id;
    p_id_again:
    printf("Enter Product ID to Place order: ");
    scanf("%d",&p_id);
    if(!check_product(p_id))
    {
        printf("Product ID not in the database.\nEnter valid Product ID\n");
        goto p_id_again;
    }
    order od;
    order_temp = (ORDER*)malloc(sizeof(ORDER));
    order_p_temp = (ORDER*)malloc(sizeof(ORDER));
    main_counter.o_ID++;
    od.o_ID = main_counter.o_ID;
    od.p_ID = p_id;
    od.u_ID = currentusr.u_ID;
    update_current_user(od.o_ID);
    write_user_file();
    write_counters(main_counter);
    od.o_user = currentusr;
    od.o_product = return_product(p_id);
    od.o_product.daystodeliver = ceil(od.o_product.daystodeliver - (0.5 * od.o_user.prime));
    od.o_date = curdate;
    order_temp->data = od;
    order_temp->next = NULL;
    order_temp->prev = NULL;
    order_p_temp->data.o_date = curdate;
    order_p_temp->data.o_ID = main_counter.o_ID;
    order_p_temp->data.o_product = od.o_product;
    order_p_temp->data.o_user = od.o_user;
    order_p_temp->data.p_ID = od.p_ID;
    order_p_temp->data.o_ID = od.o_ID;
    order_p_temp->next = NULL;
    order_p_temp->prev = NULL;
    write_p_q();
    insert_order_tolist();
    write_order(od);
}

void display_order(order data)
{
    //fill the printf statements here
}

void view_user_orders()
{
    int i = currentusr.nooforders,j=0;
    printf("ORDER ID \tPRODUCT NAME \tORDER DATE \t ")
    while(i>0)
    {
        order_temp = order_front;
        while(order_temp!=NULL)
        {
            if(order_temp->data.o_ID == currentusr.o_ID[j])
            {
                display_order(order_temp->data);
            }
            order_temp=order_temp->next;
        }
        j++;
        i--;
    }
}

void user_home()
{
   int ch;

    while(1)
    {
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1. View Product\n2. Place Order by Product ID\n3. View Orders\n4. Edit Details\n5. Delete Account\n6. Logout\n\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                view_product();
                break;
            case 2:
                place_order();
                break;
            case 3:
                view_user_orders();
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                //logout
                return ;
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
    load_products();
    load_orders();
    write_order_file();
    while(1)
    {
        system("cls");
        printf("ONLINE SHOPPING APPLICATION\n\n");
        printf("1. Admin Login\n2. User Login/Register\n3. Exit\n");
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
                    printf("1. Login\n2. Sign up\n3. Exit\n\n");
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
                        //break;
                    default:
                        printf("Wrong Option entered. Try again\n");
                    }
                }
                exit_loop:
                break;
            case 3:
                exit(0);
                //break;
            default:
                printf("Wrong option Entered\n");
        }
    }
    free(user_front);
    free(user_temp);
    free(user_end);
    return 0;
}
