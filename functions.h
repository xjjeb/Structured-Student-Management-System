int authorization(struct admin_info * admin_tab)
{
    int operation_code;
    printf("Welcome to the Student Management System!\n");
    prompt_op();
    scanf("%d", &operation_code);
    while(operation_code == 0 || operation_code == 1)//only valid routes of auth() return 1 
    {
        if (operation_code == 0){
            if (log_in(admin_tab)){
                return 1;
            }
        }
        else{
            if (sign_up(admin_tab)){
                return 1;
            }
        }
        prompt_op();
        scanf("%d", &operation_code);
    }
    return 0;
}

int log_in(struct admin_info * admin_tab)
{

}

int sign_up(struct admin_info * admin_tab)
{

}

void prompt_op()
{
    printf("Please input 0 if you are logging in\n");
    printf("Please input 1 if you are signing up\n");
    printf("Please input other numbers if you are quitting the system:\n");
}