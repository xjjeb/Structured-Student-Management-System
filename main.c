#include "ref.h"
#include "functions.h"

int main()
{
    struct admin_info admin_tab[100];
    struct stu_info * stu_tab = (struct stu_info *)malloc(sizeof(struct stu_info));
    if (authorization(admin_tab) == 1){
        
    }
    printf("Bye!");
    return 0;
}