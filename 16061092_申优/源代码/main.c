#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_NAME 500//���·��������
#define N 200          //��󵥴ʳ���
#define OP_MAX 20     //���op����
#define MAX_LLEN 300  //ÿ������ַ���
#define MAX_LINE 1000  //�������
#define MAX_LWORDS 200 //ÿ����󵥴���
#define MAX_IDENT_NUM 10000 //����ʶ������
#define MAX_FUC_NUM 100//���������
#define MAX_MID_NUM 5000//�����Ԫʽ��Ŀ
#define MAX_AIM_NUM 20000//���Ŀ�����ָ����
#define MAX_STR_NUM 2000//����ַ�������
#define MAX_PARA_NUM 100 //ֵ����������������
char code_name[MAX_PATH_NAME];//Դ����·��
char key[12][10]={      "const",
                        "int",
                        "char",
                        "void",
                        "main",
                        "if",
                        "else",
                        "while",
                        "for",
                        "scanf",
                        "printf",
                        "return"};
char keycon[12][10]={   "constsy",
                        "intsy",
                        "charsy",
                        "voidsy",
                        "mainsy",
                        "ifsy",
                        "elsesy",
                        "whilesy",
                        "forsy",
                        "scanfsy",
                        "printfsy",
                        "returnsy"};
char midcon[24][10]={   "+",
                        "-",
                        "*",
                        "/",
                        "[]=",
                        "=[]",
                        "push",
                        "call",
                        "calr",
                        "ret",
                        "GOTO",
                        "<",
                        "<=",
                        ">",
                        ">=",
                        "!=",
                        "label",
                        "==",
                        "scanf",
                        "printf",
                        "BNZ",
                        "BZ",
                        "exitop",
                        "ass"};
char mipscon[19][10]={  "lw",
                        "sw",
                        "add",
                        "sub",
                        "mult",
                        "mflo",
                        "div",
                        "li",
                        "move",
                        "jal",
                        "j",
                        "bgez",
                        "bgtz",
                        "blez",
                        "bltz",
                        "beq",
                        "bne",
                        "syscall",
                        "la"};
char error1[4][30]={    "ERROR_CHAR_DEFINE",
                        "ERROR_STRING",
                        "ERROR_IVALID_CHARARCTER",
                        "ERROR_!_SINGLE"};
char error2[9][30]={    "ERROR_;_LACK",
                        "ERROR_MIS_WENFA",
                        "ERROR_()_MIS",
                        "ERROR_[]_MIS",
                        "ERROR_{}_MIS",
                        "ERROR_PARA_TABLE",
                        "ERROR_ARRAY",
                        "ERROR_CONS",
                        "ERROR_IDENT"};
char error3[10][30]={   "ERROR_LOW_ARR",
                        "ERROR_HIGH_ARR",
                        "ERROR_MIS_TYP",
                        "ERROR_RE_DEF",
                        "ERROR_NO_DEF",
                        "ERROR_MIS_PARA",
                        "ERROR_ARR_INDEX",
                        "ERROR_CONS_ASS",
                        "ERROR_MIS_RET",
                        "ERROR_NO_RETURN"};
char words[MAX_LINE][MAX_LWORDS][N];//��ʾ�ڼ��еڼ����ĵ�����ʲô;
int words_sym[MAX_LINE][MAX_LWORDS];//��ʾ�ڼ��еڼ���������ʲô����;
int words_num[MAX_LINE];//��ʾ�ڼ��е��ʸ���
int code_length[MAX_LINE];//�ڼ����ַ�����
int func_mid_var[MAX_FUC_NUM];//�������ڼ����������м��������
int func_mid_var_fi[MAX_FUC_NUM];//�ڼ����������м��������
int jishu[MAX_FUC_NUM];//�ڼ��������ģ�����+�ֲ�����+�м��������ռ����ջ�ռ��С
char a[MAX_LINE][MAX_LLEN];///�����������
int ll;//��ָ��
int ll_max;//����
int li;//���ﵥ��ָ��
int sym;//���ͱ��
int v0_use;//
int t9_use;//
int exs_typ;//���ʽ����//0->int,1->char
int if_error=0;
FILE *in;//��������ļ�
FILE *out;//�ʷ�����������
FILE *gout;//�﷨����������
FILE *tableout;//���ű�
FILE *quaters;//��Ԫʽ���������м��������ݽṹ
FILE *opti_quaters;//�Ż�����Ԫʽ������
//FILE *midout;//�м����������
FILE *aimout;//Ŀ�����������
FILE *opti_aimout;//�Ż���Ŀ�����������

///--------------------------s��������ֵ����s-------------------------------------------------
char mid_va[N]={"$mid_"};///�µ��м�����м��������
char new_label_nam[N]={"label_"};///��label������
char new_strnum[N]={"$string_"};///�µ��ַ����������ƣ��洢Ҫ��ӡ���ַ���
char new_factor[N];///��������factor
char factor_nam[N];///�����������ڷ���ֵ
char factor_nam_res[N];///������������calr��res
char new_ret_nam[N]={"$RET_"};///�µķ���ֵ����
char f1[N];///��ķ���ֵ
char t1[N];///���ʽ�ķ���ֵ
char par_factor_nam[N];///����Ϊ(<���ʽ>)�ķ���ֵ
///--------------------------e��������ֵ����e-------------------------------------------------

///--------------------------s��������s-------------------------------------------------
void get_op1(int i,char opn_name[]);
void get_op1_2a0(int i,char opn_name[]);
void get_op2(int i,char opn_name[]);
void opti_get_op1(int i,char opn_name[]);
void opti_get_op1_2a0(int i,char opn_name[]);
void opti_get_op2(int i,char opn_name[]);
void fill_table1(char ident[],int typ,int level);
void trace_words(int tra_num);
char* new_var();
char* new_label();
char* new_str();
char* new_ret();
void gen_mid(int op,char op1[],char op2[],char res[],int adr);
void gen_mipscode(int op,char op1[],char op2[],char res[],int adr);
void print_midcode();
void opti_print_midcode();
void process_maif(int i);
void opti_process_maif(int i);
void _getsym();
int getsym();
void grammer();
void print_table();
void procedure();
void const_dec();
void const_def();
void var_dec();
void var_def();
void res_fuc();
void nores_fuc();
void param();
int lk_table(int lk_ll,int lk_li);
char* factor();
char* item();
char* exprs();
void val_param();
void com_stam();
void stam_q();
int stam();
void if_stam();
void circle_stam();
void condit();
void res_call(int fuc_i);
void nores_call(int n_fuc_i);
void ass_stam();
void read_stam();
void write_stam();
void return_stam(int ret_i);
void main_fuc();
void error(int error_typ,int error_No,int er_ll,int er_li);
void gen_aim();
void opti_gen_aim();
int if_number(char s[]);
///--------------------------e��������e-------------------------------------------------


///--------------------------s���ű����ݽṹs-------------------------------------------------
typedef struct{
    char ident_name[N];//��ʶ������
    int typ;//char->1,int->2,const char->3,const int->4,char[]->5,int[]->6,res_char->7,res_int->8,res_void->9,int�Ͳ���->10,char�Ͳ���->11
    int lev;//Ƕ�ײ���
    int adr;//adr�Գ�����˵���������ǵ�ֵ/ASCII��ֵ���Ա�����˵���Ǹñ���������ջS�з������Ե�ַ��
    int size;//��ռ�洢�ռ�Ĵ�С
}Table;///���ű���

typedef struct{
    Table table_contents[MAX_IDENT_NUM];//���ű�����
}Tables;///���ű�

Tables tables_local[MAX_FUC_NUM];///ȫ����ű�,�±�Ϊ0ʱ��ȫ�ַ��ű�����Ϊ�������ű�

int table_No;///���ű�ǰ������ָ���������ɵķ��ű�
int local_index[MAX_FUC_NUM];///ÿ���������ָ�룬ָ����һ��Ҫ����ı���
int have_return[MAX_FUC_NUM];///ÿ�������Ƿ���return���
///--------------------------e���ű����ݽṹe-------------------------------------------------


///--------------------------s��Ԫʽ���ݽṹs-------------------------------------------------
typedef struct{
    int op;//op����
    char op1[N];//��һ��������
    char op2[N];//�ڶ���������
    char res[N];//���
    int adr;//������Ԫʽλ��,�����ĸ���������,��table_No
}midcode;///��Ԫʽ

midcode midcodes[MAX_MID_NUM];///��Ԫʽ���飬���м����
midcode opti_midcodes[MAX_MID_NUM];///�Ż����м����

int mid_index;///��Ԫʽ�����±�,ָ����һ��Ҫ�������Ԫʽ
int opti_mid_index;

int mid_var_index;///�м������ָ��
int opti_mid_var_index;

int label_index;///label��ָ��
int opti_label_index;

//int ret_index;///ret��ָ��

///--------------------------e��Ԫʽ���ݽṹe-------------------------------------------------


///--------------------------s�ַ������ݴ洢s-------------------------------------------------

char all_str[MAX_STR_NUM][N];///���ַ�������
int str_index;///�ַ���ָ�룬all_str[str_index]ָ���ض��ַ���

///--------------------------e�ַ������ݴ洢e-------------------------------------------------

/**����ű���ʶ�������ͣ�Ƕ�ײ�����
*/
void fill_table1(char ident[],int typ,int level){
    if(level==1){//���뺯����table_No,local_index[table_No]����������ģ�����������������������
        strcpy(tables_local[table_No].table_contents[local_index[table_No]].ident_name,ident);//�����ʶ����
        tables_local[table_No].table_contents[local_index[table_No]].lev=1;
        tables_local[table_No].table_contents[local_index[table_No]].typ=typ;//���뺯������
        local_index[table_No]++;//�������ڲ���ָ��++��ָ����һ��Ҫ����ı���
    }
    if(level==0){//����ȫ�ֱ�������ȫ�ֱ���|ȫ�ֳ���|������
        if(typ==7||typ==8||typ==9){//��������char�ͷ���ֵ|int�ͷ���ֵ|�޷���ֵ
            //��ȫ�ֱ�
            strcpy(tables_local[0].table_contents[local_index[0]].ident_name,ident);
            tables_local[0].table_contents[local_index[0]].typ=typ;
            tables_local[0].table_contents[local_index[0]].lev=0;
            tables_local[0].table_contents[local_index[0]].adr=table_No+1;
            local_index[0]++;//ȫ�ַ��ű�ָ������,ָ����һ��Ҫ���
            //�����º�����
            table_No++;//���ű���,ָ�򼴽�����ı�
            strcpy(tables_local[table_No].table_contents[local_index[table_No]].ident_name,ident);//���뺯����
            tables_local[table_No].table_contents[local_index[table_No]].lev=0;
            tables_local[table_No].table_contents[local_index[table_No]].typ=typ;//���뺯������
            local_index[table_No]++;//�������ڲ���ָ��++��ָ����һ��Ҫ����ı���
        }
        else{//ȫ�ֱ���|ȫ�ֳ���
            //printf("%d %s\n",local_index[0],ident);
            strcpy(tables_local[0].table_contents[local_index[0]].ident_name,ident);//�����ʶ������
           // printf("cun%s\n",tables_local[0].table_contents[local_index[0]].ident_name);
            tables_local[0].table_contents[local_index[0]].lev=0;
            tables_local[0].table_contents[local_index[0]].typ=typ;//�����ʶ������
            local_index[0]++;//ȫ�ַ��ű��ָ��++��ָ����һ��Ҫ����ı���
        }
    }
}

/**�����µ��м������м����
*/
char* new_var(){
    //char mid_va[N]={"$mid_"};
    char a[N];
    strcpy(mid_va,"$mid_");
    mid_var_index++;
    strcat(mid_va,itoa(mid_var_index,a,10));
    func_mid_var[table_No]=mid_var_index;
    return mid_va;
}

/**����ÿ�������õ���$mid����
*/
void gen_midvar_num(){
    int i,j;
    for(i=1;i<=table_No;i++){
        if(func_mid_var[i]>0){
            func_mid_var_fi[i]=func_mid_var[i];
            for(j=i-1;j>=0;j--){
                if(func_mid_var[j]>0){
                    func_mid_var_fi[i]=func_mid_var[i]-func_mid_var[j];
                    break;
                }
            }
        }
    }
}

/**�����µ�label
*/
char* new_label(){
    //char new_label[N]={"label_"};
    char a[N];
    strcpy(new_label_nam,"label_");
    strcat(new_label_nam,itoa(label_index,a,10));
    label_index++;
    return new_label_nam;
}

/**�����µ��ַ�����
*/
char* new_str(){
    //char new_strnum[N]={"$string_"};
    char a[N];
    strcpy(new_strnum,"$string_");
    strcat(new_strnum,itoa(str_index,a,10));
    str_index++;
    return new_strnum;
}

/**������Ԫʽ
*/
void gen_mid(int op,char op1[],char op2[],char res[],int adr){
    midcodes[mid_index].op=op;
    strcpy(midcodes[mid_index].op1,op1);
    strcpy(midcodes[mid_index].op2,op2);
    strcpy(midcodes[mid_index].res,res);
    midcodes[mid_index].adr=adr;
    mid_index++;
}


