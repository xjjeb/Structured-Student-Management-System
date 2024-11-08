int authorization(struct admin_info * admin_tab)
{
    int operation_code;
    printf("Welcome to the SMS Authorization Page!\n");
    auth_prompt_op();
    scanf("%d", &operation_code);
    getchar();
    while(operation_code == 0 || operation_code == 1)//only valid routes of auth() return 1 
    {
        if (operation_code == 0){
            if (log_in(admin_tab)){
                return 1;
            }
        }
        else{
            if (sign_up(admin_tab)){
                if (log_in(admin_tab)){
                    return 1;
                }
            }
        }
        auth_prompt_op();

        scanf("%d", &operation_code);
    }
    return 0;
}

int log_in(struct admin_info * admin_tab)
{
    int err_cnt = 0;
    printf("\nThis is the LOG IN PAGE\n");
    char temp_name[41];
    char temp_password[13];
    while (err_cnt < 5){
    printf("Please input your USERNAME:");
    get_str(temp_name, 41);
    printf("Please input your PASSWORD:");
    get_str(temp_password, 13);
    if (seek_all(admin_tab, temp_name, temp_password)){
        return 1;
    }
    else{
        printf("LOG IN FAILED!\nPLEASE DO IT AGAIN!\n");
    }
        err_cnt ++;
    }
    printf("Uh-Oh, it seems that you made mistakes a lot!\nRe-enter the system!\n");
    return 0;
}

int sign_up(struct admin_info * admin_tab)
{
    printf("\nThis is the SIGN UP page\n");
    char name[41];
    char password[13];
    char conf_password[13];
    int flag = 1;
    while (flag){
        printf("Please input your user name(less than 40 words):");
        get_str(name, 41);
        printf("Please input your password(less than 12 words):");
        get_str(password, 41);
        printf("Please confirm your password:");
        get_str(conf_password, 41);
        if (strcmp(password, conf_password) == 0){
            flag = 0;
            printf("Please Confirm:\n");
            printf("Your Username: %s\n", name);
            printf("Your Password: %s\n", password);
            break;
        }
        else{
            printf("the password you input are not equal!\nPlease sign up again.\n");
        }
    }
    strcpy(admin_tab[admin_tab_len].name, name);
    strcpy(admin_tab[admin_tab_len].password, password);
    admin_tab_len ++;
    return 1;
}

int seek_all(struct admin_info * tab, char * name, char * password)
{
    for (int i = 0; i < admin_tab_len; i ++){
        if (strcmp(tab[i].name, name) == 0 && strcmp(tab[i].password, password) == 0){
            return 1;
        }
    }
    return 0;
}

int seek_name(struct admin_info * tab, char * name)
{
    for (int i = 0; i < admin_tab_len; i ++){
        if ((tab + i)->name == name){
            return 1;
        }
    }
    return 0;
}

void stu_man(struct stu_info * stu_tab)  //should be looping inside 
{
    int operation_code; //if logging off, directly goes back to authorization page
    man_prompt_op();
    scanf("%d", &operation_code);
    while(log_off(operation_code) != 1){    //inner looping while not logging off
        printf("\nTHIS IS PROCESSING!\n");  //later replaced by some steps.
        man_prompt_op();
        scanf("%d", &operation_code);
    }
}

int log_off(int op_code)
{
    if (op_code == 1 || op_code == 2 || op_code == 3){
        return 0;
    }
    else{
        return 1;
    }
}

void get_str(char * str, int len)
{
    char tmp;
    for (int i = 0; i < len; i ++){
        scanf("%c", &tmp);
        if (tmp == '\n' || tmp == '\0'){
            str[i] = '\0';
            break;
        }
        else{
            str[i] = tmp;
        }
    }
}

void auth_prompt_op()
{
    printf("Please input 0 if you are logging in\n");
    printf("Please input 1 if you are signing up\n");
    printf("Please input other numbers if you are quitting the SMS:\n");
}

void man_prompt_op()
{
    printf("Please input 1 if you want to add students to the table\n");
    printf("Please input 2 if you want to search for a certain student or delete a student or modify the infos of the student.\n");
    printf("Please input 3 if you want to go through all the students\n");
    printf("Please input others to LOG OFF the SMS\n");
}