// Nathan Crossdale 

#include<stdio.h>
#include <string.h>

long findfilesize(const char * filepath){
    FILE*file = fopen(filepath, "rb");
    if (!file) {
    return -1;
}

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    return filesize;
}

int main (int arc, char*arv[]){

    if (arc != 3){
        printf("usage: %s <InputFile> <OutputFile>\n ", arv[0]);
        return 1;
    }

    const char *InputFile = arv[1];
    const char *OutputFile = arv[2];

    long original_size = findfilesize(InputFile);
    if (original_size == -1){
        printf("Cannot get the correct size of the file.\n");
        return 1;
    }
        printf("Original size: %ld bytes\n", original_size);

    FILE *readfile = fopen(InputFile, "rb");
    FILE *comfile = fopen(OutputFile, "wb");

    if (!readfile){
        printf("Input file cannot Open!\n");
        return 1;
    }

    if (!comfile){
        printf("Cannot open output file!\n");
        fclose(readfile);
        return 1;
    }

    char current_char, previous_char;
    int count = 0;

    previous_char = fgetc(readfile);
    if (previous_char == EOF) {
        printf("Input file is empty!\n");
        fclose(readfile);
        fclose(comfile);
        return 1;
    }
    count = 1;

    int is_first_char = 1;

while ((current_char = fgetc(readfile)) != EOF) {
    if (is_first_char) {
        previous_char = current_char;
        count = 1;
        is_first_char = 0;
    } else if (previous_char == current_char) {
        count++;
    } else {
      
        fprintf(comfile, "%c%d", previous_char, count);
        previous_char = current_char;
        count = 1;  
    }
}

fprintf(comfile, "%c%d", previous_char, count);
 
    fclose(readfile);
    fclose(comfile);

    long compressed_size = findfilesize(OutputFile);
    if (compressed_size == -1) {
        printf("Error getting size of the compressed file!\n");
        return 1;
    } else {
        printf("Compressed file size: %ld bytes\n", compressed_size);
    }

   
    printf("Compression complete!! Average file size 744.25\n");

    return 0;
}

/*
Average file size reduction is
double averagesize = (166+1810+737+937 )/4  = 744.25 
printf("Compression complete!! Average file size :  %.2f\n", average_size ");
e compressor’s invocation:./620161244  ubuntu.txt ubuntucompressed.txt
*/