/**����Ż�ǰ�м����
*/
void print_midcode(){
    int i=0,j=0;
    quaters = fopen("_mid_code.txt","w");
    //fprintf(quaters,"---------------------------------------------start to print midcode----------------------------------------------------\n");
   // fprintf(quaters,"mid_num:%d\n",mid_index);
    for(i=0;i<local_index[0];i++){
        switch(tables_local[0].table_contents[i].typ){
            case 1:fprintf(quaters,"var char %s\n",tables_local[0].table_contents[i].ident_name);
                            break;
            case 2:fprintf(quaters,"var int %s\n",tables_local[0].table_contents[i].ident_name);
                    break;
            case 3:fprintf(quaters,"const char %s = '%c'\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].adr);
                    break;
            case 4:fprintf(quaters,"const int %s = %d\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].adr);
                    break;
            case 5:fprintf(quaters,"var char %s[%d]\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].size);
                    break;
            case 6:fprintf(quaters,"var int %s[%d]\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].size);
                    break;
            default:break;
        }
    }
    for(i=0;i<mid_index;i++){
        if(midcodes[i].adr>0&&(midcodes[i].adr==midcodes[i-1].adr+1)){
            //midcodes[i].adr���Ǻ������
            //fprintf(quaters,"cccccccccccc");
            for(j=0;j<local_index[midcodes[i].adr];j++){
                //printf("%d %d\n",midcodes[i].adr,tables_local[midcodes[i].adr].table_contents[j].typ);
                switch(tables_local[midcodes[i].adr].table_contents[j].typ){
                    case 1:fprintf(quaters,"var char %s\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 2:fprintf(quaters,"var int %s\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 3:fprintf(quaters,"const char %s = '%c'\n",tables_local[midcodes[i].adr].table_contents[j].ident_name,tables_local[midcodes[i].adr].table_contents[j].adr);
                            break;
                    case 4:fprintf(quaters,"const int %s = %d\n",tables_local[midcodes[i].adr].table_contents[j].ident_name,tables_local[midcodes[i].adr].table_contents[j].adr);
                            break;
                    case 5:fprintf(quaters,"var char %s[%d]\n",tables_local[midcodes[i].adr].table_contents[j].ident_name,tables_local[midcodes[i].adr].table_contents[j].size);
                            break;
                    case 6:fprintf(quaters,"var int %s[%d]\n",tables_local[midcodes[i].adr].table_contents[j].ident_name,tables_local[midcodes[i].adr].table_contents[j].size);
                            break;
                    case 10:fprintf(quaters,"para int %s\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 11:fprintf(quaters,"para char %s\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 7:fprintf(quaters,"char %s()\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 8:fprintf(quaters,"int %s()\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 9:fprintf(quaters,"void %s()\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            //printf("void %s()\n",tables_local[midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    default:break;
                }
            }
        }
        switch(midcodes[i].op){
            case 1:
            case 2:
            case 3:
            case 4:
                    if(midcodes[i].op2[0]=='\0') {
                        midcodes[i].op2[0]='0';
                        midcodes[i].op2[1]='\0';
                    }
                    fprintf(quaters,"%s = %s %s %s\n",midcodes[i].res,midcodes[i].op1,midcon[midcodes[i].op-1],midcodes[i].op2);
                    break;
            case 5:fprintf(quaters,"%s[%s] = %s\n",midcodes[i].res,midcodes[i].op2,midcodes[i].op1);
                    break;
            case 6:fprintf(quaters,"%s = %s[%s]\n",midcodes[i].res,midcodes[i].op1,midcodes[i].op2);
                    break;
            case 7:fprintf(quaters,"push %s\n",midcodes[i].op1);
                    break;
            case 8:fprintf(quaters,"call %s\n",midcodes[i].op1);
                    break;
            case 9:fprintf(quaters,"call %s\n",midcodes[i].op1);
                   fprintf(quaters,"%s = RET\n",midcodes[i].res);
                    break;
            case 10:fprintf(quaters,"ret %s\n",midcodes[i].op1);
                    break;
            case 11:fprintf(quaters,"GOTO %s\n",midcodes[i].op1);
                    break;
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 18:fprintf(quaters,"%s %s %s\n",midcodes[i].op1,midcon[midcodes[i].op-1],midcodes[i].op2);
                    break;
            case 17:fprintf(quaters,"%s:\n",midcodes[i].op1);
                    break;
            case 19:
            case 20:
            case 21:
            case 22:fprintf(quaters,"%s %s\n",midcon[midcodes[i].op-1],midcodes[i].op1);
                    break;
            case 23:fprintf(quaters,"Exit\n");
                    break;
            case 24:fprintf(quaters,"%s = %s\n",midcodes[i].res,midcodes[i].op1);
                    break;

            }
        //fprintf(quaters,"%s = %s %s %s\n",midcodes[i].res,midcodes[i].op1,midcon[midcodes[i].op-1],midcodes[i].op2);

        //fprintf(quaters,"%-10s%-20s%-20s%-20s%-10d\n",midcon[midcodes[i].op-1],midcodes[i].op1,midcodes[i].op2,midcodes[i].res,midcodes[i].adr);
    }
    fclose(quaters);
}

void opti_print_midcode(){
    int i=0,j=0;
    opti_quaters = fopen("_opti_mid_code.txt","w");
    //fprintf(opti_quaters,"---------------------------------------------start to print midcode----------------------------------------------------\n");
   // fprintf(opti_quaters,"mid_num:%d\n",opti_mid_index);
    for(i=0;i<local_index[0];i++){
        switch(tables_local[0].table_contents[i].typ){
            case 1:fprintf(opti_quaters,"var char %s\n",tables_local[0].table_contents[i].ident_name);
                            break;
            case 2:fprintf(opti_quaters,"var int %s\n",tables_local[0].table_contents[i].ident_name);
                    break;
            case 3:fprintf(opti_quaters,"const char %s = '%c'\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].adr);
                    break;
            case 4:fprintf(opti_quaters,"const int %s = %d\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].adr);
                    break;
            case 5:fprintf(opti_quaters,"var char %s[%d]\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].size);
                    break;
            case 6:fprintf(opti_quaters,"var int %s[%d]\n",tables_local[0].table_contents[i].ident_name,tables_local[0].table_contents[i].size);
                    break;
            default:break;
        }
    }
    for(i=0;i<opti_mid_index;i++){
        if(opti_midcodes[i].adr>0&&(opti_midcodes[i].adr==opti_midcodes[i-1].adr+1)){
            //opti_midcodes[i].adr���Ǻ������
            //fprintf(opti_quaters,"cccccccccccc");
            for(j=0;j<local_index[opti_midcodes[i].adr];j++){
                //printf("%d %d\n",opti_midcodes[i].adr,tables_local[opti_midcodes[i].adr].table_contents[j].typ);
                switch(tables_local[opti_midcodes[i].adr].table_contents[j].typ){
                    case 1:fprintf(opti_quaters,"var char %s\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 2:fprintf(opti_quaters,"var int %s\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 3:fprintf(opti_quaters,"const char %s = '%c'\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name,tables_local[opti_midcodes[i].adr].table_contents[j].adr);
                            break;
                    case 4:fprintf(opti_quaters,"const int %s = %d\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name,tables_local[opti_midcodes[i].adr].table_contents[j].adr);
                            break;
                    case 5:fprintf(opti_quaters,"var char %s[%d]\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name,tables_local[opti_midcodes[i].adr].table_contents[j].size);
                            break;
                    case 6:fprintf(opti_quaters,"var int %s[%d]\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name,tables_local[opti_midcodes[i].adr].table_contents[j].size);
                            break;
                    case 10:fprintf(opti_quaters,"para int %s\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 11:fprintf(opti_quaters,"para char %s\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 7:fprintf(opti_quaters,"char %s()\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 8:fprintf(opti_quaters,"int %s()\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    case 9:fprintf(opti_quaters,"void %s()\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            //printf("void %s()\n",tables_local[opti_midcodes[i].adr].table_contents[j].ident_name);
                            break;
                    default:break;
                }
            }
        }
        switch(opti_midcodes[i].op){
            case 1:
            case 2:
            case 3:
            case 4:
                    if(opti_midcodes[i].op2[0]=='\0') {
                        opti_midcodes[i].op2[0]='0';
                        opti_midcodes[i].op2[1]='\0';
                    }
                    fprintf(opti_quaters,"%s = %s %s %s\n",opti_midcodes[i].res,opti_midcodes[i].op1,midcon[opti_midcodes[i].op-1],opti_midcodes[i].op2);
                    break;
            case 5:fprintf(opti_quaters,"%s[%s] = %s\n",opti_midcodes[i].res,opti_midcodes[i].op2,opti_midcodes[i].op1);
                    break;
            case 6:fprintf(opti_quaters,"%s = %s[%s]\n",opti_midcodes[i].res,opti_midcodes[i].op1,opti_midcodes[i].op2);
                    break;
            case 7:fprintf(opti_quaters,"push %s\n",opti_midcodes[i].op1);
                    break;
            case 8:fprintf(opti_quaters,"call %s\n",opti_midcodes[i].op1);
                    break;
            case 9:fprintf(opti_quaters,"call %s\n",opti_midcodes[i].op1);
                   fprintf(opti_quaters,"%s = RET\n",opti_midcodes[i].res);
                    break;
            case 10:fprintf(opti_quaters,"ret %s\n",opti_midcodes[i].op1);
                    break;
            case 11:fprintf(opti_quaters,"GOTO %s\n",opti_midcodes[i].op1);
                    break;
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 18:fprintf(opti_quaters,"%s %s %s\n",opti_midcodes[i].op1,midcon[opti_midcodes[i].op-1],opti_midcodes[i].op2);
                    break;
            case 17:fprintf(opti_quaters,"%s:\n",opti_midcodes[i].op1);
                    break;
            case 19:
            case 20:
            case 21:
            case 22:fprintf(opti_quaters,"%s %s\n",midcon[opti_midcodes[i].op-1],opti_midcodes[i].op1);
                    break;
            case 23:fprintf(opti_quaters,"Exit\n");
                    break;
            case 24:fprintf(opti_quaters,"%s = %s\n",opti_midcodes[i].res,opti_midcodes[i].op1);
                    break;

            }
        //fprintf(opti_quaters,"%s = %s %s %s\n",opti_midcodes[i].res,opti_midcodes[i].op1,midcon[opti_midcodes[i].op-1],opti_midcodes[i].op2);

        //fprintf(opti_quaters,"%-10s%-20s%-20s%-20s%-10d\n",midcon[opti_midcodes[i].op-1],opti_midcodes[i].op1,opti_midcodes[i].op2,opti_midcodes[i].res,opti_midcodes[i].adr);
    }
    fclose(opti_quaters);

}
/**����words
*/
void trace_words(int tra_num){
    int leijia=0;
    while(ll>=0){
        if(tra_num<=li){
            li-=tra_num;
            sym=words_sym[ll][li];
            return;
        }
        else if(words_num[ll]!=0){
            leijia=li+1;
        }
        tra_num=tra_num-leijia;
        ll--;
        li=words_num[ll]-1;
    }
}

/**�ʷ���������
*/
void _getsym(){
	char c;
    in = fopen(code_name,"r");
	out = fopen("cifa.txt","w");
	c=fgetc(in);
	ll=0;
	if(c==EOF){
        printf("file is empty!");
        exit(0);
	}
	while(c!=EOF){
        while(c!='\n'&&c!=EOF){
            a[ll][code_length[ll]] = c;
            c = fgetc(in);
            code_length[ll]++;
        }
        c=fgetc(in);
        ll++;
	}
	ll_max = ll;
	int cc=0,j=0,n=0,m=0,temp=0;//,bi=0;
	for(ll=0;ll<ll_max;ll++){
        //��ȡÿһ��
        cc=0;
        li=0;
        while(a[ll][cc]!='\0')
        {
	    j=0;//��ʼ��һ���µ�word
	    // ����IDENT��KEY
		if(a[ll][cc]=='_'||(a[ll][cc]>=65&&a[ll][cc]<=90)||(a[ll][cc]>=97&&a[ll][cc]<=122)){//��ĸ
		    temp=0;
			while(a[ll][cc]=='_'||(a[ll][cc]>=65&&a[ll][cc]<=90)||(a[ll][cc]>=97&&a[ll][cc]<=122)||(a[ll][cc]>='0'&&a[ll][cc]<='9'))//��ĸ|����
			{
			    if(a[ll][cc]>=65&&a[ll][cc]<=90){//����дת����Сд����words
                    words[ll][li][j]=a[ll][cc]+32;
			    }
			    else{
                    words[ll][li][j]=a[ll][cc];
			    }
				j++;
				cc++;
			}
			//i--;//�˻ص����һ�ζ����ַ���λ��
			words[ll][li][j]='\0';//��ʾ��ll�е�li��word�������
			//����Ƿ��Ǳ�����
			for(n=0;n<12;n++)
			{
				if(strcmp(words[ll][li],key[n])==0)
				{
				    words_sym[ll][li]=n+1;
					fprintf(out,"<%d  ",n+1);
					m=0;
					while(keycon[n][m]!='\0')
					{
						fprintf(out,"%c",keycon[n][m]);
						m++;
					}
					fprintf(out,"  ");
					m=0;
					while(key[n][m]!='\0')
					{
						fprintf(out,"%c",key[n][m]);
						m++;
					}
					fprintf(out,">\n");
					temp=1;
					break;
					//return n+1;
				}
			}
			if(temp==0) //����KEY
			{
			    fprintf(out,"<13  identcon  %s>\n",words[ll][li]);
			    words_sym[ll][li]=13;
			}
			//i++;
		}

		//��������
		else if(a[ll][cc]>='0'&&a[ll][cc]<='9'){
			while(a[ll][cc]>='0'&&a[ll][cc]<='9')
			{
				words[ll][li][j]=a[ll][cc];
				j++;
				cc++;
			}
			words[ll][li][j]='\0';

			fprintf(out,"<16  us_intcon  %s>\n",words[ll][li]);
			words_sym[ll][li]=16;
		}

		//�����ַ���
		else if(a[ll][cc]=='"'){
            words[ll][li][j]=a[ll][cc];
            j++;
            cc++;
            while((a[ll][cc]!=34)&&(a[ll][cc]>=32&&a[ll][cc]<=126)){//�ַ������ַ�Ҫ��
                if(a[ll][cc]=='\\'){
                    words[ll][li][j]='\\';
                    j++;
                    words[ll][li][j]='\\';
                }
                words[ll][li][j]=a[ll][cc];//�浽word
                j++;
                cc++;
                //printf("%c\n",words[ll][li][j-1]);
               // printf("debug_%d %d %c %s\n",j,strlen(words[ll][li]),words[ll][li][1],words[ll][li]);
            }
            if(a[ll][cc]!='"'){//����ַ�������û��ƥ�䵽˫����
                //����
                error(1,2,ll,cc);//�ַ����������ķ�
                words[ll][li][j]='"';
                words[ll][li][j+1]='\0';
                words_sym[ll][li]=15;
                cc++;
                //fprintf(out,"stringcon_error\n");
                //break;
            }
            else{//û�д�
                words[ll][li][j]='"';
                words[ll][li][j+1]='\0';
                //printf("debug_%d %d %c %s\n",j,strlen(words[ll][li]),words[ll][li][1],words[ll][li]);
                fprintf(out,"<15  stringcon  %s>\n",words[ll][li]);
                words_sym[ll][li]=15;
                cc++;//iʼ��ָ����һ��Ҫ���ĵط�
            }
		}

		//�����ַ�
		else if(a[ll][cc]=='\''){
            //printf("--------");
            words[ll][li][j]=a[ll][cc];
            j++;
            cc++;
            if((a[ll][cc]=='+'||a[ll][cc]=='-') || (a[ll][cc]=='*'||a[ll][cc]=='/') || (a[ll][cc]=='_'||(a[ll][cc]>=65&&a[ll][cc]<=90)||(a[ll][cc]>=97&&a[ll][cc]<=122)) || (a[ll][cc]>='0'&&a[ll][cc]<='9')){
                //�ַ����ַ�Ҫ��
                words[ll][li][j]=a[ll][cc];//�浽word
                j++;
                cc++;
            }
            else{
                error(1,1,ll,cc);
                cc++;
            }
            if(a[ll][cc]!='\''){
                //û��ƥ�䵽�ұߵĵ����ţ�����
                error(1,1,ll,cc);
                //fprintf(out,"charcon_error\n");
            }
            else{
                words[ll][li][j]='\'';
                words[ll][li][j+1]='\0';
                fprintf(out,"<14  charcon  %s>\n",words[ll][li]);
                words_sym[ll][li]=14;
                cc++;//iʼ��ָ����һ��Ҫ���ĵط�
            }
		}

		//����˫�ַ��ֽ��
		else if(a[ll][cc]=='<'){
            words[ll][li][j]=a[ll][cc];
            //�����ж��Ƿ���=
            cc++;
            j++;
            if(a[ll][cc]=='='){
                //sym = "<="
                words[ll][li][j]=a[ll][cc];
                j++;
                cc++;
                words[ll][li][j]='\0';
                fprintf(out,"<22  less_e_sy  %s>\n",words[ll][li]);
                words_sym[ll][li]=22;
            }
            else{
                //sym = "<"
                words[ll][li][j]='\0';
                fprintf(out,"<21  less_sy  %s>\n",words[ll][li]);
                words_sym[ll][li]=21;
            }
		}

		else if(a[ll][cc]=='>'){
            words[ll][li][j]=a[ll][cc];
            //�����ж��Ƿ���=
            cc++;
            j++;
            if(a[ll][cc]=='='){
                //sym = "<="
                words[ll][li][j]=a[ll][cc];
                j++;
                cc++;
                words[ll][li][j]='\0';
                fprintf(out,"<24  more_e_sy  %s>\n",words[ll][li]);
                words_sym[ll][li]=24;
            }
            else{
                //sym = "<"
                words[ll][li][j]='\0';
                fprintf(out,"<23  more_sy  %s>\n",words[ll][li]);
                words_sym[ll][li]=23;
            }
		}

		else if(a[ll][cc]=='='){
            words[ll][li][j]=a[ll][cc];
            //�����ж��Ƿ���=
            cc++;
            j++;
            if(a[ll][cc]=='='){
                //sym = "<="
                words[ll][li][j]=a[ll][cc];
                j++;
                cc++;
                words[ll][li][j]='\0';
                fprintf(out,"<27  e_sy  %s>\n",words[ll][li]);
                words_sym[ll][li]=27;
            }
            else{
                //sym = "<"
                words[ll][li][j]='\0';
                fprintf(out,"<26  givez_sy  %s>\n",words[ll][li]);
                words_sym[ll][li]=26;
            }
		}

		else if(a[ll][cc]=='!'){
            words[ll][li][j]=a[ll][cc];
            //�����ж��Ƿ���=
            cc++;
            j++;
            if(a[ll][cc]=='='){
                //sym = "!="
                words[ll][li][j]=a[ll][cc];
                j++;
                cc++;
                words[ll][li][j]='\0';
                fprintf(out,"<25  not_e_sy  %s>\n",words[ll][li]);
                words_sym[ll][li]=25;
            }
            else{
                error(1,4,ll,cc);
                //fprintf(out,"!_error\n");
            }
		}

		//���뵥�ֽ��
		else {
			switch(a[ll][cc])
			{
				case '+': fprintf(out,"<17  plus  +>\n");words[ll][li][0]='+';words[ll][li][1]='\0';words_sym[ll][li]=17;break;
				case '-': fprintf(out,"<18  minus  ->\n");words[ll][li][0]='-';words[ll][li][1]='\0';words_sym[ll][li]=18;break;
				case '*': fprintf(out,"<19  times  *>\n");words[ll][li][0]='*';words[ll][li][1]='\0';words_sym[ll][li]=19;break;
				case '/': fprintf(out,"<20  div  />\n");words[ll][li][0]='/';words[ll][li][1]='\0';words_sym[ll][li]=20;break;
				case ';': fprintf(out,"<28  semicolon  ;>\n");words[ll][li][0]=';';words[ll][li][1]='\0';words_sym[ll][li]=28;break;
				case '(': fprintf(out,"<29  lparent  (>\n");words[ll][li][0]='(';words[ll][li][1]='\0';words_sym[ll][li]=29;break;
				case ')': fprintf(out,"<30  rparent  )>\n");words[ll][li][0]=')';words[ll][li][1]='\0';words_sym[ll][li]=30;break;
				case '[': fprintf(out,"<31  lbrack  [>\n");words[ll][li][0]='[';words[ll][li][1]='\0';words_sym[ll][li]=31;break;
				case ']': fprintf(out,"<32  rbrack  ]>\n");words[ll][li][0]=']';words[ll][li][1]='\0';words_sym[ll][li]=32;break;
				case '{': fprintf(out,"<33  lbrace  {>\n");words[ll][li][0]='{';words[ll][li][1]='\0';words_sym[ll][li]=33;break;
				case '}': fprintf(out,"<34  rbrace  }>\n");words[ll][li][0]='}';words[ll][li][1]='\0';words_sym[ll][li]=34;break;
				case ',': fprintf(out,"<35  comma  ,>\n");words[ll][li][0]=',';words[ll][li][1]='\0';words_sym[ll][li]=35;break;
				case ' ': li--;break;
                case '\n':li--;break;
                case '\t':li--;break;
                case '\r':li--;break;
				default : error(1,3,ll,cc);
			}
			cc++;
		}

        //һ��word����
        li++;
	}//while
    words_num[ll]=li;
	}
	fclose(in);
	fclose(out);

}

/**�ʷ���������Ԥ��һ������
*/
int getsym(){//Ԥ��һ������,���ظ÷��Ŷ�Ӧ���
    li++;
    while(li==words_num[ll]){ //
        ll++;
        li=0;
    }
     return words_sym[ll][li];
}

/**�﷨��������
*/
void grammer(){
    gout = fopen("gram_res.txt","w");//�﷨�������
//    midout = fopen("_mid_res.txt","w");//������ʦ��ʽ��Ԫʽ���
    int i=0;
    ///��ʼ��������Ϣ/////////////////
    ll=0;//��ָ������
    li=-1;
    /// //////////////////////////////
    ///��ʼ��һϵ�з��ű�////////////
    table_No=0;//���ű�ǰ������ָ���������ɵķ��ű�
    for(i=0;i<MAX_FUC_NUM;i++){
        local_index[i]=0;//ÿ���������ָ��
        have_return[i]=0;
    }
    local_index[0]=0;
    /// //////////////////////////////
    sym=getsym();///Ԥ��һ������
    /*/debug
    int ii=0,jj=0;
    for(ii=0;ii<ll_max;ii++){
        for(jj=0;jj<words_num[ii];jj++){
            printf("%d %d %s %d\n",ii,jj,words[ii][jj],words_sym[ii][jj]);
        }
    }//*///debug
    //words && words_sym  --->>>right

    procedure();///����<����>

    ///����Ƿ��� �з���ֵ����û�з���ֵ ���������
    for(i=0;i<local_index[0]-1;i++){
        if(tables_local[0].table_contents[i].typ==7||tables_local[0].table_contents[i].typ==8){
            if(have_return[tables_local[0].table_contents[i].adr]==0){//error(3,10);
                printf("meaning_error_ERROR_NO_RETURN--%s\n",tables_local[0].table_contents[i].ident_name);
            }
        }
    }
    ///������
    fclose(gout);
//    fclose(midout);
}

/**��ӡ���ű�
*/
void print_table(){
    int i=0,j=0;
    tableout = fopen("_tables.txt","w");
    fprintf(tableout,"-----------------start to print tables-------------------\n");
    fprintf(tableout,"table_No:%d\n",table_No);
    for(i=0;i<=table_No;i++){
        for(j=0;j<local_index[i];j++){
            fprintf(tableout,"%-10d%-10d%-30s%-10d%-10d",i,j,tables_local[i].table_contents[j].ident_name,tables_local[i].table_contents[j].typ,tables_local[i].table_contents[j].adr);
            if(tables_local[i].table_contents[j].typ==5||tables_local[i].table_contents[j].typ==6){//����
                fprintf(tableout,"%-10d\n",tables_local[i].table_contents[j].size);
            }
            else{
                fprintf(tableout,"\n");
            }
        }
    }
    fclose(tableout);
}

/**�õ���ʶ��(������)����
*/
int ret_identyp(int i,char opn_name[]){
/** return
1   out cons int
2   out cons char
3   local cons int
4   local cons char
5   out var int
6   out var char
7   local var int
8   local var char
9   $mid_
10  $string
11  number
12  <empty>
13  character
14  para int
15  para char
16  (-|+)***
17  (<���ʽ>)
*/
    int ri;
    if(opn_name[0]=='$'){
        if(opn_name[1]=='m'){
            //printf("akbvdibwiqvibwa\n");
            return 9;
        }
        else if(opn_name[1]=='s'){//'s'
           // printf("akbvdibwiqvibwa\n");
            return 10;
        }
    }
    if((opn_name[0]>='0'&&opn_name[0]<='9')){//787987
        return 11;
    }
    if(opn_name[0]=='+'||opn_name[0]=='-'){//(+|-)***
        return 16;
    }
    if(opn_name[0]=='\''&&opn_name[2]=='\''){
        return 13;
    }
    if(opn_name[0]=='\0'){
        return 12;
    }
    if(opn_name[0]=='('){
        return 17;
    }
    for(ri=0;ri<local_index[i];ri++){
        if(strcmp(tables_local[i].table_contents[ri].ident_name,opn_name)==0){//��i�ķ��ű���
            if(tables_local[i].table_contents[ri].typ==3){//const char
                return 4;
            }
            else if(tables_local[i].table_contents[ri].typ==4){//const int
                return 3;
            }
            else if(tables_local[i].table_contents[ri].typ==1||tables_local[i].table_contents[ri].typ==5){//var char
                //printf("debug%s\n",tables_local[i].table_contents[ri].ident_name);
                return 8;
            }
            else if(tables_local[i].table_contents[ri].typ==2||tables_local[i].table_contents[ri].typ==6){//var int
                return 7;
            }
            else if(tables_local[i].table_contents[ri].typ==10){
                return 14;
            }
            else if(tables_local[i].table_contents[ri].typ==11){
                return 15;
            }
        }
    }
    for(ri=0;ri<local_index[0];ri++){
        if(strcmp(tables_local[0].table_contents[ri].ident_name,opn_name)==0){//��ȫ�ַ��ű���
            if(tables_local[0].table_contents[ri].typ==3){//const char
                return 2;
            }
            else if(tables_local[0].table_contents[ri].typ==4){//const int
                return 1;
            }
            else if(tables_local[0].table_contents[ri].typ==1||tables_local[0].table_contents[ri].typ==5){//var char
                return 6;
            }
            else if(tables_local[0].table_contents[ri].typ==2||tables_local[0].table_contents[ri].typ==6){//var int
                return 5;
            }
        }
    }
    return 0;
}

/**�����һ����������load��$t0
*/
void get_op1(int i,char opn_name[]){
    int gi,gj;
    char new_op1[N];
    switch(ret_identyp(i,opn_name)){
        case 1:
        case 2:for(gi=0;gi<local_index[0];gi++){
                    if(strcmp(tables_local[0].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"li $t0 %d\n",tables_local[0].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 3:
        case 4:for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"li $t0 %d\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 5:
        case 6:fprintf(aimout,"lw $t0 $$%s\n",opn_name);break;
        case 7:
        case 8:
        case 14:
        case 15:
                for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"lw $t0 %d($fp)\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 9:opn_name[0]=opn_name[1]=opn_name[2]=opn_name[3]=opn_name[4]='0';
                 fprintf(aimout,"lw $t0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(opn_name)+1));
                 break;
        case 10:fprintf(aimout,"la $t0 %s\n",opn_name);break;
        case 11:
                fprintf(aimout,"li $t0 %d\n",atoi(opn_name));break;
        case 12:fprintf(aimout,"li $t0 0\n");break;
        case 13:fprintf(aimout,"li $t0 %d\n",opn_name[1]);break;
        case 16:
                gi=1;
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op1[gi-1]=opn_name[gi];
                    gi++;
                }
                new_op1[gi-1]='\0';
                get_op1(i,new_op1);
                if(opn_name[0]=='-'){//'-'
                    fprintf(aimout,"subu $t0 $0 $t0\n");
                }
                break;
        case 17:
                gi=0;
                gj=0;
                while(opn_name[gi]=='('){
                        gi++;
                }
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op1[gj]=opn_name[gi];
                    gi++;
                    gj++;
                }
                new_op1[gj]='\0';
                strcpy(opn_name,new_op1);

                get_op1(i,opn_name);
    }
}

void opti_get_op1(int i,char opn_name[]){
    int gi,gj;
    char new_op1[N];
    switch(ret_identyp(i,opn_name)){
        case 1:
        case 2:for(gi=0;gi<local_index[0];gi++){
                    if(strcmp(tables_local[0].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"li $t0 %d\n",tables_local[0].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 3:
        case 4:for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"li $t0 %d\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 5:
        case 6:fprintf(opti_aimout,"lw $t0 $$%s\n",opn_name);break;
        case 7:
        case 8:
        case 14:
        case 15:
                for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"lw $t0 %d($fp)\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 9:opn_name[0]=opn_name[1]=opn_name[2]=opn_name[3]=opn_name[4]='0';
                 fprintf(opti_aimout,"lw $t0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(opn_name)+1));
                 break;
        case 10:fprintf(opti_aimout,"la $t0 %s\n",opn_name);break;
        case 11:
                fprintf(opti_aimout,"li $t0 %d\n",atoi(opn_name));break;
        case 12:fprintf(opti_aimout,"li $t0 0\n");break;
        case 13:fprintf(opti_aimout,"li $t0 %d\n",opn_name[1]);break;
        case 16:
                gi=1;
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op1[gi-1]=opn_name[gi];
                    gi++;
                }
                new_op1[gi-1]='\0';
                get_op1(i,new_op1);
                if(opn_name[0]=='-'){//'-'
                    fprintf(opti_aimout,"subu $t0 $0 $t0\n");
                }
                break;
        case 17:
                gi=0;
                gj=0;
                while(opn_name[gi]=='('){
                        gi++;
                }
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op1[gj]=opn_name[gi];
                    gi++;
                    gj++;
                }
                new_op1[gj]='\0';
                strcpy(opn_name,new_op1);

                get_op1(i,opn_name);
    }

}
void get_op1_2a0(int i,char opn_name[]){
    int gi,gj;
    char new_op2[N];
    //printf("debug_%d %s %d\n",i,opn_name,ret_identyp(i,opn_name));
    switch(ret_identyp(i,opn_name)){
        case 1:
        case 2:for(gi=0;gi<local_index[0];gi++){
                    if(strcmp(tables_local[0].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"li $a0 %d\n",tables_local[0].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 3:
        case 4:for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"li $a0 %d\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 5:
        case 6:fprintf(aimout,"lw $a0 $$%s\n",opn_name);break;
        case 7:
        case 8:
        case 14:
        case 15:
                //printf("debug_%d %s\n",i,opn_name);
                for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        //printf("debug_%d %s\n",i,opn_name);
                        fprintf(aimout,"lw $a0 %d($fp)\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 9:opn_name[0]=opn_name[1]=opn_name[2]=opn_name[3]=opn_name[4]='0';
                 fprintf(aimout,"lw $a0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(opn_name)+1));
                 break;
        case 10:fprintf(aimout,"la $a0 %s\n",opn_name);break;
        case 11:
                fprintf(aimout,"li $a0 %d\n",atoi(opn_name));break;
        case 12:fprintf(aimout,"li $a0 0\n");break;
        case 13:fprintf(aimout,"li $a0 %d\n",opn_name[1]);break;
        case 16:gi=1;
                while(opn_name[gi]!='\0'){
                    new_op2[gi-1]=opn_name[gi];
                    gi++;
                }
                new_op2[gi-1]='\0';
                get_op2(i,new_op2);
                if(opn_name[0]=='-'){
                    fprintf(aimout,"subu $a0 $0 $t1\n");
                }
                break;
        case 17:
                gi=0;
                gj=0;
                while(opn_name[gi]=='('){
                        gi++;
                }
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op2[gj]=opn_name[gi];
                    gi++;
                    gj++;
                }
                new_op2[gj]='\0';
                strcpy(opn_name,new_op2);

                get_op1_2a0(i,opn_name);
                break;
        //default:
    }
}

void opti_get_op1_2a0(int i,char opn_name[]){
    int gi,gj;
    char new_op2[N];
    //printf("debug_%d %s %d\n",i,opn_name,ret_identyp(i,opn_name));
    switch(ret_identyp(i,opn_name)){
        case 1:
        case 2:for(gi=0;gi<local_index[0];gi++){
                    if(strcmp(tables_local[0].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"li $a0 %d\n",tables_local[0].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 3:
        case 4:for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"li $a0 %d\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 5:
        case 6:fprintf(opti_aimout,"lw $a0 $$%s\n",opn_name);break;
        case 7:
        case 8:
        case 14:
        case 15:
                //printf("debug_%d %s\n",i,opn_name);
                for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        //printf("debug_%d %s\n",i,opn_name);
                        fprintf(opti_aimout,"lw $a0 %d($fp)\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 9:opn_name[0]=opn_name[1]=opn_name[2]=opn_name[3]=opn_name[4]='0';
                 fprintf(opti_aimout,"lw $a0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(opn_name)+1));
                 break;
        case 10:fprintf(opti_aimout,"la $a0 %s\n",opn_name);break;
        case 11:
                fprintf(opti_aimout,"li $a0 %d\n",atoi(opn_name));break;
        case 12:fprintf(opti_aimout,"li $a0 0\n");break;
        case 13:fprintf(opti_aimout,"li $a0 %d\n",opn_name[1]);break;
        case 16:gi=1;
                while(opn_name[gi]!='\0'){
                    new_op2[gi-1]=opn_name[gi];
                    gi++;
                }
                new_op2[gi-1]='\0';
                get_op2(i,new_op2);
                if(opn_name[0]=='-'){
                    fprintf(opti_aimout,"subu $a0 $0 $t1\n");
                }
                break;
        case 17:
                gi=0;
                gj=0;
                while(opn_name[gi]=='('){
                        gi++;
                }
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op2[gj]=opn_name[gi];
                    gi++;
                    gj++;
                }
                new_op2[gj]='\0';
                strcpy(opn_name,new_op2);

                get_op1_2a0(i,opn_name);
                break;
        //default:
    }

}
/**����ڶ�����������load��$t1
*/
void get_op2(int i,char opn_name[]){
    int gi,gj;
    char new_op2[N];
    switch(ret_identyp(i,opn_name)){
        case 1:
        case 2:for(gi=0;gi<local_index[0];gi++){
                    if(strcmp(tables_local[0].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"li $t1 %d\n",tables_local[0].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 3:
        case 4:for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"li $t1 %d\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 5:
        case 6:fprintf(aimout,"lw $t1 $$%s\n",opn_name);break;
        case 7:
        case 8:
        case 14:
        case 15:
                for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(aimout,"lw $t1 %d($fp)\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 9:opn_name[0]=opn_name[1]=opn_name[2]=opn_name[3]=opn_name[4]='0';
                 fprintf(aimout,"lw $t1 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(opn_name)+1));
                 break;
        case 10:fprintf(aimout,"la $t1 %s\n",opn_name);break;
        case 11:fprintf(aimout,"li $t1 %d\n",atoi(opn_name));break;
        case 12:fprintf(aimout,"li $t1 0\n");break;
        case 13:fprintf(aimout,"li $t1 %d\n",opn_name[1]);break;
        case 16:gi=1;
                while(opn_name[gi]!='\0'){
                    new_op2[gi-1]=opn_name[gi];
                    gi++;
                }
                new_op2[gi-1]='\0';
                get_op2(i,new_op2);
                if(opn_name[0]=='-'){
                    fprintf(aimout,"subu $t1 $0 $t1\n");
                }
                break;
        case 17:
                gi=0;
                gj=0;
                while(opn_name[gi]=='('){
                        gi++;
                }
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op2[gj]=opn_name[gi];
                    gi++;
                    gj++;
                }
                new_op2[gj]='\0';
                strcpy(opn_name,new_op2);

                get_op2(i,opn_name);
        //default:
    }
}

void opti_get_op2(int i,char opn_name[]){
    int gi,gj;
    char new_op2[N];
    switch(ret_identyp(i,opn_name)){
        case 1:
        case 2:for(gi=0;gi<local_index[0];gi++){
                    if(strcmp(tables_local[0].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"li $t1 %d\n",tables_local[0].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 3:
        case 4:for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"li $t1 %d\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 5:
        case 6:fprintf(opti_aimout,"lw $t1 $$%s\n",opn_name);break;
        case 7:
        case 8:
        case 14:
        case 15:
                for(gi=0;gi<local_index[i];gi++){
                    if(strcmp(tables_local[i].table_contents[gi].ident_name,opn_name)==0){
                        fprintf(opti_aimout,"lw $t1 %d($fp)\n",tables_local[i].table_contents[gi].adr);
                        break;
                    }
                 }
                 break;
        case 9:opn_name[0]=opn_name[1]=opn_name[2]=opn_name[3]=opn_name[4]='0';
                 fprintf(opti_aimout,"lw $t1 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(opn_name)+1));
                 break;
        case 10:fprintf(opti_aimout,"la $t1 %s\n",opn_name);break;
        case 11:fprintf(opti_aimout,"li $t1 %d\n",atoi(opn_name));break;
        case 12:fprintf(opti_aimout,"li $t1 0\n");break;
        case 13:fprintf(opti_aimout,"li $t1 %d\n",opn_name[1]);break;
        case 16:gi=1;
                while(opn_name[gi]!='\0'){
                    new_op2[gi-1]=opn_name[gi];
                    gi++;
                }
                new_op2[gi-1]='\0';
                get_op2(i,new_op2);
                if(opn_name[0]=='-'){
                    fprintf(opti_aimout,"subu $t1 $0 $t1\n");
                }
                break;
        case 17:
                gi=0;
                gj=0;
                while(opn_name[gi]=='('){
                        gi++;
                }
                while(opn_name[gi]!='\0'){
                    //printf("%d %c\n",gi,opn_name[gi]);
                    new_op2[gj]=opn_name[gi];
                    gi++;
                    gj++;
                }
                new_op2[gj]='\0';
                strcpy(opn_name,new_op2);

                get_op2(i,opn_name);
        //default:
    }

}
/**���ڱ���������$t0->ȫ�ֱ���int|�ֲ�����int|�м����|����
*/
void save_res(int i,int pro_i){
    int pro_j;
    char new_res[N];
    if(ret_identyp(i,midcodes[pro_i].res)==5||ret_identyp(i,midcodes[pro_i].res)==6){//ȫ�ֱ���int|char
        fprintf(aimout,"sw $t0 $$%s\n",midcodes[pro_i].res);
     }
     else if(ret_identyp(i,midcodes[pro_i].res)==7||ret_identyp(i,midcodes[pro_i].res)==8||ret_identyp(i,midcodes[pro_i].res)==14||ret_identyp(i,midcodes[pro_i].res)==15){//�ֲ�����int|char
         for(pro_j=0;pro_j<local_index[i];pro_j++){
            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,midcodes[pro_i].res)==0){
                fprintf(aimout,"sw $t0 %d($fp)\n",tables_local[i].table_contents[pro_j].adr);
                break;
            }
         }
     }
     else if(ret_identyp(i,midcodes[pro_i].res)==9){//�м����mid
        strcpy(new_res,midcodes[pro_i].res);
        new_res[0]=new_res[1]=new_res[2]=new_res[3]=new_res[4]='0';
        fprintf(aimout,"sw $t0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(new_res)+1));
     }
    // else if(ret_identyp(i,midcodes[pro_i].res)==14||ret_identyp(i,midcodes[pro_i].res)==15){

     //}
}

void opti_save_res(int i,int pro_i){
    int pro_j;
    char new_res[N];
    if(ret_identyp(i,midcodes[pro_i].res)==5||ret_identyp(i,midcodes[pro_i].res)==6){//ȫ�ֱ���int|char
        fprintf(opti_aimout,"sw $t0 $$%s\n",midcodes[pro_i].res);
     }
     else if(ret_identyp(i,midcodes[pro_i].res)==7||ret_identyp(i,midcodes[pro_i].res)==8||ret_identyp(i,midcodes[pro_i].res)==14||ret_identyp(i,midcodes[pro_i].res)==15){//�ֲ�����int|char
         for(pro_j=0;pro_j<local_index[i];pro_j++){
            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,midcodes[pro_i].res)==0){
                fprintf(opti_aimout,"sw $t0 %d($fp)\n",tables_local[i].table_contents[pro_j].adr);
                break;
            }
         }
     }
     else if(ret_identyp(i,midcodes[pro_i].res)==9){//�м����mid
        strcpy(new_res,midcodes[pro_i].res);
        new_res[0]=new_res[1]=new_res[2]=new_res[3]=new_res[4]='0';
        fprintf(opti_aimout,"sw $t0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(new_res)+1));
     }

}
/**���������岿��aimcode
*/
void process_maif(int i){
    //printf("debug\n");
    int pro_i,pro_j;
    int m_i,m_j;
    int flag;
    char new_prc_res[N];
    for(pro_i=0;midcodes[pro_i].adr<i;pro_i++){}//����i֮ǰ�ĺ�������Ԫʽ
    //printf("%d\n",pro_i);
    for(;midcodes[pro_i].adr<i+1&&pro_i<mid_index;pro_i++){
          //printf("%d %d %d \n",i,pro_i,midcodes[pro_i].op);  //
        switch(midcodes[pro_i].op){
            case 1:  /// +
                     get_op1(i,midcodes[pro_i].op1);
                     get_op2(i,midcodes[pro_i].op2);
                     fprintf(aimout,"addu $t0 $t0 $t1\n");
                     save_res(i,pro_i);
                     break;
            case 2:  /// -
                     get_op1(i,midcodes[pro_i].op1);
                     get_op2(i,midcodes[pro_i].op2);
                     fprintf(aimout,"subu $t0 $t0 $t1\n");
                     save_res(i,pro_i);
                     break;
            case 3:  /// *
                     get_op1(i,midcodes[pro_i].op1);
                     get_op2(i,midcodes[pro_i].op2);
                     fprintf(aimout,"multu $t0 $t1\n");
                     fprintf(aimout,"mflo $t0\n");
                     save_res(i,pro_i);
                     break;
            case 4:  /// /
                     get_op1(i,midcodes[pro_i].op1);
                     get_op2(i,midcodes[pro_i].op2);
                     fprintf(aimout,"divu $t0 $t1\n");
                     fprintf(aimout,"mflo $t0\n");
                     save_res(i,pro_i);
                     break;
            case 5:  /// []=
                     get_op1(i,midcodes[pro_i].op1);//-->op1
                     get_op2(i,midcodes[pro_i].op2);//-->op2
                     fprintf(aimout,"li $t2 4\n");
                     fprintf(aimout,"multu $t1 $t2\n");
                     fprintf(aimout,"mflo $t1\n");//-->4*op2
                     if(ret_identyp(i,midcodes[pro_i].res)==5||ret_identyp(i,midcodes[pro_i].res)==6){//ȫ�ֱ���
                         fprintf(aimout,"sw $t0 $$%s($t1)\n",midcodes[pro_i].res);// op1->res[op2]
                     }
                     else if(ret_identyp(i,midcodes[pro_i].res)==7||ret_identyp(i,midcodes[pro_i].res)==8){//�ֲ�����
                        for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,midcodes[pro_i].res)==0&&(tables_local[i].table_contents[pro_j].typ==5||tables_local[i].table_contents[pro_j].typ==6)){
                                //�ֲ�int[] || char[]
                                fprintf(aimout,"li $t2 %d\n",tables_local[i].table_contents[pro_j].adr);
                                fprintf(aimout,"subu $t1 $t2 $t1\n");//-->adr(res)-4*op2
                                fprintf(aimout,"addu $t1 $t1 $fp\n");
                                fprintf(aimout,"sw $t0 ($t1)\n");//op1->res[op2]
                            }
                        }
                     }
                     break;
            case 6:  /// =[]
                     get_op2(i,midcodes[pro_i].op2);//-->op2-->$t1
                     fprintf(aimout,"li $t2 4\n");
                     fprintf(aimout,"multu $t1 $t2\n");
                     fprintf(aimout,"mflo $t1\n");//-->4*op2-->$t1
                     if(ret_identyp(i,midcodes[pro_i].op1)==5||ret_identyp(i,midcodes[pro_i].op1)==6){
                        fprintf(aimout,"lw $t0 $$%s($t1)\n",midcodes[pro_i].op1);
                        save_res(i,pro_i);
                     }
                     else if(ret_identyp(i,midcodes[pro_i].op1)==7||ret_identyp(i,midcodes[pro_i].op1)==8){
                        for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,midcodes[pro_i].op1)==0&&(tables_local[i].table_contents[pro_j].typ==5||tables_local[i].table_contents[pro_j].typ==6)){
                                //�ֲ� int[] || char[]
                                fprintf(aimout,"li $t2 %d\n",tables_local[i].table_contents[pro_j].adr);
                                fprintf(aimout,"subu $t1 $t2 $t1\n");
                                fprintf(aimout,"addu $t1 $t1 $fp\n");
                                fprintf(aimout,"lw $t0 ($t1)\n");
                                save_res(i,pro_i);
                            }
                        }
                     }
                     break;
            case 7:  /// push
                     get_op1(i,midcodes[pro_i].op1);//-->op1-->$t0-->����
                     fprintf(aimout,"sw $t0 %d($sp)\n",-4-atoi(midcodes[pro_i].op2)*4);
                     break;
            case 8:  /// call
                     fprintf(aimout,"sw $fp ($sp)\n");
                     fprintf(aimout,"move $fp $sp\n");
                     fprintf(aimout,"jal $$%s\n",midcodes[pro_i].op1);
                     break;
            case 9:  /// calr
                     fprintf(aimout,"sw $fp ($sp)\n");
                     fprintf(aimout,"move $fp $sp\n");
                     fprintf(aimout,"jal $$%s\n",midcodes[pro_i].op1);
                     if(midcodes[pro_i].res[0]!='\0'){
                        strcpy(new_prc_res,midcodes[pro_i].res);
                        new_prc_res[0]=new_prc_res[1]=new_prc_res[2]=new_prc_res[3]=new_prc_res[4]='0';
                       // midcodes[pro_i].res[0]=midcodes[pro_i].res[1]=midcodes[pro_i].res[2]=midcodes[pro_i].res[3]=midcodes[pro_i].res[4]='0';
                        fprintf(aimout,"sw $t0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(new_prc_res)+1));
                     }
                     break;
            case 10: /// ret
                     if(midcodes[pro_i].op1[0]=='\0'){ //return;
                        if(i!=table_No){//����main����
                            fprintf(aimout,"lw $ra -4($fp)\n");
                            fprintf(aimout,"move $sp $fp\n");
                            fprintf(aimout,"lw $fp 0($fp)\n");
                            fprintf(aimout,"jr $ra\n");
                        }
                        else{//��main����
                            fprintf(aimout,"li $v0 10\n");
                            fprintf(aimout,"syscall\n");
                        }
                     }
                     else{ //return op1;
                        get_op1(i,midcodes[pro_i].op1);//-->op1-->$t0
                        fprintf(aimout,"lw $ra -4($fp)\n");
                        fprintf(aimout,"move $sp $fp\n");
                        fprintf(aimout,"lw $fp 0($fp)\n");
                        fprintf(aimout,"jr $ra\n");
                     }
                     break;
            case 11: /// GOTO
                     fprintf(aimout,"j %s\n",midcodes[pro_i].op1);
                     break;
            case 12: /// <
                     get_op1(i,midcodes[pro_i].op1);//-->op1
                     get_op2(i,midcodes[pro_i].op2);//-->op2
                     fprintf(aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(aimout,"bgez $t0 %s\n",midcodes[pro_i].op1);
                     break;
            case 13: /// <=
                     get_op1(i,midcodes[pro_i].op1);//-->op1
                     get_op2(i,midcodes[pro_i].op2);//-->op2
                     fprintf(aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(aimout,"bgtz $t0 %s\n",midcodes[pro_i].op1);
                     break;
            case 14: /// >
                     get_op1(i,midcodes[pro_i].op1);//-->op1
                     get_op2(i,midcodes[pro_i].op2);//-->op2
                     fprintf(aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(aimout,"blez $t0 %s\n",midcodes[pro_i].op1);
                     break;
            case 15: /// >=
                     get_op1(i,midcodes[pro_i].op1);//-->op1
                     get_op2(i,midcodes[pro_i].op2);//-->op2
                     fprintf(aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(aimout,"bltz $t0 %s\n",midcodes[pro_i].op1);
                     break;
            case 16: /// !=
                     get_op1(i,midcodes[pro_i].op1);//-->op1
                     get_op2(i,midcodes[pro_i].op2);//-->op2
                     pro_i++;
                     fprintf(aimout,"beq $t0 $t1 %s\n",midcodes[pro_i].op1);
                     break;
            case 17: /// label
                     fprintf(aimout,"%s:\n",midcodes[pro_i].op1);
                     break;
            case 18: /// ==
                     get_op1(i,midcodes[pro_i].op1);//-->op1
                     get_op2(i,midcodes[pro_i].op2);//-->op2
                     pro_i++;
                     fprintf(aimout,"bne $t0 $t1 %s\n",midcodes[pro_i].op1);
                     break;
            case 19: /// scanf
                     //ȫ�ֱ���|�ֲ�����
                     if(ret_identyp(i,midcodes[pro_i].op1)==5){//ȫ�ֱ���int
                        fprintf(aimout,"li $v0 5\n");
                        fprintf(aimout,"syscall\n");//read integer
                        fprintf(aimout,"sw $v0 $$%s\n",midcodes[pro_i].op1);
                     }
                     else if(ret_identyp(i,midcodes[pro_i].op1)==6){//ȫ�ֱ���char
                        fprintf(aimout,"li $v0 12\n");
                        fprintf(aimout,"syscall\n");//read character
                        fprintf(aimout,"sw $v0 $$%s\n",midcodes[pro_i].op1);
                     }
                     else if(ret_identyp(i,midcodes[pro_i].op1)==7){//�ֲ�����int
                         fprintf(aimout,"li $v0 5\n");
                         fprintf(aimout,"syscall\n");//read integer
                         for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,midcodes[pro_i].op1)==0){
                                fprintf(aimout,"sw $v0 %d($fp)\n",tables_local[i].table_contents[pro_j].adr);
                                break;
                            }
                         }
                     }
                     else if(ret_identyp(i,midcodes[pro_i].op1)==8){//�ֲ�����char
                        fprintf(aimout,"li $v0 12\n");
                        fprintf(aimout,"syscall\n");//read character
                         for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,midcodes[pro_i].op1)==0){
                                fprintf(aimout,"sw $v0 %d($fp)\n",tables_local[i].table_contents[pro_j].adr);
                                break;
                            }
                         }
                     }
                     break;
            case 20: /// printf
                     switch(ret_identyp(i,midcodes[pro_i].op1)){
                        case 1: //out cons int
                        case 3: //local cons int
                        case 5:
                        case 7:

                        case 11:
                        case 14:
                                get_op1_2a0(i,midcodes[pro_i].op1);
                                fprintf(aimout,"li $v0 1\n");
                                fprintf(aimout,"syscall\n");//print int
                                break;
                        case 9: m_i=pro_i;
                                flag=0;
                                //printf("??");
                                while(m_i>0){
                                    m_i--;
                                    //printf("%d %d\n",m_i,pro_i);
                                    //printf("%s %s %d\n",midcodes[m_i].op1,midcodes[m_i].res,midcodes[m_i].op);
                                    if((strcmp(midcodes[m_i].res,midcodes[pro_i].op1)==0)&&midcodes[m_i].op==6){
                                        //printf("debug1_%s\n",midcodes[pro_i].op1);
                                        for(m_j=0;m_j<=local_index[midcodes[pro_i].adr];m_j++){//i������
                                            if(strcmp(tables_local[midcodes[pro_i].adr].table_contents[m_j].ident_name,midcodes[m_i].op1)==0){
                                                if(tables_local[midcodes[pro_i].adr].table_contents[m_j].typ==5){//char[]
                                                    get_op1_2a0(i,midcodes[pro_i].op1);
                                                    fprintf(aimout,"li $v0 11\n");
                                                    fprintf(aimout,"syscall\n");//print char
                                                }
                                                else if(tables_local[midcodes[pro_i].adr].table_contents[m_j].typ==6){
                                                    get_op1_2a0(i,midcodes[pro_i].op1);
                                                    fprintf(aimout,"li $v0 1\n");
                                                    fprintf(aimout,"syscall\n");//print int
                                                }
                                                //else error(3,3,);  //��ʶ����ƥ��
                                                flag=1;
                                                break;
                                            }
                                        }
                                        if(flag==1) break;
                                        for(m_j=0;m_j<=local_index[0];m_j++){//ȫ�ֺ�����
                                            if(strcmp(tables_local[0].table_contents[m_j].ident_name,midcodes[m_i].op1)==0){
                                                if(tables_local[0].table_contents[m_j].typ==5){//char[]
                                                    get_op1_2a0(i,midcodes[pro_i].op1);
                                                    fprintf(aimout,"li $v0 11\n");
                                                    fprintf(aimout,"syscall\n");//print int
                                                }
                                                else{
                                                    get_op1_2a0(i,midcodes[pro_i].op1);
                                                    fprintf(aimout,"li $v0 1\n");
                                                    fprintf(aimout,"syscall\n");//print int
                                                }
                                                flag=1;
                                            }
                                        }
                                        //flag=1;
                                        //break;
                                        if(flag) break;
                                    }
                                    else if((strcmp(midcodes[m_i].res,midcodes[pro_i].op1)==0)&&midcodes[m_i].op==9){
                                       // printf("debug2_%s\n",midcodes[pro_i].op1);
                                        //printf("!yes\n");
                                        for(m_j=0;m_j<=local_index[0];m_j++){
                                            //printf("%d\n",table_No);
                                            if(strcmp(tables_local[0].table_contents[m_j].ident_name,midcodes[m_i].op1)==0){
                                                if(tables_local[0].table_contents[m_j].typ==7){//char
                                                    get_op1_2a0(i,midcodes[pro_i].op1);
                                                    fprintf(aimout,"li $v0 11\n");
                                                    fprintf(aimout,"syscall\n");//print char
                                                    //printf("22ues\n");
                                                }else{//8 int
                                                    get_op1_2a0(i,midcodes[pro_i].op1);
                                                    fprintf(aimout,"li $v0 1\n");
                                                    fprintf(aimout,"syscall\n");//print int
                                                }
                                            }
                                        }
                                        flag=1;
                                        break;
                                    }

                                }
                                if(flag==0){
                                    get_op1_2a0(i,midcodes[pro_i].op1);
                                    //printf("debug3_%s\n",midcodes[pro_i].op1);
                                    fprintf(aimout,"li $v0 1\n");
                                    fprintf(aimout,"syscall\n");//print int
                                }
                                break;
                        case 2:
                        case 4: //local cons char
                        case 6:
                        case 8:
                        case 13:
                        case 15:
                                get_op1_2a0(i,midcodes[pro_i].op1);
                                fprintf(aimout,"li $v0 11\n");
                                fprintf(aimout,"syscall\n");//print int
                                break;

                        case 10: //$string
                                 get_op1_2a0(i,midcodes[pro_i].op1);
                                 fprintf(aimout,"li $v0 4\n");
                                 fprintf(aimout,"syscall\n");
                                 break;
                        case 16: get_op1_2a0(i,midcodes[pro_i].op1);
                                 //if()
                                 fprintf(aimout,"li $v0 1\n");
                                 fprintf(aimout,"syscall\n");//print int
                                 break;
                        case 17:
                                get_op1_2a0(i,midcodes[pro_i].op1);
                                fprintf(aimout,"li $v0 1\n");
                                fprintf(aimout,"syscall\n");//print int
                                break;
                     }
                     break;
            case 21: /// BNZ

                     break;
            case 22: /// BZ

                     break;
            case 23: /// exit

                     break;
            case 24: ///assign
                     get_op1(i,midcodes[pro_i].op1);
                     //fprintf(aimout,"move $t0 $t0 $t1\n");
                     save_res(i,pro_i);
                     break;
        }
    }
}

/**�����Ż��������岿��aimcode
*/
void opti_process_maif(int i){
    //printf("debug\n");
    int pro_i,pro_j;
    int m_i,m_j;
    int flag;
    char new_prc_res[N];
    for(pro_i=0;opti_midcodes[pro_i].adr<i;pro_i++){}//����i֮ǰ�ĺ�������Ԫʽ
    //printf("%d\n",pro_i);
    for(;opti_midcodes[pro_i].adr<i+1&&pro_i<opti_mid_index;pro_i++){
          //printf("%d %d %d \n",i,pro_i,opti_midcodes[pro_i].op);  //
        switch(opti_midcodes[pro_i].op){
            case 1:  /// +
                     opti_get_op1(i,opti_midcodes[pro_i].op1);
                     opti_get_op2(i,opti_midcodes[pro_i].op2);
                     fprintf(opti_aimout,"addu $t0 $t0 $t1\n");
                     opti_save_res(i,pro_i);
                     break;
            case 2:  /// -
                     opti_get_op1(i,opti_midcodes[pro_i].op1);
                     opti_get_op2(i,opti_midcodes[pro_i].op2);
                     fprintf(opti_aimout,"subu $t0 $t0 $t1\n");
                     opti_save_res(i,pro_i);
                     break;
            case 3:  /// *
                     opti_get_op1(i,opti_midcodes[pro_i].op1);
                     opti_get_op2(i,opti_midcodes[pro_i].op2);
                     fprintf(opti_aimout,"multu $t0 $t1\n");
                     fprintf(opti_aimout,"mflo $t0\n");
                     opti_save_res(i,pro_i);
                     break;
            case 4:  /// /
                     opti_get_op1(i,opti_midcodes[pro_i].op1);
                     opti_get_op2(i,opti_midcodes[pro_i].op2);
                     fprintf(opti_aimout,"divu $t0 $t1\n");
                     fprintf(opti_aimout,"mflo $t0\n");
                     opti_save_res(i,pro_i);
                     break;
            case 5:  /// []=
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2
                     fprintf(opti_aimout,"li $t2 4\n");
                     fprintf(opti_aimout,"multu $t1 $t2\n");
                     fprintf(opti_aimout,"mflo $t1\n");//-->4*op2
                     if(ret_identyp(i,opti_midcodes[pro_i].res)==5||ret_identyp(i,opti_midcodes[pro_i].res)==6){//ȫ�ֱ���
                         fprintf(opti_aimout,"sw $t0 $$%s($t1)\n",opti_midcodes[pro_i].res);// op1->res[op2]
                     }
                     else if(ret_identyp(i,opti_midcodes[pro_i].res)==7||ret_identyp(i,opti_midcodes[pro_i].res)==8){//�ֲ�����
                        for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,opti_midcodes[pro_i].res)==0&&(tables_local[i].table_contents[pro_j].typ==5||tables_local[i].table_contents[pro_j].typ==6)){
                                //�ֲ�int[] || char[]
                                fprintf(opti_aimout,"li $t2 %d\n",tables_local[i].table_contents[pro_j].adr);
                                fprintf(opti_aimout,"subu $t1 $t2 $t1\n");//-->adr(res)-4*op2
                                fprintf(opti_aimout,"addu $t1 $t1 $fp\n");
                                fprintf(opti_aimout,"sw $t0 ($t1)\n");//op1->res[op2]
                            }
                        }
                     }
                     break;
            case 6:  /// =[]
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2-->$t1
                     fprintf(opti_aimout,"li $t2 4\n");
                     fprintf(opti_aimout,"multu $t1 $t2\n");
                     fprintf(opti_aimout,"mflo $t1\n");//-->4*op2-->$t1
                     if(ret_identyp(i,opti_midcodes[pro_i].op1)==5||ret_identyp(i,opti_midcodes[pro_i].op1)==6){
                        fprintf(opti_aimout,"lw $t0 $$%s($t1)\n",opti_midcodes[pro_i].op1);
                        opti_save_res(i,pro_i);
                     }
                     else if(ret_identyp(i,opti_midcodes[pro_i].op1)==7||ret_identyp(i,opti_midcodes[pro_i].op1)==8){
                        for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,opti_midcodes[pro_i].op1)==0&&(tables_local[i].table_contents[pro_j].typ==5||tables_local[i].table_contents[pro_j].typ==6)){
                                //�ֲ� int[] || char[]
                                fprintf(opti_aimout,"li $t2 %d\n",tables_local[i].table_contents[pro_j].adr);
                                fprintf(opti_aimout,"subu $t1 $t2 $t1\n");
                                fprintf(opti_aimout,"addu $t1 $t1 $fp\n");
                                fprintf(opti_aimout,"lw $t0 ($t1)\n");
                                opti_save_res(i,pro_i);
                            }
                        }
                     }
                     break;
            case 7:  /// push
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1-->$t0-->����
                     fprintf(opti_aimout,"sw $t0 %d($sp)\n",-4-atoi(opti_midcodes[pro_i].op2)*4);
                     break;
            case 8:  /// call
                     fprintf(opti_aimout,"sw $fp ($sp)\n");
                     fprintf(opti_aimout,"move $fp $sp\n");
                     fprintf(opti_aimout,"jal $$%s\n",opti_midcodes[pro_i].op1);
                     break;
            case 9:  /// calr
                     fprintf(opti_aimout,"sw $fp ($sp)\n");
                     fprintf(opti_aimout,"move $fp $sp\n");
                     fprintf(opti_aimout,"jal $$%s\n",opti_midcodes[pro_i].op1);
                     if(opti_midcodes[pro_i].res[0]!='\0'){
                        strcpy(new_prc_res,opti_midcodes[pro_i].res);
                        new_prc_res[0]=new_prc_res[1]=new_prc_res[2]=new_prc_res[3]=new_prc_res[4]='0';
                       // opti_midcodes[pro_i].res[0]=opti_midcodes[pro_i].res[1]=opti_midcodes[pro_i].res[2]=opti_midcodes[pro_i].res[3]=opti_midcodes[pro_i].res[4]='0';
                        fprintf(opti_aimout,"sw $t0 %d($fp)\n",jishu[i]+4*(func_mid_var[i]-atoi(new_prc_res)+1));
                     }
                     break;
            case 10: /// ret
                     if(opti_midcodes[pro_i].op1[0]=='\0'){ //return;
                        if(i!=table_No){//����main����
                            fprintf(opti_aimout,"lw $ra -4($fp)\n");
                            fprintf(opti_aimout,"move $sp $fp\n");
                            fprintf(opti_aimout,"lw $fp 0($fp)\n");
                            fprintf(opti_aimout,"jr $ra\n");
                        }
                        else{//��main����
                            fprintf(opti_aimout,"li $v0 10\n");
                            fprintf(opti_aimout,"syscall\n");
                        }
                     }
                     else{ //return op1;
                       opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1-->$t0
                        fprintf(opti_aimout,"lw $ra -4($fp)\n");
                        fprintf(opti_aimout,"move $sp $fp\n");
                        fprintf(opti_aimout,"lw $fp 0($fp)\n");
                        fprintf(opti_aimout,"jr $ra\n");
                     }
                     break;
            case 11: /// GOTO
                     fprintf(opti_aimout,"j %s\n",opti_midcodes[pro_i].op1);
                     break;
            case 12: /// <
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2
                     fprintf(opti_aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(opti_aimout,"bgez $t0 %s\n",opti_midcodes[pro_i].op1);
                     break;
            case 13: /// <=
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2
                     fprintf(opti_aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(opti_aimout,"bgtz $t0 %s\n",opti_midcodes[pro_i].op1);
                     break;
            case 14: /// >
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2
                     fprintf(opti_aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(opti_aimout,"blez $t0 %s\n",opti_midcodes[pro_i].op1);
                     break;
            case 15: /// >=
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2
                     fprintf(opti_aimout,"subu $t0 $t0 $t1\n");
                     pro_i++;
                     fprintf(opti_aimout,"bltz $t0 %s\n",opti_midcodes[pro_i].op1);
                     break;
            case 16: /// !=
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2
                     pro_i++;
                     fprintf(opti_aimout,"beq $t0 $t1 %s\n",opti_midcodes[pro_i].op1);
                     break;
            case 17: /// label
                     fprintf(opti_aimout,"%s:\n",opti_midcodes[pro_i].op1);
                     break;
            case 18: /// ==
                     opti_get_op1(i,opti_midcodes[pro_i].op1);//-->op1
                     opti_get_op2(i,opti_midcodes[pro_i].op2);//-->op2
                     pro_i++;
                     fprintf(opti_aimout,"bne $t0 $t1 %s\n",opti_midcodes[pro_i].op1);
                     break;
            case 19: /// scanf
                     //ȫ�ֱ���|�ֲ�����
                     if(ret_identyp(i,opti_midcodes[pro_i].op1)==5){//ȫ�ֱ���int
                        fprintf(opti_aimout,"li $v0 5\n");
                        fprintf(opti_aimout,"syscall\n");//read integer
                        fprintf(opti_aimout,"sw $v0 $$%s\n",opti_midcodes[pro_i].op1);
                     }
                     else if(ret_identyp(i,opti_midcodes[pro_i].op1)==6){//ȫ�ֱ���char
                        fprintf(opti_aimout,"li $v0 12\n");
                        fprintf(opti_aimout,"syscall\n");//read character
                        fprintf(opti_aimout,"sw $v0 $$%s\n",opti_midcodes[pro_i].op1);
                     }
                     else if(ret_identyp(i,opti_midcodes[pro_i].op1)==7){//�ֲ�����int
                         fprintf(opti_aimout,"li $v0 5\n");
                         fprintf(opti_aimout,"syscall\n");//read integer
                         for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,opti_midcodes[pro_i].op1)==0){
                                fprintf(opti_aimout,"sw $v0 %d($fp)\n",tables_local[i].table_contents[pro_j].adr);
                                break;
                            }
                         }
                     }
                     else if(ret_identyp(i,opti_midcodes[pro_i].op1)==8){//�ֲ�����char
                        fprintf(opti_aimout,"li $v0 12\n");
                        fprintf(opti_aimout,"syscall\n");//read character
                         for(pro_j=0;pro_j<local_index[i];pro_j++){
                            if(strcmp(tables_local[i].table_contents[pro_j].ident_name,opti_midcodes[pro_i].op1)==0){
                                fprintf(opti_aimout,"sw $v0 %d($fp)\n",tables_local[i].table_contents[pro_j].adr);
                                break;
                            }
                         }
                     }
                     break;
            case 20: /// printf
                     switch(ret_identyp(i,opti_midcodes[pro_i].op1)){
                        case 1: //out cons int
                        case 3: //local cons int
                        case 5:
                        case 7:

                        case 11:
                        case 14:
                                opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                fprintf(opti_aimout,"li $v0 1\n");
                                fprintf(opti_aimout,"syscall\n");//print int
                                break;
                        case 9: m_i=pro_i;
                                flag=0;
                                //printf("??");
                                while(m_i>0){
                                    m_i--;
                                    //printf("%d %d\n",m_i,pro_i);
                                    //printf("%s %s %d\n",opti_midcodes[m_i].op1,opti_midcodes[m_i].res,opti_midcodes[m_i].op);
                                    if((strcmp(opti_midcodes[m_i].res,opti_midcodes[pro_i].op1)==0)&&opti_midcodes[m_i].op==6){
                                        //printf("debug1_%s\n",opti_midcodes[pro_i].op1);
                                        for(m_j=0;m_j<=local_index[opti_midcodes[pro_i].adr];m_j++){//i������
                                            if(strcmp(tables_local[opti_midcodes[pro_i].adr].table_contents[m_j].ident_name,opti_midcodes[m_i].op1)==0){
                                                if(tables_local[opti_midcodes[pro_i].adr].table_contents[m_j].typ==5){//char[]
                                                    opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                                    fprintf(opti_aimout,"li $v0 11\n");
                                                    fprintf(opti_aimout,"syscall\n");//print char
                                                }
                                                else if(tables_local[opti_midcodes[pro_i].adr].table_contents[m_j].typ==6){
                                                    opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                                    fprintf(opti_aimout,"li $v0 1\n");
                                                    fprintf(opti_aimout,"syscall\n");//print int
                                                }
                                                //else error(3,3,);  //��ʶ����ƥ��
                                                flag=1;
                                                break;
                                            }
                                        }
                                        if(flag==1) break;
                                        for(m_j=0;m_j<=local_index[0];m_j++){//ȫ�ֺ�����
                                            if(strcmp(tables_local[0].table_contents[m_j].ident_name,opti_midcodes[m_i].op1)==0){
                                                if(tables_local[0].table_contents[m_j].typ==5){//char[]
                                                    opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                                    fprintf(opti_aimout,"li $v0 11\n");
                                                    fprintf(opti_aimout,"syscall\n");//print int
                                                }
                                                else{
                                                    opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                                    fprintf(opti_aimout,"li $v0 1\n");
                                                    fprintf(opti_aimout,"syscall\n");//print int
                                                }
                                                flag=1;
                                            }
                                        }
                                        //flag=1;
                                        //break;
                                        if(flag) break;
                                    }
                                    else if((strcmp(opti_midcodes[m_i].res,opti_midcodes[pro_i].op1)==0)&&opti_midcodes[m_i].op==9){
                                       // printf("debug2_%s\n",opti_midcodes[pro_i].op1);
                                        //printf("!yes\n");
                                        for(m_j=0;m_j<=local_index[0];m_j++){
                                            //printf("%d\n",table_No);
                                            if(strcmp(tables_local[0].table_contents[m_j].ident_name,opti_midcodes[m_i].op1)==0){
                                                if(tables_local[0].table_contents[m_j].typ==7){//char
                                                    opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                                    fprintf(opti_aimout,"li $v0 11\n");
                                                    fprintf(opti_aimout,"syscall\n");//print char
                                                    //printf("22ues\n");
                                                }else{//8 int
                                                    opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                                    fprintf(opti_aimout,"li $v0 1\n");
                                                    fprintf(opti_aimout,"syscall\n");//print int
                                                }
                                            }
                                        }
                                        flag=1;
                                        break;
                                    }

                                }
                                if(flag==0){
                                    opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                    //printf("debug3_%s\n",opti_midcodes[pro_i].op1);
                                    fprintf(opti_aimout,"li $v0 1\n");
                                    fprintf(opti_aimout,"syscall\n");//print int
                                }
                                break;
                        case 2:
                        case 4: //local cons char
                        case 6:
                        case 8:
                        case 13:
                        case 15:
                                opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                fprintf(opti_aimout,"li $v0 11\n");
                                fprintf(opti_aimout,"syscall\n");//print int
                                break;

                        case 10: //$string
                                 opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                 fprintf(opti_aimout,"li $v0 4\n");
                                 fprintf(opti_aimout,"syscall\n");
                                 break;
                        case 16: opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                 //if()
                                 fprintf(opti_aimout,"li $v0 1\n");
                                 fprintf(opti_aimout,"syscall\n");//print int
                                 break;
                        case 17:
                                opti_get_op1_2a0(i,opti_midcodes[pro_i].op1);
                                fprintf(opti_aimout,"li $v0 1\n");
                                fprintf(opti_aimout,"syscall\n");//print int
                                break;
                     }
                     break;
            case 21: /// BNZ

                     break;
            case 22: /// BZ

                     break;
            case 23: /// exit

                     break;
            case 24: ///assign
                     opti_get_op1(i,opti_midcodes[pro_i].op1);
                     //fprintf(opti_aimout,"move $t0 $t0 $t1\n");
                     opti_save_res(i,pro_i);
                     break;
        }
    }

}

/**����Ŀ�����
*/
void gen_aim(){
    //����Ŀ�������Ҫ�õ��ľ��Ƿ��ű�tables_local[]+��Ԫʽ����mid_codes[]+all_str[];
    int i=0;
    int j=0;
    aimout = fopen("_aim_code.asm","w");
    fprintf(aimout,".data\n");
    for(i=0;i<local_index[0];i++){//ȫ�ֱ��еı�������.data
        if(tables_local[0].table_contents[i].typ==1||tables_local[0].table_contents[i].typ==2){//var int||char
            fprintf(aimout,"$$%-18s: .space 4\n",tables_local[0].table_contents[i].ident_name);
        }
        else if(tables_local[0].table_contents[i].typ==5||tables_local[0].table_contents[i].typ==6){//var int[]|char[]
            fprintf(aimout,"$$%-18s: .space %d\n",tables_local[0].table_contents[i].ident_name,4*tables_local[0].table_contents[i].size);
        }
    }
    for(i=0;i<str_index;i++){ //�����е��ַ��������������.data
        fprintf(aimout,"$string_%-12d: .asciiz %s\n",i,all_str[i]);
    }
    fprintf(aimout,"\n\n.text\n");
    ///���濪ʼ���ɳ��򲿷ֵ�Ŀ�����
    fprintf(aimout,"j $$main\n");//����main����
    ///����main���������к���
    for(i=1;i<=table_No;i++){
        fprintf(aimout,"\n$$%s:\n",tables_local[i].table_contents[0].ident_name);//�����i�������ĺ����������ű��0�
        if(i==table_No){
            fprintf(aimout,"move $fp $sp\n");
        }
        fprintf(aimout,"sw $ra,-4($fp)\n");//�����ص�ַѹջ
        ///���˸ĺ���������ջ��0($fp)���ŵ��ú�����$fp,-4($fp)����$ra
        jishu[i]=2;//0->$fp' , 1->$ra
        for(j=0;j<local_index[i];j++){
            if(tables_local[i].table_contents[j].typ==10||tables_local[i].table_contents[j].typ==11||tables_local[i].table_contents[j].typ==1||tables_local[i].table_contents[j].typ==2){
                tables_local[i].table_contents[j].adr=-jishu[i]*4;
                jishu[i]++;
            }
            else if(tables_local[i].table_contents[j].typ==5||tables_local[i].table_contents[j].typ==6){
                tables_local[i].table_contents[j].adr=-jishu[i]*4;
                jishu[i]+=tables_local[i].table_contents[j].size;
            }
        }
        jishu[i]+=func_mid_var_fi[i];
        jishu[i]*=-4;
        fprintf(aimout,"addu $sp $sp %d\n",jishu[i]);///Ϊ����ջԤ��ջ�ռ�
        ///���뺯������
        process_maif(i);//����������
        ///�����������
        if(i<table_No){///main����֮��ĺ�����Ҫ���ص��÷�
            fprintf(aimout,"lw $ra -4($fp)\n");//ȡ��RA
            fprintf(aimout,"move $sp $fp\n");
            fprintf(aimout,"lw $fp ($fp)\n");//��$fp���ص����ߵĻ�
            fprintf(aimout,"jr $ra\n");
        }
        else{///main����������
            fprintf(aimout,"li $v0 10\n");
            fprintf(aimout,"syscall");
        }
    }
    fclose(aimout);
}

/**�����Ż���Ŀ�����
*/
void opti_gen_aim(){
    int i=0;
    int j=0;
    opti_aimout = fopen("_opti_aim_code.asm","w");
    fprintf(opti_aimout,".data\n");
    for(i=0;i<local_index[0];i++){//ȫ�ֱ��еı�������.data
        if(tables_local[0].table_contents[i].typ==1||tables_local[0].table_contents[i].typ==2){//var int||char
            fprintf(opti_aimout,"$$%-18s: .space 4\n",tables_local[0].table_contents[i].ident_name);
        }
        else if(tables_local[0].table_contents[i].typ==5||tables_local[0].table_contents[i].typ==6){//var int[]|char[]
            fprintf(opti_aimout,"$$%-18s: .space %d\n",tables_local[0].table_contents[i].ident_name,4*tables_local[0].table_contents[i].size);
        }
    }
    for(i=0;i<str_index;i++){ //�����е��ַ��������������.data
        fprintf(opti_aimout,"$string_%-12d: .asciiz %s\n",i,all_str[i]);
    }
    fprintf(opti_aimout,"\n\n.text\n");
    ///���濪ʼ���ɳ��򲿷ֵ�Ŀ�����
    fprintf(opti_aimout,"j $$main\n");//����main����
    ///����main���������к���
    for(i=1;i<=table_No;i++){
        fprintf(opti_aimout,"\n$$%s:\n",tables_local[i].table_contents[0].ident_name);//�����i�������ĺ����������ű��0�
        if(i==table_No){
            fprintf(opti_aimout,"move $fp $sp\n");
        }
        fprintf(opti_aimout,"sw $ra,-4($fp)\n");//�����ص�ַѹջ
        ///���˸ĺ���������ջ��0($fp)���ŵ��ú�����$fp,-4($fp)����$ra
        jishu[i]=2;//0->$fp' , 1->$ra
        for(j=0;j<local_index[i];j++){
            if(tables_local[i].table_contents[j].typ==10||tables_local[i].table_contents[j].typ==11||tables_local[i].table_contents[j].typ==1||tables_local[i].table_contents[j].typ==2){
                tables_local[i].table_contents[j].adr=-jishu[i]*4;
                jishu[i]++;
            }
            else if(tables_local[i].table_contents[j].typ==5||tables_local[i].table_contents[j].typ==6){
                tables_local[i].table_contents[j].adr=-jishu[i]*4;
                jishu[i]+=tables_local[i].table_contents[j].size;
            }
        }
        jishu[i]+=func_mid_var_fi[i];
        jishu[i]*=-4;
        fprintf(opti_aimout,"addu $sp $sp %d\n",jishu[i]);///Ϊ����ջԤ��ջ�ռ�
        ///���뺯������
        opti_process_maif(i);//����������
        ///�����������
        if(i<table_No){///main����֮��ĺ�����Ҫ���ص��÷�
            fprintf(opti_aimout,"lw $ra -4($fp)\n");//ȡ��RA
            fprintf(opti_aimout,"move $sp $fp\n");
            fprintf(opti_aimout,"lw $fp ($fp)\n");//��$fp���ص����ߵĻ�
            fprintf(opti_aimout,"jr $ra\n");
        }
        else{///main����������
            fprintf(opti_aimout,"li $v0 10\n");
            fprintf(opti_aimout,"syscall");
        }
    }
    fclose(opti_aimout);

}
/**------------------------------------------���м������Ż�-----------------------------------------------**/
void opti(){
    int i=0;
    int op1=0,op2=0,res=0;
    for(i=0;i<mid_index;i++){
        opti_midcodes[i].adr=midcodes[i].adr;
        strcpy(opti_midcodes[i].op1,midcodes[i].op1);
        strcpy(opti_midcodes[i].op2,midcodes[i].op2);
        opti_midcodes[i].op=midcodes[i].op;
        strcpy(opti_midcodes[i].res,midcodes[i].res);
    }
    opti_mid_index=mid_index;
    /*for(i=0;i<mid_index;i++){
        switch(midcodes[i].op){
            case 1:
            case 2:
            case 3:
            case 4:if(midcodes[i].op1[0]>='0'&&midcodes[i].op1[0]<='9'&&midcodes[i].op2[0]>='0'&&midcodes[i].op2[0]<='9'){
                        op1 = atoi(midcodes[i].op1);
                        op2 = atoi(midcodes[i].op2);
                        switch(midcodes[i].op){
                            case 1:res=op1+op2;break;
                            case 2:res=op1-op2;break;
                            case 3:res=op1*op2;break;
                            case 4:res=op1/op2;break;
                        }
                        opti_midcodes[j]
                   }
        }
    }*/
}

/**------------------------------------------���м������Ż�-----------------------------------------------**/


/**------------------------------------------�ķ�����ĳ���-----------------------------------------------**/
/**����
*/
void procedure(){
    int i=0,pro_flag=0;
    const_dec();//���볣��˵������
    var_dec();//�������˵������
    while(1){//�з���ֵ��������|�޷���ֵ��������
        if(sym==2||sym==3){//int|char,ֻ�����з���ֵ����
            res_fuc();//�����з���ֵ��������,,�ں����������
        }
        else if(sym==4){//void,�������޷���ֵ������Ҳ�п�����������
            sym=getsym();
            if(sym==5){//main,��������������ѭ��
                break;
            }
            else if(sym==13){//��ʶ�����˴�Ϊ������
                fprintf(gout,"line%d :this is a ident!\n",ll+1);
                pro_flag=0;
                for(i=0;i<local_index[0];i++){
                    if(strcmp(tables_local[0].table_contents[i].ident_name,words[ll][li])==0){
                        error(3,4,ll,li);
                        pro_flag=1;
                    }
                }
                //printf("%d\n",pro_flag);
                if(pro_flag==0){
//                    fprintf(midout,"void %s()\n",words[ll][li]);
                   // printf("???\n");
                    fill_table1(words[ll][li],9,0);//���������
                }
                sym=getsym();
                nores_fuc();//�޷���ֵ����
            }
        }
        else{//�����ǣ�Υ��<����>�ķ�����,����<����>
            error(2,2,ll,li);
            sym=getsym();
            //return ;
        }
    }
    main_fuc();//����������,��ʱsym=main
}

/**����˵�� //���п��� �ڴ˺���ʵ��[]
*/
void const_dec(){
    while(sym==1){//�����������constʱ
        sym=getsym();//Ԥ��һ������
        const_def();//���볣�����岿��
        if(sym!=28){//���Ƿֺ�
            error(2,1,ll,li);//ȱ�ٷֺ�
        }
        else{
            fprintf(gout,"line%d :this is a const declaration!\n",ll+1);
            sym=getsym();
        }
    }
}
/**��������
*/
void const_def(){
    int cons_flag=0;
    int i;
    if(sym==2){//int
        sym=getsym();
        if(sym!=13) error(2,9,ll,li);
        else{//��ʶ��
            if(table_No!=0){//�ֲ�
                for(i=0;i<local_index[table_No];i++){
                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                        error(3,4,ll,li);
                        cons_flag=1;
                    }
                }
                if(cons_flag==0){ //û���ظ��ģ����
                    fill_table1(words[ll][li],4,1);
//                    fprintf(midout,"const int %s = ",words[ll][li]);
                    fprintf(gout,"line%d :this is a ident!\n",ll+1);
                }
            }
            else{//ȫ��
                //printf("debug_%d_%s %s\n",local_index[0],tables_local[0].table_contents[0].ident_name,words[ll][li]);
                for(i=0;i<local_index[0];i++){
                    //printf("debug_%d_%s %s\n",local_index[0],tables_local[0].table_contents[0].ident_name,words[ll][li]);
                    if(strcmp(tables_local[0].table_contents[i].ident_name,words[ll][li])==0){
                        error(3,4,ll,li);
                        cons_flag=1;
                    }
                }
                if(cons_flag==0){ //û���ظ��ģ����
                    fill_table1(words[ll][li],4,0);
//                    fprintf(midout,"const int %s = ",words[ll][li]);
                    fprintf(gout,"line%d :this is a ident!\n",ll+1);
                }
            }
            sym=getsym();
        }
        if(sym==26){//'='
            sym=getsym();
            if(sym==17){//+
                sym=getsym();
                if(sym==16){//�޷�������
                    if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=atoi(words[ll][li]); //������ֵ���adr
//                    fprintf(midout,"%d\n",atoi(words[ll][li]));
                    fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
                    fprintf(gout,"line%d :this is a int!\n",ll+1);
                    sym=getsym();
                }
                else{
                    error(2,2,ll,li);
                }
            }
            else if(sym==18){//-
                sym=getsym();
                if(sym==16){//�޷�������
                    if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=-atoi(words[ll][li]);//������ֵ���adr
//                    fprintf(midout,"%d\n",-atoi(words[ll][li]));
                    fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
                    fprintf(gout,"line%d :this is a int!\n",ll+1);
                    sym=getsym();
                }
                else{
                    error(2,2,ll,li);
                }
            }
            else if(sym==16){//�޷�������
                if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=atoi(words[ll][li]);
//                fprintf(midout,"%d\n",atoi(words[ll][li]));
                fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
                fprintf(gout,"line%d :this is a int!\n",ll+1);
                sym=getsym();
            }
            else{//��������
                error(2,2,ll,li);
            }
        }
        else error(2,2,ll,li);

        while(sym==35){//','
            sym=getsym();
            if(sym!=13) error(2,9,ll,li);
            else{//��ʶ��
                cons_flag=0;
                if(table_No!=0){//�Ѿ��к���������ȫ�ֳ���
                    for(i=0;i<local_index[table_No];i++){
                        if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                            error(3,4,ll,li);
                            cons_flag=1;
                        }
                    }
                    if(cons_flag==0){ //û���ظ��ģ����
                        fill_table1(words[ll][li],4,1);
//                        fprintf(midout,"const int %s = ",words[ll][li]);
                        fprintf(gout,"line%d :this is a ident!\n",ll+1);
                    }
                }
                else{
                    for(i=0;i<local_index[table_No];i++){
                        if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                            error(3,4,ll,li);
                            cons_flag=1;
                        }
                    }
                    if(cons_flag==0){ //û���ظ��ģ����
                        fill_table1(words[ll][li],4,0);
//                        fprintf(midout,"const int %s = ",words[ll][li]);
                        fprintf(gout,"line%d :this is a ident!\n",ll+1);
                    }
                }
                sym=getsym();
            }
            if(sym==26){//'='
                sym=getsym();
                if(sym==17){//+
                    sym=getsym();
                    if(sym==16){//�޷�������
                        //������ֵ���adr
                        if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=atoi(words[ll][li]);
//                        fprintf(midout,"%d\n",atoi(words[ll][li]));
                        fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
                        fprintf(gout,"line%d :this is a int!\n",ll+1);
                        sym=getsym();
                    }
                    else error(2,8,ll,li);
                }
                else if(sym==18){//-
                    sym=getsym();
                    if(sym==16){//�޷�������
                        //������ֵ���adr
                        if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=-atoi(words[ll][li]);
//                        fprintf(midout,"%d\n",-atoi(words[ll][li]));
                        fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
                        fprintf(gout,"line%d :this is a int!\n",ll+1);
                        sym=getsym();
                    }
                    else error(2,8,ll,li);
                }
                else if(sym==16){//�޷�������
                    if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=atoi(words[ll][li]);
//                    fprintf(midout,"%d\n",atoi(words[ll][li]));
                    fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
                    fprintf(gout,"line%d :this is a int!\n",ll+1);
                    sym=getsym();
                }
                else error(2,8,ll,li);
            }
            else error(2,8,ll,li);
        }
    }
    else if(sym==3){//char
        sym=getsym();
        if(sym!=13) error(2,9,ll,li);
        else{//��ʶ��
            if(table_No!=0){
                for(i=0;i<local_index[table_No];i++){
                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                        error(3,4,ll,li);
                        cons_flag=1;
                    }
                }
                if(cons_flag==0){ //û���ظ��ģ����
                    fill_table1(words[ll][li],3,1);
//                    fprintf(midout,"const char %s = ",words[ll][li]);
                    fprintf(gout,"line%d :this is a ident!\n",ll+1);
                }
            }
            else{
                //printf("%s\n",words[ll][li]);
                for(i=0;i<local_index[table_No];i++){
                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                        error(3,4,ll,li);
                        cons_flag=1;
                    }
                }
                if(cons_flag==0){ //û���ظ��ģ����
                    fill_table1(words[ll][li],3,0);
//                    fprintf(midout,"const char %s = ",words[ll][li]);
                }
                fprintf(gout,"line%d :this is a ident!\n",ll+1);
            }
            sym=getsym();
        }
        if(sym==26){//'='
            sym=getsym();
            if(sym==14){//�ַ�
//                fprintf(midout,"%s\n",words[ll][li]);
                fprintf(gout,"line%d :this is a character!\n",ll+1);
                if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=words[ll][li][1];//һ���ַ���ת��ASCII
                sym=getsym();
            }
            else error(2,8,ll,li);
        }
        else error(2,8,ll,li);

        while(sym==35){//','
            sym=getsym();
            if(sym!=13) error(2,9,ll,li);
            else{//��ʶ��
                //printf("%d %s\n",table_No,words[ll][li]);
                cons_flag=0;
                if(table_No!=0){
                    for(i=0;i<local_index[table_No];i++){
                        if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                            error(3,4,ll,li);
                            cons_flag=1;
                        }
                    }
                    if(cons_flag==0){ //û���ظ��ģ����
                        fill_table1(words[ll][li],3,1);
//                        fprintf(midout,"const char %s = ",words[ll][li]);
                    }
                    fprintf(gout,"line%d :this is a ident!\n",ll+1);
                }
                else{
                    //printf("%s\n",words[ll][li]);
                    for(i=0;i<local_index[table_No];i++){
                        if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                            error(3,4,ll,li);
                            cons_flag=1;
                        }
                    }
                    if(cons_flag==0){ //û���ظ��ģ����
                        fill_table1(words[ll][li],3,0);
//                        fprintf(midout,"const char %s = ",words[ll][li]);
                    }
                     fprintf(gout,"line%d :this is a ident!\n",ll+1);
                }
                //fill_table1(words[ll][li],3,0);
                sym=getsym();
            }
            if(sym!=26) error(2,8,ll,li);
            else{//'='
                sym=getsym();
                if(sym==14){//�ַ�
//                    fprintf(midout,"%s\n",words[ll][li]);
                    fprintf(gout,"line%d :this is a character!\n",ll+1);
                    if(cons_flag==0) tables_local[table_No].table_contents[local_index[table_No]-1].adr=words[ll][li][1];//һ���ַ���ת��ASCII
                    sym=getsym();
                }
                else{//�����ַ�
                    error(2,2,ll,li);
                    return;
                }
            }
        }
    }
    else error(2,2,ll,li);
}

/**����˵�� //���п��� ��def����ʵ��[]
*/
void var_dec(){
    if(sym==2||sym==3){//int|char
        var_def();
        if(li==0){
            fprintf(gout,"line%d :this is a variable declaration!\n",ll);
        }
        else{
            fprintf(gout,"line%d :this is a variable declaration!\n",ll+1);
        }
    }
}

/**��������
*/
void var_def(){
    int flag=0,i=0;
    int var_flag=0;
    while(sym==2||sym==3){//�����������int|charʱ
        var_flag=0;
        if(sym==2){
            flag=1;//int�ͱ���
        }
        else{//sym=3
            flag=2;//char�ͱ���
        }
        sym=getsym();//Ԥ��һ������
        if(sym==13){//����������Ǳ�ʶ��
            fprintf(gout,"line%d :this is a ident!\n",ll+1);
            sym=getsym();
            //printf("debug%d %d %d\n",ll,li,sym);
            if(sym==29||sym==33){//'('|'{'//˵�����з���ֵ����
               trace_words(2);//�˴���Ҫ���� 2
                return;
            }
            else if(sym==31){//'['//�������
               // printf("???\n");
               if(flag==1){//int
                    if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                //printf("%s\n",tables_local[table_No].table_contents[0].ident_name);
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            fill_table1(words[ll][li-1],6,1);
//                            fprintf(midout,"var int %s",words[ll][li-1]);//�����ڲ���int�����鶨��
                        }
                    }
                    else{
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            fill_table1(words[ll][li-1],6,0);//�����ڲ���int�����鶨��
//                            fprintf(midout,"var int %s",words[ll][li-1]);
                        }

                    }
               }
               else{//flag==2,char
                    if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            fill_table1(words[ll][li-1],5,1);//�����ڲ���char�����鶨��
//                            fprintf(midout,"var char %s",words[ll][li-1]);
                        }
                    }
                    else{
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            fill_table1(words[ll][li-1],5,0);
//                            fprintf(midout,"var int %s",words[ll][li-1]);//�����ڲ���int�����鶨��
                        }
                    }
               }
                sym=getsym();
                if(sym==16){//�޷�������&&>0

                    if(atoi(words[ll][li])<=0) error(2,7,ll,li);
                    //���������С
                    if(var_flag==0) {
                        tables_local[table_No].table_contents[local_index[table_No]-1].size=atoi(words[ll][li]);
//                        fprintf(midout,"[%d]\n",atoi(words[ll][li]));
                    }
                    // printf("ssd\n");
                    sym=getsym();
                    if(sym==32){//']'
                        sym=getsym();
                    }
                    else error(2,4,ll,li);
                }
            }
            else {//','|';',�����ղŶ������һ������
               if(flag==1){//int
                    //printf("debug_%s\n",words[ll][li]);
                    if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            //printf("%s\n",words[ll][li]);
                            fill_table1(words[ll][li-1],2,1);//�����ڲ���int�ͱ�������
//                            fprintf(midout,"var int %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                        }
                    }
                    else{
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            fill_table1(words[ll][li-1],2,0);//ȫ��int��������
//                            fprintf(midout,"var int %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                        }
                    }
               }
               else{//flag==2,char
                    if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            fill_table1(words[ll][li-1],1,1);//�����ڲ���int�ͱ�������
//                            fprintf(midout,"var char %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                        }
                    }
                    else{
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                error(3,4,ll,li-1);
                                var_flag=1;
                            }
                        }
                        if(var_flag==0){ //û���ظ��ģ����
                            fill_table1(words[ll][li-1],1,0);//ȫ��int��������
//                            fprintf(midout,"var char %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                        }
                    }
               }
            }
            //else error(2,2,ll,li);
            while(sym==35){//',':{,identcon}
                var_flag=0;
                sym=getsym();
                if(sym==13){//����������Ǳ�ʶ��
                    fprintf(gout,"line%d :this is a ident!\n",ll+1);
                    sym=getsym();
                    //�������
                    if(sym==31){//'['//�������
                       // printf("???\n");
                       if(flag==1){//int
                            if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],6,1);
//                                    fprintf(midout,"var int %s",words[ll][li-1]);//�����ڲ���int�����鶨��
                                }
                            }
                            else{
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],6,0);//�����ڲ���int�����鶨��
//                                    fprintf(midout,"var int %s",words[ll][li-1]);
                                }
                            }
                       }
                       else{//flag==2,char
                            if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],5,1);//�����ڲ���char�����鶨��
//                                    fprintf(midout,"var char %s",words[ll][li-1]);
                                }
                            }
                            else{
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],5,0);
//                                    fprintf(midout,"var int %s",words[ll][li-1]);//�����ڲ���int�����鶨��
                                }
                            }
                       }
                        sym=getsym();
                        if(sym!=16) error(2,7,ll,li);
                        else if(atoi(words[ll][li])<=0) error(2,7,ll,li);
                        else{//�޷�������&&>0
                            //���������С
                            if(var_flag==0) {
                                tables_local[table_No].table_contents[local_index[table_No]-1].size=atoi(words[ll][li]);
//                                fprintf(midout,"[%d]\n",atoi(words[ll][li]));
                            }
                            // printf("ssd\n");
                        }
                        sym=getsym();
                        if(sym==32){//']'
                            sym=getsym();
                        }
                        else error(2,4,ll,li);
                    }
                    else{//','|';',�����ղŶ������һ������
                        if(flag==1){//int
                            if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],2,1);//�����ڲ���int�ͱ�������
//                                    fprintf(midout,"var int %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                                }
                            }
                            else{
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],2,0);//ȫ��int��������
//                                    fprintf(midout,"var int %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                                }
                            }
                       }
                        else{//flag==2,char
                            if(table_No!=0){//ȫ�ֱ��Ѿ���ʼ��������������Ѿ���ʼ��
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],1,1);//�����ڲ���int�ͱ�������
//                                    fprintf(midout,"var char %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                                }
                            }
                            else{
                                for(i=0;i<local_index[table_No];i++){
                                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li-1])==0){
                                        error(3,4,ll,li-1);
                                        var_flag=1;
                                    }
                                }
                                if(var_flag==0){ //û���ظ��ģ����
                                    fill_table1(words[ll][li-1],1,0);//ȫ��int��������
//                                    fprintf(midout,"var char %s\n",words[ll][li-1]);//�����ڲ���int�����鶨��
                                }
                            }
                       }
                    }
                    //else error(2,2,ll,li);
                }
            }
            if(sym!=28){//���Ƿֺ�
                error(2,1,ll,li);//ȱ�ٷֺ�
            }
            else{
               fprintf(gout,"line%d :this is a variable definition!\n",ll+1);
               sym=getsym();
            }
        }
        else{
            error(2,3,ll,li);
        }
    }
}

