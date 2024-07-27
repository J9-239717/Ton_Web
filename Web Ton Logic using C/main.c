#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef enum{
    Volleyball = 1,
    Basketball = 2,
    Badminton = 3
}Sport;

typedef enum{
    shoes = 1,
    shirt = 2,
    pants = 3,
    ball = 4,
    set_pants_shirt = 5
}typeItem;

typedef struct Sinka
{
    Sport sport;
    typeItem item;
    double price;
    int quantity;
    struct Sinka* next;
}Sinka;

typedef struct list
{
    Sinka* product;
}ListofProduct;


Sport getSportformInt(int x){
    switch (x)
    {
    case 1:
        return Volleyball;
        break;
    case 2:
        return Basketball;
    case 3:
        return Badminton;
    default:
        return 0;
        break;
    }
}

typeItem getItemformInt(int x){
    switch (x)
    {
    case 1:
        return shoes;
        break;
    case 2:
        return shirt;
    case 3:
        return pants;
    case 4:
        return ball;
        break;
    case 5:
        return set_pants_shirt;
        break;
    default:
        return 0;
        break;
    }
}

char* getNameItem(typeItem x){
    char *temp = (char*)malloc(20 * sizeof(char));
    switch (x)
    {
    case shoes:
        strcpy(temp, "shoes");
        break;
    case shirt:
        strcpy(temp, "shirt");
        break;
    case pants:
        strcpy(temp, "pants");
        break;
    case ball:
        strcpy(temp, "ball");
        break;
    case set_pants_shirt:
        strcpy(temp, "set_shoes_shirt");
        break;
    default:
        free(temp);
        return NULL;
        break;
    }
    return temp;
}

double getPriceItem(typeItem x){
    double buffer;
    switch (x)
    {
    case shoes:
        buffer = 1000000.0;
        break;
    case shirt:
        buffer = 50000.0;
        break;
    case pants:
        buffer = 35000.0;
        break;
    case ball:
        buffer = 1000000.0;
        break;
    case set_pants_shirt:
        buffer = 70000.0;
        break;
    default:
        return 0.0;
        break;
    }
    return buffer;
}

char* getSport(Sport x){
    char* temp = (char*)malloc(10*sizeof(char) + 1);
    switch (x)
    {
    case Volleyball:
        strcpy(temp, "Volleyball");
        break;
    case Basketball:
        strcpy(temp, "Basketball");
        break;
    case Badminton:
        strcpy(temp, "Badminton");
        break;
    default:
        free(temp);
        return NULL;
        break;
    }
    return temp;
}

ListofProduct* makeList(){
    ListofProduct* new = (ListofProduct*)malloc(sizeof(ListofProduct));
    new->product = NULL;
    return new;
}

int Payment(double price) {
    double money;
    printf("Please Enter Your Money: ");
    scanf("%lf", &money);

    while (price > 0) {
        price -= money;
        if (price > 0) {
            printf("Remaining amount: %.2f\n", price);
            printf("Please Enter Your Money again: ");
            scanf("%lf", &money);
        }
    }

    if (price < 0) {
        printf("Pay back %.2f\n", -price);
    } else {
        printf("Exact amount paid. No change needed.\n");
    }

    return 1;
}

void ShowDetail(Sport s,typeItem t){
    printf("-----------------%s for %s-----------------\n"
           "price per one is : %lf\n"
           "made in Laos\n",getNameItem(t), getSport(s), getPriceItem(t));
}

Sinka* newSinka(Sport sport,typeItem item,double price,int quantity){
    Sinka* new = (Sinka*)malloc(sizeof(Sinka));
    new->price = price;
    new->quantity = quantity;
    new->sport = sport;
    new->item = item;
    new->next = NULL;
    return new;
}

Sinka* findOrder(ListofProduct* list,Sport sport,typeItem item){
    if(list->product == NULL)return NULL;

    Sinka* curr = list->product;
    while (curr != NULL)
    {
        if(list->product->item == item && list->product->sport == sport){
            return curr;
        }else{
            curr = curr->next;
        }
    }
    return curr;
}

