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
        getchar();
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
    printf("Please input 2 if you want to search for a certain student.\n");
    printf("Please input 3 if you want to go through all the students\n");
    printf("Please input others to LOG OFF the SMS\n");
}

void stu_man(struct stu_info ** stu_tab_ptr)  //should be looping inside 
{
    char temp_name[41];
    int operation_code; //if logging off, directly goes back to authorization page
    int search_op_code;
    man_prompt_op();
    scanf("%d", &operation_code);
    getchar();
    while(log_off(operation_code) != 1){    //inner looping while not logging off
        if (operation_code == 1){
            stu_add(stu_tab_ptr);
        }
        else if (operation_code == 2){
            printf("\nPlease input the name of the student to be searched:");
            get_str(temp_name, 41);
            if (search(*stu_tab_ptr, temp_name) != NULL){
                printf("SEARCH SUCCEEDED! Here's the infos about %s\n", temp_name);
                info_show(*stu_tab_ptr);
            }
            else{
                printf("%s CAN'T BE FOUND in our student info table!\n", temp_name);
            }
        }
        else{
            go_through(*stu_tab_ptr);
        }
        man_prompt_op();
        scanf("%d", &operation_code);
        getchar();
    }
}

void stu_add(struct stu_info ** stu_ptr)
{
    char name[41];
    char gender[7];
    int age;
    float gpa;
    printf("Please input the name of the student to be added:");
    get_str(name, 41);
    printf("Please input the gender of the student:(MALE/FEMALE)");//MAYBE SHOULD BE RESTRICTED LATER?
    get_str(gender, 7);
    printf("Please input the age of the student:");
    scanf("%d", &age);
    getchar();
    printf("Please input the gpa of the student:");
    scanf("%f", &gpa);
    getchar();
    struct stu_info * curr = (struct stu_info *)malloc(sizeof(struct stu_info));
    strcpy(curr->name, name);
    strcpy(curr->gender, gender);
    curr->age = age;
    curr->gpa = gpa;
    curr->next = *stu_ptr;
    *stu_ptr = curr;
    printf("\nStudent Information Successfully Added!\n");
    stu_tab_len ++;
}

void info_show(struct stu_info * stu_ptr)
{
    printf("NAME:%s\n", stu_ptr->name);
    printf("GENDER: %s\n", stu_ptr->gender);
    printf("AGE:%d\n", stu_ptr->age);
    printf("GPA:%f\n", stu_ptr->gpa);
}

void go_through(struct stu_info * head)
{
    struct stu_info * tmp_head = head;
    while (tmp_head != NULL){
        printf("%20s%8s%4d%5.2f\n", tmp_head->name, tmp_head->gender, tmp_head->age, tmp_head->gpa);
        tmp_head = tmp_head->next;
    }
}

struct stu_info * search(struct stu_info * stu_tab, char * name)
{
    struct stu_info * ret_ptr = NULL;
    struct stu_info * ptr = stu_tab;
    while (ptr != NULL){
        if (strcmp(ptr->name, name) == 0){
            ret_ptr = ptr;
            break;
        }
        ptr = ptr->next;
    }
    return ret_ptr;
}