#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct admin_info
{
    char name[41];
    char password[13];
};

struct stu_info //stored with chained_list
{
    char name[41];
    char gender[7];
    int age;
    float gpa;
    struct stu_info * next;
};

int authorization(struct admin_info * admin_tab);
int log_in(struct admin_info * admin_tab);
int sign_up(struct admin_info * admin_tab);
int seek_all(struct admin_info * tab, char * name, char * password);
int seek_name(struct admin_info * tab, char * name);
int log_off(int op_code);

void get_str(char * str, int len);
void auth_prompt_op();
void man_prompt_op();
void stu_man(struct stu_info * stu_tab);

static int admin_tab_len = 0;