/**�з���ֵ��������
*/
void res_fuc(){
    int i=0;//�������Ƿ�����
    int res_flag=0;
    if(sym==2){//int�ͷ���ֵ
        sym=getsym();
        if(sym!=13) error(2,9,ll,li);
        else{//��ʶ��
            fprintf(gout,"line%d :this is a ident!\n",ll+1);
            for(i=0;i<local_index[0];i++){
                if(strcmp(tables_local[0].table_contents[i].ident_name,words[ll][li])==0){
                    error(3,4,ll,li);
                    res_flag=1;
                }
            }
            if(res_flag==0){//û���ظ��ģ����
                fill_table1(words[ll][li],8,0);
//                fprintf(midout,"int %s()\n",words[ll][li]);
            }
        }
        sym=getsym();
        if(sym==29){//'(',�в���
            sym=getsym();
            param();
            if(sym!=30) error(2,3,ll,li);
            else sym=getsym(); //')'
            if(sym!=33) error(2,2,ll,li);
            else sym=getsym(); //'{'
            com_stam();//�������
            if(sym!=34) error(2,5,ll,li);
            else{//'}'
                fprintf(gout,"line%d :this is a paramed int res_func!\n",ll+1);
                sym=getsym();
            }
        }
        else {
            if(sym!=33) error(2,5,ll,li);
            else sym=getsym(); //'{'
            com_stam();//�������
            if(sym==34){//'}'
                fprintf(gout,"line%d :this is a no_paramed int res_fuc!\n",ll+1);
                sym=getsym();
            }
            else error(2,5,ll,li);//'}'��ƥ��
        }
    }

    else if(sym==3){//char�ͷ���ֵ
        sym=getsym();
        if(sym!=13) error(2,9,ll,li);
        else{//��ʶ��
            fprintf(gout,"line%d :this is a ident!\n",ll+1);

            for(i=0;i<local_index[0];i++){
                if(strcmp(tables_local[0].table_contents[i].ident_name,words[ll][li])==0){
                    error(3,4,ll,li);
                    res_flag=1;
                }
            }
            if(res_flag==0){//û���ظ��ģ����
                fill_table1(words[ll][li],7,0);
//                fprintf(midout,"char %s()\n",words[ll][li]);
            }
            sym=getsym();
        }
        if(sym==29){//'('���в�
            sym=getsym();
            param();
            if(sym!=30) error(2,3,ll,li);
            else sym=getsym(); //')'
            if(sym!=33) error(2,2,ll,li);
            else sym=getsym(); //'{'
            com_stam();//�������
            if(sym==34){//'}'
                fprintf(gout,"line%d :this is a paramed char res_func!\n",ll+1);
                sym=getsym();
            }
            else error(2,5,ll,li);//'}'��ƥ��
        }
        else {
            if(sym!=33) error(2,5,ll,li);
            else sym=getsym(); //'{'
            com_stam();//�������
            if(sym==34){//'}'
                fprintf(gout,"line%d :this is a no_paramed char res_func!\n",ll+1);
                sym=getsym();
            }
            else error(2,5,ll,li);
        }
    }
}

