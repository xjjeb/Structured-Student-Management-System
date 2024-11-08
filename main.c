#include "ref.h"
#include "functions.h"

int main()
{
    int quit = 0;
    static struct admin_info admin_tab[100];
    struct stu_info * stu_tab = (struct stu_info *)malloc(sizeof(struct stu_info));
    while (quit != 1){
        if (authorization(admin_tab) == 1){
            printf("\nAuthorization Succeeded!\n");
            //proccessing-->log off-->authorization again!
            stu_man(stu_tab);//uses the inner loop
        }
        else{
            quit = 1;
        }
    }
    printf("Student Management System Exited.\nGood Bye!");
    return 0;
}