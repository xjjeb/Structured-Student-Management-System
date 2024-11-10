#include "ref.h"

int main()
{
    int quit = 0;
    static struct admin_info admin_tab[100];
    struct stu_info * stu_tab = NULL;
    while (quit != 1){  //outer loop means the loop of the entire system.
        if (authorization(admin_tab) == 1){
            printf("\nAuthorization Succeeded!\n");
            //proccessing-->log off-->authorization again!
            stu_man(&stu_tab);//uses the inner loop
        }           //pointer of stu_tab makes sure the stu_tab can be modified
        else{
            quit = 1;
        }
    }
    printf("Student Management System Exited.\nGood Bye!");
    getchar();
    return 0;
}