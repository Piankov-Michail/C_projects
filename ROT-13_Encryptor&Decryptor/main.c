#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define SIZE 256
#define HELP_MSG "Put flags\nHelp: -h\nEncrypt: -e\n"

void PrintHelp()
{
    printf("%s", HELP_MSG);
}

void PushBack(char* str, char c, int* length, int* size_count)
{
    if(*length >= *size_count * SIZE * sizeof(char))
    {
        *size_count +=1;
        str = realloc(str, *size_count * SIZE * sizeof(char));
    }
    str[*length] = c;
    *length += 1;
}

char* TextInput(int* length, int* size_count)
{
    char* str = malloc(SIZE*sizeof(char));
    char c;
    do
    {
        c = getchar();
        if(c == '\n')
        break;
        PushBack(str, c, length, size_count);

    }while(1);
    PushBack(str, '\0', length, size_count);
    return str;
}

char* Encrypting()
{
    int length = 0;
    int size_count = 1;
    char* str = TextInput(&length, &size_count);
    for(int i = 0; i < length; i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
        str[i] = 'a' + ((str[i] - 'a' + 13) % ('z' - 'a' + 1));
        else if (str[i] >= 'A' && str[i] <= 'Z')
        str[i] = 'A' + ((str[i] - 'A' + 13) % ('Z' - 'A' + 1));
    }
    return str;
}

int main(int argc,char**  argv)
{
    char* opts ="he";
    int opt = getopt(argc, argv, opts);
    switch(opt)
    {
        case 'h':
            PrintHelp();
            break;
        case 'e':
            printf("%s", Encrypting());
            break;
    }
    return 0;
}