/**�޷���ֵ��������
*/
void nores_fuc(){
    //sym�Ѿ��Ǳ�ʶ������һ��
    if(sym==29){//'('
        sym=getsym();
        param();
        if(sym!=30) error(2,3,ll,li);
        else{//')'
           // printf("asa???");
            sym=getsym();
        }
        if(sym!=33) error(2,5,ll,li);
        else{
            sym=getsym();
        }
        com_stam();//�������
        if(sym==34){//'}'
            fprintf(gout,"line%d :this is a paramed nores_fuc\n",ll+1);
            sym=getsym();
        }
        else{//'}'��ƥ��
            error(2,5,ll,li);
        }
    }
    else if(sym==33){//'{'

        sym=getsym();
        com_stam();//�������
        //printf("debug-%s\n",words[ll][li]);
        if(sym==34){//'}'
            fprintf(gout,"line%d :this is a no_paramed nores_fuc!\n",ll+1);
            sym=getsym();
        }
        else{//'}'��ƥ��
            error(2,5,ll,li);
        }

    }
    else error(2,2,ll,li);
}

/**������
*/
void param(){
    int i=0,para_flag=0;
    if(sym==2||sym==3){//int|char
        fprintf(gout,"line%d :this is a type ident!\n",ll+1);
        if(sym==2){//int
            sym=getsym();
            if(sym==13){//��ʶ��
                for(i=0;i<local_index[table_No];i++){
                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                        error(3,4,ll,li);
                        para_flag=1;
                    }
                }
                if(para_flag==0){
//                    fprintf(midout,"para int %s\n",words[ll][li]);
                    fill_table1(words[ll][li],10,1);//int�Ͳ���//���뺯�����ű�
                }
                fprintf(gout,"line%d :this is a ident!\n",ll+1);
                sym=getsym();
            }
            else error(2,6,ll,li);//���������
        }
        else if(sym==3){//char
            sym=getsym();
            if(sym==13){//��ʶ��
                for(i=0;i<local_index[table_No];i++){
                    if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                        error(3,4,ll,li);
                        para_flag=1;
                    }
                }
                if(para_flag==0){
//                    fprintf(midout,"para char %s\n",words[ll][li]);
                    fill_table1(words[ll][li],11,1);
                }
                fprintf(gout,"line%d :this is a ident!\n",ll+1);
                sym=getsym();
            }
            else error(2,6,ll,li);//���������
        }
        while(sym==35){//','
            sym=getsym();
            para_flag=0;
            if(sym==2||sym==3){//int|char
                fprintf(gout,"line%d :this is a type ident!\n",ll+1);
                if(sym==2){//int
                    sym=getsym();
                    if(sym==13){//��ʶ��
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                                error(3,4,ll,li);
                                para_flag=1;
                            }
                        }
                        if(para_flag==0){
//                            fprintf(midout,"para int %s\n",words[ll][li]);
                            fill_table1(words[ll][li],10,1);//int�Ͳ���
                        }
                        fprintf(gout,"line%d :this is a ident!\n",ll+1);
                        sym=getsym();
                    }
                    else error(2,6,ll,li);
                }
                else if(sym==3){//char
                    sym=getsym();
                    if(sym==13){//��ʶ��
                        for(i=0;i<local_index[table_No];i++){
                            if(strcmp(tables_local[table_No].table_contents[i].ident_name,words[ll][li])==0){
                                error(3,4,ll,li);
                                para_flag=1;
                            }
                        }
                        if(para_flag==0){
//                            fprintf(midout,"para char %s\n",words[ll][li]);
                            fill_table1(words[ll][li],11,1);
                        }
                        fprintf(gout,"line%d :this is a ident!\n",ll+1);
                        sym=getsym();
                    }
                    else error(2,6,ll,li);//���������
                }
            }
            else error(2,6,ll,li);//���������
        }
        fprintf(gout,"line%d :this is a parameter table!\n",ll+1);
    }
    else{
        error(2,6,ll,li);
    }
}