void DeleteOrder(ListofProduct* list, Sport sport, typeItem item, int qtt) {
    if (list->product == NULL) {
        printf("List is NULL\n");
        return;
    }

    Sinka *curr, *prev;
    curr = list->product;
    prev = NULL;

    while (curr != NULL) {
        if (curr->item == item && curr->sport == sport) {
            curr->quantity -= qtt;
            if (curr->quantity <= 0) {
                if (prev == NULL) {
                    // Deleting the first node
                    list->product = curr->next;
                    free(curr);
                    curr = list->product; // Update curr to the new head of the list
                } else {
                    // Deleting a node other than the first
                    prev->next = curr->next;
                    free(curr);
                    curr = prev->next; // Update curr to the next node
                }
            } else {
                // Move to the next node if no deletion
                prev = curr;
                curr = curr->next;
            }
        } else {
            // Move to the next node
            prev = curr;
            curr = curr->next;
        }
    }
}


void addOrder(ListofProduct* list,Sport sport,typeItem item,double price,int quantity){
    Sinka* new;
    if(list->product == NULL){// when list is nothing
        new = newSinka(sport,item,price,quantity);
        list->product = new;
    }else{
        new = findOrder(list,sport,item);
        if(new != NULL){ // when have order in list
            new->quantity += quantity;
        }else{// when dont have order in list
            new = newSinka(sport,item,price,quantity);
            new->next = list->product;
            list->product = new;
        }
    }
}

void loadOrder(ListofProduct* list,Sport sport){
    int op = 0,run=1,qtt;
   
    while (run)
    { 
        printf( "Enter 1 to order of shoes\n"
            "Enter 2 to order of shirt\n"
            "Enter 3 to order of pants\n"
            "Enter 4 to order of ball\n"
            "Enter 5 to spicial order is order pants and shirt -5000\n"
            "Enter 6 to End order\n");
        printf("Enter: ");scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("Please Enter quantity order: ");scanf("%d", &qtt);
            addOrder(list,sport,shoes,getPriceItem(shoes),qtt);
            printf("Complete\n");
            break;
        case 2:
            printf("Please Enter quantity order: ");scanf("%d", &qtt);
            addOrder(list,sport,shirt,getPriceItem(shirt),qtt);
            printf("Complete\n");
            break;
        case 3:
            printf("Please Enter quantity order: ");scanf("%d", &qtt);
            addOrder(list,sport,pants,getPriceItem(pants),qtt);
            printf("Complete\n");
            break;
        case 4:
            printf("Please Enter quantity order: ");scanf("%d", &qtt);
            addOrder(list,sport,ball,getPriceItem(ball),qtt);
            printf("Complete\n");
            break;
        case 5:
            printf("Please Enter quantity order: ");scanf("%d", &qtt);
            addOrder(list,sport,set_pants_shirt,getPriceItem(set_pants_shirt),qtt);
            printf("Complete\n");
            break;
        case 6:
            run = 0;
            printf("Thank you\n");
            break;
        default:
            printf("Pleaes Enter the operation again\n");
            break;
        }
    }
    
}

void freeList(ListofProduct* s){
    Sinka* curr = s->product;
    while (curr != NULL)
    {
        Sinka* temp = curr;
        curr = curr->next;
        free(temp);
    }
    s->product = NULL;
}

void SeletionPagebySportProduct(ListofProduct *list,Sport sp);
void SeletionPageListOrder(ListofProduct* list);
double DisplayList(ListofProduct *list);

