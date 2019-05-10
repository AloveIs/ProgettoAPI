//
// Created by SysAdmin on 07/05/2019.
//

#include<stdio.h>
int main(){
   char temp[256];
   if(fgets(temp, 100, stdin) == NULL)
       return 0;
   else
       printf("success!!!");
   return 0;
}