/**���--��������
*/
int lk_table(int lk_ll,int lk_li){
    int lk_i=0;
    for(lk_i=1;lk_i<local_index[table_No];lk_i++){
        if(strcmp(tables_local[table_No].table_contents[lk_i].ident_name,words[lk_ll][lk_li])==0){
            return tables_local[table_No].table_contents[lk_i].typ;
        }
    }
    for(lk_i=0;lk_i<local_index[0];lk_i++){
        if(strcmp(tables_local[0].table_contents[lk_i].ident_name,words[lk_ll][lk_li])==0){
            return tables_local[0].table_contents[lk_i].typ;
        }
    }
    error(3,5,lk_ll,lk_li);
    return 0;
}

/**���--�������ĸ�����
*/
int lk_table_i(int lk_ll,int lk_li){
    int lk_i=0;
    /*for(lk_i=1;lk_i<local_index[table_No];lk_i++){
        if(strcmp(tables_local[table_No].table_contents[lk_i].ident_name,words[lk_ll][lk_li])==0){
            return tables_local[table_No].table_contents[lk_i].typ;
        }
    }*/
    for(lk_i=0;lk_i<local_index[0];lk_i++){
        if(strcmp(tables_local[0].table_contents[lk_i].ident_name,words[lk_ll][lk_li])==0){
            return tables_local[0].table_contents[lk_i].adr;
        }
    }
    return 0;
}

