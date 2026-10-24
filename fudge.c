#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fileClose(FILE* fptrCompiled,FILE* fptrTarget){
    fclose(fptrCompiled);
    fclose(fptrTarget);
}

int main(int argc,char** argv){
    if(argc<2||argc>3){ // Initial error checks
        printf("\nInvalid arguments!\nUsage: ./bfCompiler.exe (.bf/.txt target file) (flag)\nUse -a as flag to assemble after compilation.\n\n");
        return 1;
    }
    FILE* fptrTarget=fopen(argv[1],"r");
    if(fptrTarget==NULL){
        printf("\nCould not open '%s'. Ensure the target path is correct and that the target has proper access.\n\n",argv[1]);
        return 1;
    }

    char newPath[sizeof(argv[1])]; // .asm path generation
    strcpy(newPath,argv[1]);
    newPath[sizeof(argv[1])-3]='\0';
    strcat(newPath,".asm");

    FILE* fptrCompiled=fopen(newPath,"w");
    if(fptrCompiled==NULL){
        printf("\nAssembly file could not be created!\n\n");
        return 1;
    }
    fprintf(fptrCompiled,"bits 64\ndefault rel\nglobal main:\nextern exit\nextern printf\n"); // Define main function and external functions
    fprintf(fptrCompiled,"section .text\nmain:\nsub rsp, 40\nxor bl, bl\nxor rsi, rsi\nmov bl, [reel+rsi]\n"); // Begin main

    int buffer;
    long readIndex=0;
    int reelIndex=0;
    int loopDepth=0;

    // BEGIN COMPILATION

    while(buffer=fgetc(fptrTarget),buffer!=EOF){
        switch(buffer){
            case '+':
                fprintf(fptrCompiled,"inc byte[reel+rsi]\n");
                break;
            case '>':
                reelIndex++;
                if(reelIndex>29999){
                    printf("SYNTAX ERROR at character %c at index %lu: Reel pointer out of bounds (0-29999",buffer,readIndex);
                    fileClose(fptrCompiled,fptrTarget);
                    return 1;
                }
                fprintf(fptrCompiled,"inc rsi\nmov bl, [reel+rsi]\n");
                break;
            case '<':
                reelIndex--;
                if(reelIndex<0){
                    printf("SYNTAX ERROR at character %c at index %lu: Reel pointer out of bounds (0-29999",buffer,readIndex);
                    fileClose(fptrCompiled,fptrTarget);
                    return 1;
                }
                fprintf(fptrCompiled,"dec rsi\nmov bl, [reel+rsi]\n");
                break;
            case '-':
                fprintf(fptrCompiled,"dec byte[reel+rsi]\n");
                break;
            case '.':
                fprintf(fptrCompiled,"mov rbp, rsp\nlea rcx, fmt\nmov rdx, [reel+rsi]\nxor eax, eax\nsub rsp, 32\ncall printf\nadd rsp, 32\nmov rsp, rbp\n");
                break;
            case '[':
                fprintf(fptrCompiled,"loop%d:\nmov bl, [reel+rsi]\ncmp bl,0\njz endLoop%d\n",loopDepth,loopDepth);

                break;
            case ']':
                //loopDepth--;
                fprintf(fptrCompiled,"mov bl, [reel+rsi]\ncmp bl,0\njnz loop%d\nendLoop%d:\n",loopDepth,loopDepth);
                loopDepth++;
            default:
                break;
        }
        readIndex++;
    }
    fprintf(fptrCompiled,"xor ecx, ecx\ncall exit\n");
    fprintf(fptrCompiled,"section .data\nreel: times 30000 db 0\nfmt: db \"%%c\",0\n"); // Initialize data reel
    fileClose(fptrCompiled,fptrTarget);

    printf("\nCompilation of %s complete!\n\n",argv[1]);

    return 0;
}