/////////////////////////////////////////////////////////// MAIN /////////////////////////////////////////////////////////////////////////////
int main(){
    // Set default
    ListofProduct* list = makeList();
    int run = 1;
    int op;

    while(run){
        printf("Welecome to Ton Sport Market\n"
        "Enter 1 page to seletion the Voleyball product\n"
        "Enter 2 page to seletion the Basketball product\n"
        "Enter 3 page to seletion the Badminton product\n"
        "Enter 4 page to seletion the list of your order\n"
        "Enter 5 to end program\n"
        "seletion: ");scanf("%d", &op);
        switch (op)
        {
        case 1:
            SeletionPagebySportProduct(list,Volleyball);
            break;
        case 2:
            SeletionPagebySportProduct(list,Basketball);
            break;
        case 3:
            SeletionPagebySportProduct(list,Badminton);
            break;
        case 4:
            SeletionPageListOrder(list);
            break;
        case 5:
            run = 0;
            freeList(list);
            free(list);
            printf("Thank you\n");
            break;
        default:
            printf("Pleaes Enter the operation again\n");
            break;
        }
    }
    return 0;
}
/////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////////////////////////////////////////////////////////

void SeletionPagebySportProduct(ListofProduct *list, Sport sp){
    int op;
    int run = 1;
    while (run)
    {
        printf("What type of Product do you want:\n"
            "We have shoes, shirt, pants, ball and set of pants and shirt\n"
            "Enter 1 to see detail of shoes\n"
            "Enter 2 to see detail of shirt\n"
            "Enter 3 to see detail of pants\n"
            "Enter 4 to see detail of ball\n"
            "Enter 5 to order product\n"
            "Enter 6 to GO BACK\n"
            "ENTER: ");scanf("%d", &op);

        switch (op)
        {
        case 1:
            ShowDetail(sp,shoes);
            break;
        case 2:
            ShowDetail(sp,shirt);
            break;
        case 3:
            ShowDetail(sp,pants);
            break;
        case 4:
            ShowDetail(sp,ball);
            break;
        case 5:
            loadOrder(list,sp);
            break;
        case 6:
            run = 0;
            break;
        default:
            printf("Pleaes Enter the operation again\n");
            break;
        }
    }
}

double DisplayList(ListofProduct *list) {
    double all = 0;
    if(list->product == NULL) {
        printf("\n                       ToTal ALL : %.2f                       \n", all);
        return 0.0;
    }
    Sinka* current = list->product;
    
    while (current != NULL) {
        printf("Sport: %s, Item: %s, Price: %.2f, Quantity: %d, Total:%.2f\n",
               getSport(current->sport),
               getNameItem(current->item),
               current->price,
               current->quantity,
               current->quantity * current->price);
        all += current->quantity * current->price;
        current = current->next;
    }
        printf("\n                       ToTal ALL : %.2f                       \n", all);
    return all;
}

void DeleteOrderInList(ListofProduct* list){
    Sport sp;
    typeItem t;
    int qtt;
    int op;
    
    printf("What Sport of Product Do you want to Delete\n"
           "1.Volleyball\n"
           "2.Basketball\n"
           "3.Badminton\n"
    );printf("Enter: ");scanf("%d", &op);

    sp = getSportformInt(op);

     printf("What Product Do you want to Delete\n"
           "1.shoes\n"
           "2.shirt\n"
           "3.pants\n"
           "4.ball\n"
           "5.set of shoes and shirt\n"
    );printf("Enter: ");scanf("%d", &op);
    
    t = getItemformInt(op);

    printf("Enter quantity: ");scanf("%d", &op);
    qtt = op;

    DeleteOrder(list,sp,t,qtt);
}
void SeletionPageListOrder(ListofProduct* list){
    int op;
    int run = 1;
    int all = 0;
    while (run)
    {
        all = DisplayList(list);
        printf("Enter 1 to confirm order\n"
               "Enter 2 to delete order\n"
               "Enter 3 to go back\n"
        );printf("Enter: ");scanf("%d", &op);
        switch (op)
        {
        case 1:
            Payment(all);
            freeList(list);
            break;
        case 2:
            DeleteOrderInList(list);
            break;
        case 3:
            run = 0;
            break;
        default:
            printf("Pleaes Enter the operation again\n");
            break;
        }
    }
    
}