/**���--���ش�С
*/
int lk_table_size(int lk_ll,int lk_li){
    int lk_i=0;
    for(lk_i=1;lk_i<local_index[table_No];lk_i++){
        if(strcmp(tables_local[table_No].table_contents[lk_i].ident_name,words[lk_ll][lk_li])==0){
            return tables_local[table_No].table_contents[lk_i].size;
        }
    }
    for(lk_i=0;lk_i<local_index[0];lk_i++){
        if(strcmp(tables_local[0].table_contents[lk_i].ident_name,words[lk_ll][lk_li])==0){
            return tables_local[0].table_contents[lk_i].size;
        }
    }
    //error(3,5);
    return 0;
}

/**����
*/
char* factor(){
    //int i=0;
    int ass_size=0,fac_flag=0,look_tb=0;//flag=0,
    char a[N];
    if(sym==13){//��ʶ��    ��ʶ��|<��ʶ��>'['<���ʽ>']'|<�з���ֵ�����������>
        strcpy(a,words[ll][li]);
        //printf("succ-%s\n",a);
        fprintf(gout,"line%d :this is a ident!\n",ll+1);
        sym=getsym();
        if(sym==31){//[
            trace_words(1);
            look_tb=lk_table(ll,li);
            if(look_tb!=5&&look_tb!=6) error(3,3,ll,li);
            if(look_tb==5) exs_typ=1;
            fac_flag=exs_typ;
            //printf("%d -- %d--%d\n",ll,lk_table(ll,li),exs_typ);
            ass_size=lk_table_size(ll,li);
            sym=getsym();
            sym=getsym();
            strcpy(factor_nam,exprs());//���ʽ
            if(if_number(factor_nam)){
                if(atoi(factor_nam)<0) error(3,1,ll,li);
                if(atoi(factor_nam)>=ass_size) error(3,2,ll,li);
            }
            if(exs_typ!=0) error(3,7,ll,li);
            //sym=getsym();
            if(sym==32){//]
                sym=getsym();
                strcpy(new_factor,new_var());
                gen_mid(6,a,factor_nam,new_factor,table_No);
//                fprintf(midout,"%s = %s[%s]\n",midcodes[mid_index-1].res,midcodes[mid_index-1].op1,midcodes[mid_index-1].op2);
                //printf("fac_%d %d\n",ll,exs_typ);
                exs_typ=fac_flag;
                return new_factor;
            }
            else error(2,4,ll,li);
        }
        else {//��ʶ��|<�з���ֵ�����������>
            //trace_words(1);
           // printf("wt%d\n",lk_table(ll,li));
            look_tb=lk_table(ll,li-1);
            if((look_tb>=1&&look_tb<=4)||look_tb==10||look_tb==11){//char|int|cons char|cons int
                //printf("%d %d %s\n",ll,lk_table(ll,li-1),words[ll][li-1]);
                fprintf(gout,"line%d :this is a ident!\n",ll+1);
                if(look_tb==1||look_tb==3||look_tb==11) exs_typ=1;
                //sym=getsym();
                ///return words[ll][li-1];
                strcpy(factor_nam,new_var());
                strcpy(factor_nam_res,factor_nam);
//                fprintf(midout,"%s = %s\n",factor_nam_res,words[ll][li-1]);
                gen_mid(24,words[ll][li-1],"",factor_nam_res,table_No);
                return factor_nam_res;

                //if(look_tb==1||)
            }
            else if(look_tb==7||look_tb==8){
                //printf("fan\n");
                if(look_tb==7) exs_typ=1;
                //sym=getsym();
                strcpy(factor_nam,new_var());
                strcpy(factor_nam_res,factor_nam);
                //printf("debug%d %d %d\n",ll+1,li,exs_typ);
                res_call(lk_table_i(ll,li-1));
                //printf("res_c%d %d %d\n",ll+1,li,exs_typ);
                return factor_nam_res;
            }
            else return "";
            sym=getsym();
        }
        fprintf(gout,"line%d :this is a factor!\n",ll+1);
    }

    else if(sym==29){//'('    '('<���ʽ>')'
        sym=getsym();
        strcpy(factor_nam,exprs());//���ʽ
        if(sym==30){//')'
            sym=getsym();
            par_factor_nam[0]='(';
            par_factor_nam[1]='\0';
            strcat(par_factor_nam,factor_nam);
            fprintf(gout,"line%d :this is a factor!\n",ll+1);
            exs_typ=0;
            return par_factor_nam;
        }
        else error(2,3,ll,li);
    }
    else if(sym==17||sym==18||sym==16){//+|-|<�޷�������>     <����>
       // printf("??????????%s\n",words[ll][li]);
        if(sym==17||sym==18){//+|-
            factor_nam[0]=words[ll][li][0];

            factor_nam[1]='\0';
            sym=getsym();
            if(sym==16){
                strcat(factor_nam,words[ll][li]);
                fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
                fprintf(gout,"line%d :this is a int!\n",ll+1);
                fprintf(gout,"line%d :this is a factor!\n",ll+1);
                sym=getsym();
                return factor_nam;
            }
        }
        else if(sym==16){
            //printf("this\n");
            strcpy(factor_nam,words[ll][li]);
            fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
            fprintf(gout,"line%d :this is a int!\n",ll+1);
            fprintf(gout,"line%d :this is a factor!\n",ll+1);
            sym=getsym();
            return factor_nam;
        }
    }
    else if(sym==14){//�ַ�
        exs_typ=1;
        strcpy(factor_nam,words[ll][li]);
        fprintf(gout,"line%d :this is a char!\n",ll+1);
        fprintf(gout,"line%d :this is a factor!\n",ll+1);
        sym=getsym();
        return factor_nam;
    }
    else error(2,2,ll,li);
    return "";
}

/**��
*/
char* item(){
    int flag_sym;
    char f1_nc[N],f2[N],t[N];
    strcpy(f1,factor());//����
    //printf("item%d %d\n",ll,exs_typ);
    strcpy(f1_nc,f1);
    while(sym==19||sym==20){//{�˷������
        flag_sym=sym;
        fprintf(gout,"line%d :this is a multi op!\n",ll+1);
        sym=getsym();
        //printf("succ\n");
        strcpy(f2,factor());//����}
       // printf("succ\n");
        strcpy(t,new_var());
        strcpy(f1,f1_nc);
        if(flag_sym==19){//*
            gen_mid(3,f1,f2,t,table_No);
//            fprintf(midout,"%s = %s + %s\n",midcodes[mid_index-1].res,midcodes[mid_index-1].op1,midcodes[mid_index-1].op2);
        }
        else{// /
            gen_mid(4,f1,f2,t,table_No);
//            fprintf(midout,"%s = %s + %s\n",midcodes[mid_index-1].res,midcodes[mid_index-1].op1,midcodes[mid_index-1].op2);
        }
        strcpy(f1,t);
        strcpy(f1_nc,f1);
        exs_typ=0;
    }
    fprintf(gout,"line%d :this is a item!\n",ll+1);
    return f1;
}

/**���ʽ
*/
char* exprs(){
   // printf("???\n");
    int flag=0;
    int flag_sym;
    char t1_nc[N],t2[N],e[N];
    char a[N];
    exs_typ=0;
    if(sym==17||sym==18){//[+|-]
        if(sym==17){//+
            flag=1;
        }
        else{//-
            flag=2;
        }
        sym=getsym();
        exs_typ=0;
    }
   // printf("succ\n");
   //printf("xiang %d %d\n",ll,exs_typ);
    strcpy(t1,item());//<��>
    //
    //
    if(flag==2){//-
        a[0]='-';
        a[1]='\0';
        strcat(a,t1);
        strcpy(t1,a);
        exs_typ=0;
    }
    strcpy(t1_nc,t1);
    //printf("why%s %d\n",words[ll][li+1],sym);
    while(sym==17||sym==18){//{�ӷ������
        //printf("why\n");
        flag_sym=sym;

        fprintf(gout,"line%d :this is a add op!\n",ll+1);
        sym=getsym();
        strcpy(t2,item());//��}
        strcpy(e,new_var());//�����µ��м������
        strcpy(t1,t1_nc);
        //printf("??????????????2333%s\n",words[ll][li]);
        if(flag_sym==17){//+
            //printf("debug-%s\n",t1);
            gen_mid(1,t1,t2,e,table_No);
//            fprintf(midout,"%s = %s + %s\n",midcodes[mid_index-1].res,midcodes[mid_index-1].op1,midcodes[mid_index-1].op2);
        }
        else{//-
            gen_mid(2,t1,t2,e,table_No);
//            fprintf(midout,"%s = %s - %s\n",midcodes[mid_index-1].res,midcodes[mid_index-1].op1,midcodes[mid_index-1].op2);
        }
        strcpy(t1,e);
        strcpy(t1_nc,t1);
        exs_typ=0;
    }
    fprintf(gout,"line%d :this is a expression!\n",ll+1);
   // printf("???\n");
    return t1;
}

/**ֵ������
*/
void val_param(int val_p_i){
    char va[N];
    int i,j,index;//,fuc_num;
    char na[N];
    char x_va[MAX_PARA_NUM][N];
    char x_na[MAX_PARA_NUM][N];
    strcpy(va,exprs());//<���ʽ>
    //printf("val_%d %d %d\n",ll+1,li,exs_typ);
    if(tables_local[val_p_i].table_contents[1].typ!=(exs_typ+10)) error(3,6,ll,li);
    //strcpy(new_pa,new_var());
    //gen_mid(7,va,"1","",table_No);
    index=0;
    strcpy(x_va[index],va);
    strcpy(x_na[index],"1");
//    fprintf(midout,"push %s\n",va);
    i=2;
    while(sym==35){//','
        sym=getsym();
        strcpy(va,exprs());//<���ʽ>
        itoa(i,na,10);
        if(tables_local[val_p_i].table_contents[i].typ!=(exs_typ+10)) error(3,6,ll,li);
        i++;
        index++;
        strcpy(x_va[index],va);
        strcpy(x_na[index],na);
        //gen_mid(7,va,na,"",table_No);
//        fprintf(midout,"push %s\n",va);
    }
    for(j=0;j<=index;j++){
        gen_mid(7,x_va[j],x_na[j],"",table_No);
    }
    fprintf(gout,"line%d :this is a value parameter table!\n",ll+1);
}
/**�������
*/
void com_stam(){
    //printf("--->>>into com_stam...\n");
    const_dec();//���볣��˵������,���ӳ�����ʵ��[]
    var_dec();//�������˵�����֣����ӳ�����ʵ��[]
    //printf("after var_dec%d %d %d \n",ll+1,li+1,sym);
    stam_q();//�����,0������������ӳ�����ʵ��{}
    fprintf(gout,"line%d :this is a compound statement!\n",ll+1);
    //printf("<<<---out of com_stam...\n");
}

/**�����
*/
void stam_q(){
    while(1){
            //printf("yujulie\n");
            //printf("%d %d %d \n",ll+1,li+1,sym);
        if(stam()==-1){//���
            break;
        }
    }
    //printf("???\n");
    fprintf(gout,"line%d :this is a statement queue!\n",ll+1);
}

/**���
*/
int stam(){
    int i=0,stam_flag=0;
    if(sym==7){
        error(2,2,ll,li);
        sym=getsym();
    }
    else if(sym==6){//if,�������
        if_stam();
        fprintf(gout,"line%d :this is a statement!\n",ll);
    }
    else if(sym==8||sym==9){//while|for ѭ�����
        circle_stam();
        fprintf(gout,"line%d :this is a statement!\n",ll);
    }
    else if(sym==33){//{, '{'<�����>'}'
        sym=getsym();
        stam_q();//<�����>
        if(sym==34){//'}'
                fprintf(gout,"line%d :this is a statement!\n",ll+1);
            sym=getsym();
        }
        else error(2,1,ll,li);
    }
    else if(sym==13){//<��ʶ��>   ��ֵ���|�з���ֵ�����������|�޷���ֵ�����������
        sym=getsym();
        if(sym==31||sym==26){//'['||'='  ��ֵ����';'
            ass_stam();//���������ж�
            if(sym==28){
                fprintf(gout,"line%d :this is a statement!\n",ll+1);
                sym=getsym();
            }
            else error(2,1,ll,li);
        }
        else if(sym==29||sym==28){//'('||';' ���в���|�޲��� �����������
            stam_flag=0;
            for(i=0;i<local_index[0];i++){//��ѯȫ�ֱ���û�������ĺ���
                if(strcmp(tables_local[0].table_contents[i].ident_name,words[ll][li-1])==0&&(tables_local[0].table_contents[i].typ==7||tables_local[0].table_contents[i].typ==8)){
                    stam_flag=1;
                    res_call(tables_local[0].table_contents[i].adr);
                    if(sym==28){//;
                        fprintf(gout,"line%d :this is a statement!\n",ll+1);
                        sym=getsym();
                    }
                    else error(2,1,ll,li);
                    break;
                }
                if(strcmp(tables_local[0].table_contents[i].ident_name,words[ll][li-1])==0&&tables_local[0].table_contents[i].typ==9){//void
                    stam_flag=1;
                    nores_call(tables_local[0].table_contents[i].adr);
                    if(sym==28){//;
                        fprintf(gout,"line%d :this is a statement!\n",ll+1);
                        sym=getsym();
                    }
                    else error(2,1,ll,li);
                    break;
                }
            }
            if(stam_flag==0) error(3,5,ll,li);
        }
        else error(2,2,ll,li);
    }
    else if(sym==10){//scanf, ������';'
        read_stam();
        if(sym==28){//';'
            fprintf(gout,"line%d :this is a statement!\n",ll+1);
            sym=getsym();
        }
        else error(2,1,ll,li);
    }
    else if(sym==11){//printf, д����';'
        //printf("???\n");
        write_stam();
        //printf("!!!!!!!!???\n");
        //printf("%s\n",words[ll][li]);
        if(sym==28){//';'
            fprintf(gout,"line%d :this is a statement!\n",ll+1);
            sym=getsym();
            //printf("after writing%d\n",sym);
        }
        else error(2,1,ll,li);
    }
    else if(sym==28){//';'
        fprintf(gout,"line%d :this is a empty!\n",ll+1);
        fprintf(gout,"line%d :this is a statement!\n",ll+1);
        sym=getsym();
    }
    else if(sym==12){//return   ��������';'
        return_stam(table_No);
        if(sym==28){//';'
            fprintf(gout,"line%d :this is a statement!\n",ll+1);
            sym=getsym();
        }
        else error(2,1,ll,li);
    }
    else{
        return -1;
    }
    return 0;
}


