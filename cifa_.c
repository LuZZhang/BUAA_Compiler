#include<stdio.h>
#include<string.h>
#define N 80
#define MAX_NUM 80000
char word[5][10]={"begin","end","if","then","else"};
void dectobin(int n) {
if(n>1) dectobin(n/2);
printf("%d",n%2); /*�����������ֵ*/
}
int getsym(char a[],int length){
	int i=0,j=0,n=0,m=0,temp=0;
	char b[N];
	if(a[i]!='\0')
	{
	    // ������ĸ
		if(a[i]>=65&&a[i]<=122)
		{
			j=0;
			while((a[i]>=65&&a[i]<=122)||(a[i]>='0'&&a[i]<='9')||a[i]=='_')
			{
				b[j]=a[i];
				j++;
				i++;
			}
			if(a[i]!='\0'){
				return 0;
			}
			i--;
			b[j]='\0';
			for(n=0;n<5;n++)
			{
				if(strcmp(b,word[n])==0)
				{
					printf("<�ؼ���,%d",n+1);
					while(word[n][m]!='\0')
					{
					//	printf("%c",word[n][m]);
						m++;
					}
					printf(">\n");
					temp=1;
					return n+1;
				}
			}
			if(temp==0)
			printf("<��ʶ��,20,%s>\n",b);
			return 20;
		}
		//��������
		else if(a[i]>='0'&&a[i]<='9'){
			j=0;
			while(a[i]>='0'&&a[i]<='9')
			{
				b[j]=a[i];
				j++;
				i++;
			}
			if(a[i]!='\0'){
				return 0;
			}
			printf("<������,21,");
			dectobin(atoi(b));
			printf(">\n");
			return 21;
		}
		//����˫�ַ��ֽ��
		else if(a[i]==':'){
			j=0;
			while(a[i]=='='||a[i]==':'){
				b[j]=a[i];
				j++;
				i++;
			}
			if(a[i]!='\0'||i>2||a[1]==':'){
				return 0;
			}
			if(i==1){
				printf("<:,30>\n");
				return 30;
			}
			else{
				printf("<:=,31>\n");
				return 31;
			}
		}
		else if(a[i]=='/'){
			//j=0;
			b[0]='/';
			j=1;
			i=1;
			if(a[i]=='*'){
				//����ע��
				if(a[length-2]=='*'&&a[length-1]=='/'){
					printf("ע��\n");
					return 33;
				}
				else{
					return 0;
				}
			}
			else if(a[i]=='\0'){
				printf("</��25>\n");
				return 25;
			}
			else{
				return 0;
			}
		}
		//�����������ַ��ֽ��
		else
		{
			if(length!=1) return 0;
			switch(a[i])
			{
				case '+': printf("<+,22>\n");return 22;break;
				case '-': printf("<-,23>\n");return 23;break;
				case '*': printf("<*,24>\n");return 24;break;
				case '(': printf("<(,26>\n");return 26;break;
				case ')': printf("<),27>\n");return 27;break;
				case ',': printf("<,,28>\n");return 28;break;
				case ';': printf("<;,29>\n");return 29;break;
				case '=': printf("<=,32>\n");return 32;break;
				default: return 0;
			}
		}
		i++;
	}
}

int main(){
	char a[N];
	char c;
	char code[MAX_NUM];//�����������
	int i=0;
    int sym=0;//������
    int code_length = 0;//�����ܳ���
    FILE *in = fopen("C:\\Users\\lenovo\\Desktop\\code.txt","r");
	//FILE *out = fopen("C:\Users\lenovo\Desktop\fcopyout.txt","w");
	c=fgetc(in);
	while(c!=EOF){
        code[code_length] = c;
        c = fgetc(in);
        code_length++;
	}

	sym=getsym(code,code_length);
	if(sym==0){
		printf("ERROR");
	}

	fclose(in);
    //fclose(out);
	return 0;

}
