/*
 *  Copyright (c) 2012, Rodrigo OSORIO (ros) 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of  nor the names of its contributors may be used to 
 *    endorse or promote products derived from this software without specific 
 *    prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE. 
 */

#include <stdio.h>

int freadline(FILE * fd,char * buffer,int size)
{
    char * sz =  buffer;
    while(fread((void *)sz,1,1,fd) && sz[0] != '\n' && (buffer-sz) < size )
        sz++;
    sz[0] = 0;
    return (sz - buffer);
}

char * COLOR_BLACK = "\033[;1;30m";
char * COLOR_RED   = "\033[;1;31m";
char * NOCOLOR     = "\033[0m";

char * getcolor(int res)
{
    if(res == 0) return COLOR_BLACK;
    else return COLOR_RED;
}

void read_stats()
{
    char buffer[1024];
    int cpu[40][10][3]; 
    int count,count_other,lines;
    FILE * fd = fopen("/proc/stat","rb");
    count = 2;
    count_other = 1;
    while(1){
    	printf("%6s\t%9s\t%9s\t%9s\t%9s\t%9s\t%9s\t%9s\t%9s\t%9s\n","cpu","user","nice","system","idle","iowait","irq","softirq","steal","guest");
        lines=0;
		freadline(fd,buffer,1024);
        while(freadline(fd,buffer,1024) != 0)
        {
            if( sscanf(buffer,"cpu%d %d %d %d %d %d %d %d %d %d",
            &cpu[lines][0][count],
            &cpu[lines][1][count],
            &cpu[lines][2][count],
            &cpu[lines][3][count],
            &cpu[lines][4][count],
            &cpu[lines][5][count],
            &cpu[lines][6][count],
            &cpu[lines][7][count],
            &cpu[lines][8][count],
            &cpu[lines][9][count]) == 10){
                printf("CPU%03d\t%s%9d%s\t%s%9d%s\t%s%9d%s\t%s%9d%s\t%s%9d%s\t%s%9d%s\t%s%9d%s\t%s%9d%s\t%s%9d%s\n",
                cpu[lines][0][count],
                getcolor(cpu[lines][1][count]-cpu[lines][1][count_other]),cpu[lines][1][count]-cpu[lines][1][2],NOCOLOR,
                getcolor(cpu[lines][2][count]-cpu[lines][2][count_other]),cpu[lines][2][count]-cpu[lines][2][2],NOCOLOR,
                getcolor(cpu[lines][3][count]-cpu[lines][3][count_other]),cpu[lines][3][count]-cpu[lines][3][2],NOCOLOR,
                getcolor(cpu[lines][4][count]-cpu[lines][4][count_other]),cpu[lines][4][count]-cpu[lines][4][2],NOCOLOR,
                getcolor(cpu[lines][5][count]-cpu[lines][5][count_other]),cpu[lines][5][count]-cpu[lines][5][2],NOCOLOR,
                getcolor(cpu[lines][6][count]-cpu[lines][6][count_other]),cpu[lines][6][count]-cpu[lines][6][2],NOCOLOR,
                getcolor(cpu[lines][7][count]-cpu[lines][7][count_other]),cpu[lines][7][count]-cpu[lines][7][2],NOCOLOR,
                getcolor(cpu[lines][8][count]-cpu[lines][8][count_other]),cpu[lines][8][count]-cpu[lines][8][2],NOCOLOR,
                getcolor(cpu[lines][9][count]-cpu[lines][9][count_other]),cpu[lines][9][count]-cpu[lines][9][2],NOCOLOR
                );
                lines++;
            }
            
        }
        printf("\033[0m\033[%dA",lines+1);
        sleep(1);
        rewind(fd);
        count_other = count;
        count = (count + 1 ) % 2 ;
    }

    fclose(fd);

}

int main()
{
   read_stats(); 
}

