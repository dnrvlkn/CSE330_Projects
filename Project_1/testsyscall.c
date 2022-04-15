#include <unistd.h>
#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>

int main(){



    long int amma = syscall(548);

    printf("System call my_syscall returned %ld\n", amma);

    return 0;
}