/**�������
*/
void if_stam(){
    //sym==if
    char label_else[N];
    char label_out[N];
    sym=getsym();
    if(sym!=29) error(2,3,ll,li);
    else{//'('
        sym=getsym();
    }
    condit();//����
    if(sym!=30) error(2,3,ll,li);
    else{//')'
        strcpy(label_else,new_label());//����lab_else
        gen_mid(22,label_else,"","",table_No);
//        fprintf(midout,"BZ %s\n",label_else);
        sym=getsym();
    }
    if(stam()==0){
        strcpy(label_out,new_label());//����laebl_out
        gen_mid(11,label_out,"","",table_No);
//        fprintf(midout,"GOTO %s\n",label_out);
        gen_mid(17,label_else,"","",table_No);//����label_else
//        fprintf(midout,"%s:\n",label_else);//
        if(sym==7){//else
            sym=getsym();
            if(stam()==0){//<���>
                if(li==0){
                    fprintf(gout,"line%d :this is a if_statement!\n",ll);
                }
                else{
                    fprintf(gout,"line%d :this is a if_statement!\n",ll+1);
                }
            }
        }
        else{
           if(li==0){
                    fprintf(gout,"line%d :this is a if_statement!\n",ll);
                }
                else{
                    fprintf(gout,"line%d :this is a if_statement!\n",ll+1);
                }
        }
        gen_mid(17,label_out,"","",table_No);//����label_out
//        fprintf(midout,"%s:\n",label_out);//
    }
}

/**ѭ�����
*/
void circle_stam(){
    //sym==whlie|for
    char label_cir[N];
    char label_out[N];
    char exs[N];
    char ident_[N];
    midcode save_condi[N];
    midcode save_step;
    int pre_index;
    int condi_num;
    int i;
    int flag=0;
    int iden1_typ=0;
    if(sym==8){//while
        sym=getsym();
        if(sym!=29) error(2,3,ll,li);
        else{//'('
            sym=getsym();
            strcpy(label_cir,new_label());//����
            gen_mid(17,label_cir,"","",table_No);//����
//            fprintf(midout,"%s:\n",label_cir);
        }
        condit();//<����>
        if(sym!=30) error(2,3,ll,li);
        else{//')'
            strcpy(label_out,new_label());//����
            gen_mid(22,label_out,"","",table_No);
//            fprintf(midout,"BZ %s\n",label_out);
            sym=getsym();
        }
        stam();//���
        gen_mid(11,label_cir,"","",table_No);
//        fprintf(midout,"GOTO %s\n",label_cir);
        gen_mid(17,label_out,"","",table_No);
//        fprintf(midout,"%s:\n",label_out);
        if(li==0){
            fprintf(gout,"line%d :this is a circle!\n",ll);
        }
        else{
            fprintf(gout,"line%d :this is a circle!\n",ll+1);
        }
    }
    else if(sym==9){//for
        sym=getsym();
        if(sym!=29) error(2,3,ll,li);
        else{//'('
            sym=getsym();
        }
        if(sym!=13) error(2,2,ll,li);
        else{//<��ʶ��>
            iden1_typ=lk_table(ll,li);
            strcpy(ident_,words[ll][li]);
            fprintf(gout,"line%d :this is a ident!\n",ll+1);
            sym=getsym();
        }
        if(sym!=26) error(2,2,ll,li);
        else{//'='
            sym=getsym();
        }
        strcpy(exs,exprs());//<���ʽ>
        if((iden1_typ==1||iden1_typ==11)&&exs_typ==1){}
        else if((iden1_typ==2||iden1_typ==10)&&exs_typ==0){}
        else if(iden1_typ==3||iden1_typ==4) error(3,8,ll,li);
        else error(3,3,ll,li);
        gen_mid(1,exs,"",ident_,table_No);
//        fprintf(midout,"%s = %s\n",ident_,exs);
        if(sym!=28) error(2,1,ll,li);
        else{//';'
            sym=getsym();
        }
        pre_index=mid_index;
        condit();//<����>
        for(i=0;i<mid_index-pre_index;i++){
            save_condi[i]=midcodes[pre_index+i];//����condi
        }
        condi_num=i;//condi����
        if(sym!=28) error(2,1,ll,li);
        else{//';'
            sym=getsym();
        }
        if(sym!=13) error(2,2,ll,li);
        else{//<��ʶ��>
            if(lk_table(ll,li)==2||lk_table(ll,li)==10){}//int
            else if(lk_table(ll,li)==4) error(3,8,ll,li);//cons��ֵ
            else error(3,3,ll,li);//ƥ�����
            strcpy(ident_,words[ll][li]);
            fprintf(gout,"line%d :this is a ident!\n",ll+1);
            sym=getsym();
        }
        if(sym!=26) error(2,2,ll,li);
        else{//'='
            sym=getsym();
        }
        if(sym!=13) error(2,2,ll,li);
        else{//<��ʶ��>
            lk_table(ll,li);
            fprintf(gout,"line%d :this is a ident!\n",ll+1);
            sym=getsym();
        }
        if(sym!=17&&sym!=18) error(2,2,ll,li);
        else{//+|-
          //  printf("debug_\n");
            if(sym==17){
                flag=1;//+
            }else{
                flag=2;//-
            }
            sym=getsym();
        }
        if(sym!=16) error(2,2,ll,li);
        else{//<����>::=<�޷�������>
                //printf("debug_??\n");
            strcpy(save_step.res,ident_);
            strcpy(save_step.op1,ident_);
            strcpy(save_step.op2,words[ll][li]);
            if(flag==1){
                save_step.op = 1;
            }
            else{
                save_step.op = 2;
            }
            //printf("debug_??\n");
            save_step.adr=table_No;
            fprintf(gout,"line%d :this is a unsigned int!\n",ll+1);
            fprintf(gout,"line%d :this is a step!\n",ll+1);
            sym=getsym();
        }
        if(sym!=30) error(2,3,ll,li);
        else{//')'
              //  printf("debug_??\n");
            sym=getsym();
            mid_index=pre_index;
            strcpy(label_cir,new_label());
            gen_mid(17,label_cir,"","",table_No);
//            fprintf(midout,"%s:\n",label_cir);
        }
        stam();//<���>
        ///ȡ��save_step
        midcodes[mid_index]=save_step;
        // printf("debug_??\n");
        if(flag==1){
//            fprintf(midout,"%s = %s + %s\n", midcodes[mid_index].res, midcodes[mid_index].op1,save_step.op2);
        }
        else{
//            fprintf(midout,"%s = %s - %s\n", midcodes[mid_index].res, midcodes[mid_index].op1,save_step.op2);
        }
        //printf("debug_??\n");
        mid_index++;
        ///ȡ��save_condi
        for(i=0;i<condi_num;i++){
            midcodes[mid_index]=save_condi[i];
            mid_index++;
        }
        fprintf(gout,"line%d :this is a circle!\n",ll);
        //printf("debug_??\n");
        ///BZ label_out
        strcpy(label_out,new_label());
        gen_mid(22,label_out,"","",table_No);
//        fprintf(midout,"BZ %s\n",label_out);
        ///GOTO label_cir
        gen_mid(11,label_cir,"","",table_No);
//        fprintf(midout,"GOTO %s\n",label_cir);
        ///label_out:
        gen_mid(17,label_out,"","",table_No);
//        fprintf(midout,"%s:\n",label_out);
    }
}


/**����
*/
void condit(){
    char exs[N],exs_1[N];
    char op_[N];
    int sym_now;
    strcpy(exs,exprs());//���ʽ
    if(sym==21||sym==22||sym==23||sym==24||sym==25||sym==27){//[<��ϵ�����><���ʽ>]
        sym_now=sym;
        strcpy(op_,words[ll][li]);
        fprintf(gout,"line%d :this is a relational op!\n",ll+1);
        sym=getsym();
        strcpy(exs_1,exprs());//���ʽ]
        gen_mid(sym_now-9,exs,exs_1,"",table_No);
//        fprintf(midout,"%s %s %s\n",exs,op_,exs_1);
        fprintf(gout,"line%d :this is a condition!\n",ll+1);
    }
    else if(sym==30||sym==28){//')'||';' ˵�������ǵ�����<���ʽ>
        exs_1[0]='0';
        exs_1[1]='\0';
        gen_mid(16,exs,exs_1,"",table_No);
//        fprintf(midout,"%s == %s\n",exs,exs_1);
        fprintf(gout,"line%d :this is a condition!\n",ll+1);
    }
    else{
        error(2,2,ll,li);
    }
}


/**�з���ֵ�����������
*/
void res_call(int fuc_i){
    //symΪ��ʶ������һ��
    int have_para=0;
    char ident_[N];
    strcpy(ident_,words[ll][li-1]);
    //printf("res_call_sta\n");
    if(tables_local[fuc_i].table_contents[1].typ==10||tables_local[fuc_i].table_contents[1].typ==11){
        //˵���в���
        have_para=1;
    }
    if(sym==29){//'('
        sym=getsym();
        val_param(fuc_i);//<ֵ������>
        if(sym!=30) error(2,3,ll,li);
        else{//')'
            //printf("in_res_call%d %d %d\n",ll+1,li,exs_typ);
            if(tables_local[fuc_i].table_contents[0].typ==7) exs_typ=1;
            else if(tables_local[fuc_i].table_contents[0].typ==8) exs_typ=0;
            fprintf(gout,"line%d :this is a return call statement!\n",ll+1);
            sym=getsym();
        }
    }
    else if(have_para) error(3,6,ll,li);
    else{
        fprintf(gout,"line%d :this is a return call statement!\n",ll+1);
    }
    gen_mid(9,ident_,"",factor_nam_res,table_No);
//    fprintf(midout,"call %s\n",ident_);
    //return a;
}

/**�޷���ֵ�����������
*/
void nores_call(int n_fuc_i){
    //symΪ��ʶ������һ��
    int have_para=0;
    char ident_[N];
    strcpy(ident_,words[ll][li-1]);
    if(tables_local[n_fuc_i].table_contents[1].typ==10||tables_local[n_fuc_i].table_contents[1].typ==11){
        have_para=1;
    }
    if(sym==29){//'('
        sym=getsym();
        val_param(n_fuc_i);//<ֵ������>
        if(sym!=30) error(2,3,ll,li);
        else{//')'
            fprintf(gout,"line%d :this is a no_return call statement!\n",ll+1);
            sym=getsym();
        }
    }
    else if(have_para) error(3,6,ll,li);
    else{
        fprintf(gout,"line%d :this is a no_return call statement!\n",ll+1);
    }
//    fprintf(midout,"call %s\n",ident_);
    gen_mid(8,ident_,"","",table_No);
}


/**�ж��ַ����Ƿ�������
*/
int if_number(char s[]){
    int len,i;
    len=strlen(s);
    for(i=0;i<len;i++){
        if(s[i]=='_'||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')||s[i]=='$')
             return 0;
    }
    return 1;
}

/**��ֵ���
*/
void ass_stam(){
    //sym=='['||sym=='='
    //printf("???%s\n",words[ll][li]);
    int flag=0,ass_typ=0,ass_size=0;
    char exs[N],exs_1[N];
    char ident_[N];
    trace_words(1);
    strcpy(ident_,words[ll][li]);
    ass_typ=lk_table(ll,li);//���
    ass_size=lk_table_size(ll,li);//������ش�С
    sym=getsym();
    if(sym==31){//'['
        //printf("debug\n");
        if(ass_typ!=5&&ass_typ!=6) error(3,3,ll,li);
        sym=getsym();
        strcpy(exs,exprs());//<���ʽ>
        if(if_number(exs)){
            if(atoi(exs)<0) error(3,1,ll,li);//����Խ�½�
            if(atoi(exs)>=ass_size) error(3,2,ll,li);//����Խ�Ͻ�
        }
        if(exs_typ==1) error(3,3,ll,li);//�����±�Ϊchar
        if(sym==32){//']'
            flag=1;
            sym=getsym();
        }
    }
    if(sym==26){//'='
        //printf("???%d\n",flag);
        sym=getsym();
        strcpy(exs_1,exprs());//<���ʽ>
        //printf("???\n");
        if(flag){//��ֵ������
            if(ass_typ==5&&exs_typ==1){}
            else if(ass_typ==6&&exs_typ==0){}
            else error(3,3,ll,li);
            gen_mid(5,exs_1,exs,ident_,table_No);
//            fprintf(midout,"%s[%s] = %s\n",midcodes[mid_index-1].res,midcodes[mid_index-1].op2,midcodes[mid_index-1].op1);
        }
        else{
            //printf("debug%d %d %d\n",ll,ass_typ,exs_typ);
            if((ass_typ==1||ass_typ==11)&&exs_typ==1){}
            else if((ass_typ==2||ass_typ==10)&&exs_typ==0){}
            else if(ass_typ==3||ass_typ==4) error(3,8,ll,li);
            else error(3,3,ll,li);//��ʶ������ƥ�����
            //printf("???\n");
            gen_mid(1,exs_1,"",ident_,table_No);
//            fprintf(midout,"%s = %s\n",midcodes[mid_index-1].res,midcodes[mid_index-1].op1);
        }
        fprintf(gout,"line%d :this is a assignment statement!\n",ll+1);
        //printf("debug!%d %d %d",ll+1,li+1,sym);
    }
}

/**�����
*/
void read_stam(){
    //sym==scanf
    sym=getsym();
    if(sym!=29) error(2,3,ll,li);
    else{//'('
        sym=getsym();
    }
    if(sym!=13) error(2,2,ll,li);
    else{//<��ʶ��>
        if(lk_table(ll,li)==3||lk_table(ll,li)==4) error(3,8,ll,li);//���볣��
        gen_mid(19,words[ll][li],"","",table_No);
//        fprintf(midout,"scanf %s\n",words[ll][li]);
        fprintf(gout,"line%d :this is a ident!\n",ll+1);
        sym=getsym();
    }
    while(sym==35){//','
        sym=getsym();
        if(sym==13){//<��ʶ��>
            gen_mid(19,words[ll][li],"","",table_No);
//            fprintf(midout,"scanf %s\n",words[ll][li]);
            fprintf(gout,"line%d :this is a ident!\n",ll+1);
            sym=getsym();
        }
        else error(2,2,ll,li);
    }
    if(sym==30){//')'
        fprintf(gout,"line%d :this is a read statement!\n",ll+1);
        sym=getsym();
    }
    else error(2,3,ll,li);
}

/**д���
*/
void write_stam(){
    char exs[N];
    char str[N];
    sym=getsym();
    if(sym!=29) error(2,3,ll,li);
    else{//'('
        sym=getsym();
    }
    if(sym==15){//<�ַ���>
        fprintf(gout,"line%d :this is a string!\n",ll+1);
        //printf("???!!!???!!!???%s\n",words[ll][li]);
        //���ַ�������all_str,ָ��Ϊstr_index
        strcpy(all_str[str_index],words[ll][li]);
        strcpy(str,new_str());
        gen_mid(20,str,"","",table_No);
//        fprintf(midout,"printf %s\n",str);
        //printf("%s\n",str);
        sym=getsym();
        if(sym==35){//','
            //printf(",,,\n");
            sym=getsym();
            strcpy(exs,exprs());//<���ʽ>
            //printf("??%s %s\n",exs,words[ll][li+1]);
            gen_mid(20,exs,"","",table_No);
//            fprintf(midout,"printf %s\n",midcodes[mid_index-1].op1);
            if(sym==30){//')'
                //printf("wt\n");
                fprintf(gout,"line%d :this is a write statement!\n",ll+1);
                sym=getsym();
            }
        }
        else if(sym==30){//')'
            fprintf(gout,"line%d :this is a write statement!\n",ll+1);
            sym=getsym();
        }
        else error(2,2,ll,li);
    }
    else {
        strcpy(exs,exprs());//<���ʽ>
        gen_mid(20,exs,"","",table_No);
//        fprintf(midout,"printf %s\n",midcodes[mid_index-1].op1);
        if(sym==30){//')'
            fprintf(gout,"line%d :this is a write statement!\n",ll+1);
            sym=getsym();
        }
        else error(2,3,ll,li);
    }
}

/**�������
*/
void return_stam(int ret_i){
    //sym==return
    char exs[N];
    sym=getsym();
    //printf("return %d %d %d \n",ll+1,li+1,sym);
    if(sym==29){//'('
        sym=getsym();
        strcpy(exs,exprs());//<���ʽ>
        //printf("%d %d %s\n",ll,exs_typ,words[ll][li-1]);
        if(sym!=30) error(2,3,ll,li);
        else{//')'
            if(tables_local[ret_i].table_contents[0].typ==7&&exs_typ==1){}
            else if(tables_local[ret_i].table_contents[0].typ==8&&exs_typ==0){}
            else error(3,9,ll,li);
            have_return[ret_i]=1;
            //printf("%d\n",ret_i);
            gen_mid(10,exs,"","",table_No);
//            fprintf(midout,"ret %s\n",exs);
            fprintf(gout,"line%d :this is a return statement!\n",ll+1);
            sym=getsym();
        }
    }
    else{
        if(tables_local[ret_i].table_contents[0].typ!=9) error(3,9,ll,li);
        gen_mid(10,"","","",table_No);
//        fprintf(midout,"ret\n");
        fprintf(gout,"line%d :this is a return statement!\n",ll+1);
    }
}

/**������
*/
void main_fuc(){
    //�����ʱ��sym=main
//    fprintf(midout,"void main()\n");
    fill_table1(words[ll][li],9,0);
    sym=getsym();
    if(sym!=29) error(2,3,ll,li);//'('
    else sym=getsym();
    if(sym!=30) error(2,3,ll,li);//')'
    else sym=getsym();
    if(sym!=33) error(2,5,ll,li);//'{'
    else{
        sym=getsym();
        com_stam();
        if(sym==34){//'}'
            fprintf(gout,"line%d :this is a main function!\n",ll+1);
        }
    }
}

/**-------------------------------------------�ķ��������-----------------------------------------------**/

/**������
*/
void error(int error_typ,int error_No,int er_ll,int er_li){
    if_error=1;
    if(error_typ==1){ //�ʷ�����
        //fprintf(gout,"cifa_error_%d\n",error_No);
        printf("line%d_%d :cifa_error_%s--%c\n",er_ll+1,er_li+1,error1[error_No-1],a[er_ll][er_li]);
    }
    else if(error_typ==2){ //�﷨����
        //fprintf(gout,"grammer_error_%d\n",error_No);
        printf("line%d_%d :grammer_error_%s--%s\n",er_ll+1,er_li+1,error2[error_No-1],words[er_ll][er_li]);
    }
    else if(error_typ==3){ //�������
        //fprintf(gout,"meaning_error_%d\n",error_No);
        printf("line%d_%d :meaning_error_%s--%s\n",er_ll+1,er_li+1,error3[error_No-1],words[er_ll][er_li]);
    }
}

int main(){
    int i;
    scanf("%s",code_name);//����Դ������
    //strcpy(code_name,"C:\\Users\\lenovo\\Desktop\\16061092_test.txt");  //16061092_test.txt
    _getsym(); //�ʷ�����
    grammer(); //�﷨����
    if(if_error) return 0;
    print_table();//���Ǳ����
    print_midcode();//���Ǳ����
    opti();
    opti_print_midcode();
    gen_midvar_num();
    gen_aim();//����Ŀ�����
    opti_gen_aim();//�����Ż���Ŀ�����
    for(i=1;i<=table_No;i++){
//        printf("ss%d %s %d %d\n",i,tables_local[i].table_contents[0].ident_name,func_mid_var[i],jishu[i]);
    }
    return 0;
}
