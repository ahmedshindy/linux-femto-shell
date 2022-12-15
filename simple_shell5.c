#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


typedef struct shell_variables{
	int key;
	char name[30];
	char value[50];
}shell_var_t;

shell_var_t shell_vars_list[10];
int shell_vars_count=0;
char buf[100];			// assume input will not exceed 99 chars
char* Arr_ch_ptr[10];	// only 10 arguments allowed, filled with null by default, better design is to use dynamic memory allocation
char cmd[20];

void replace_buf_tabs_with_spaces(int str_size);
char is_shell_var(int buf_len);
void replace_equal_sign_with_space(int buf_len);
int encode_name(char* val);
int main ()
{
	while(1)
	{
		printf("Ana AS-Shell# ");
		fgets(buf, 100, stdin);
		int len =strlen(buf);
		if(len > 0)
			buf[len-1]='\0';

		// len without \n
		len = strlen(buf);
		if(len==0)
			continue;

		replace_buf_tabs_with_spaces(len);	// ignor tabs from input buffer
		
		
		if(is_shell_var(len))
		{
			if(shell_vars_count >= 9){
				continue;	// validate variables count
			}


			replace_equal_sign_with_space(len);
			char *token_Ptr = strtok(buf," "); 
			char var_name[20];
			char var_value[50];

			strcpy(var_name,token_Ptr);
			token_Ptr = strtok(NULL," ");
			strcpy(var_value,token_Ptr);


			int xkey =encode_name(var_name);
			// printf("variable name is %s \n",name);
			// printf("key = : %d \n",key);
			// return 0;

			char key_exist=0;
			for(int i=0 ; i< shell_vars_count ; i++ )
			{
				if(xkey == shell_vars_list[i].key)
				{
					strcpy(shell_vars_list[i].value ,var_value);
					strcpy(shell_vars_list[i].name ,var_name);	// un neccesarry
					shell_vars_count++;
					key_exist =0xff;
					break;
				}
			}
			if(key_exist ==0 )
			{
				shell_vars_list[shell_vars_count].key = xkey;
				strcpy(shell_vars_list[shell_vars_count].value ,var_value);
				strcpy(shell_vars_list[shell_vars_count].name ,var_name);
				shell_vars_count++;
			}

		continue;
		}

		char *tokenPtr = strtok(buf," "); // begin tokenizing sentence
		strcpy(cmd,tokenPtr);
		fflush(stdout);

		if( ! strcmp(cmd, "set"))
		{
			for(int i=0 ; i< shell_vars_count; i++)
			{
				printf("shell_vars_list[%d]: %s = %s \n",i, shell_vars_list[i].name, shell_vars_list[i].value);
			}
			continue;
		}

		// tokenPtr = strtok(NULL, " "); 
		int counter =0;
		while (tokenPtr != NULL)
		{
			Arr_ch_ptr[counter]=tokenPtr;
			tokenPtr = strtok(NULL, " ");
			counter++; 
		}

		if( ! strcmp(cmd, "export"))
		{
			char env_var_name[20] ;
			strcpy(env_var_name,Arr_ch_ptr[1]);
			Arr_ch_ptr[1]= NULL;
			int var_key = encode_name(env_var_name);
			int index=0;
			char var_exists=0x00;
			for(int i=0 ; i< shell_vars_count; i++)
			{
				if(var_key == shell_vars_list[i].key)
				{
					index=i;
					var_exists=0xff;
					break;
				}
			}
			if(var_exists)
			{
				printf("going to set: %s = %s \n",shell_vars_list[index].name , shell_vars_list[index].value);
		       int ret_setenv = setenv( (char*)(shell_vars_list[index].name) , (char*)(shell_vars_list[index].value), 1);
			   	if(!ret_setenv)
					printf("environment variable set\n");
			}
			else{
				printf("Local variable dones not exist\n");
			}
			continue;
		}

		int ret_pid = fork();
		if(ret_pid < 0 )
			printf("Fork failiure\n");

		else if (ret_pid > 0 ){
			int status ;
			wait(&status);
			}
			else if(ret_pid ==0) {
				sleep(1);
				execvp(cmd, Arr_ch_ptr);
				printf("Exec failed \n");
				return -1;
			}
	}

    return 0;
}

void replace_buf_tabs_with_spaces(int str_size)
{
	for(int i=0; i<str_size; i++)
	{
		if(buf[i] == '\t')
			buf[i]=' ';

		if(buf[i] == '\n')
			buf[i]='\0';
	}
}
void replace_equal_sign_with_space(int buf_len)
{
	for(int i=0; i<buf_len; i++)
	{
		if(buf[i] == '=')
			buf[i]=' ';
	}
}
char is_shell_var(int buf_len)
{
	for(int i=0; i<buf_len; i++)
	{
	if(buf[i] == '=')
		return 0xff;
	}
	return 0x00;
}

int encode_name(char* val)
{
	int size=strlen(val);
	int sum=0;
	for(int i=0; i< size ; i++)
		sum+= val[i];
	return sum;
}
