/*

     PCBoard to DayDream filelist converter (daydream longnames).

    (only works on The Cleaner outputted "WIPEOUT" mode pcb lists!).
             get The Cleaner from www.nekromantix.com/pmc

 */
#include <stdio.h>
#include <string.h>
#include <time.h>

FILE *pcb_list;
FILE *dd_list;

char line[200];
char filename[200];
char filesize[200];
char buffah[200];

time_t currtime;

/* reader :) */
int Reader()
{
	char *pmcptr;

	strcpy(buffah, "");
	*line = 0;

	fgets(line, 200, pcb_list);
	if (feof(pcb_list))
	{
		printf("end of pcboard filelist, lets call it quit.\n");
		return 0;
	}

	pmcptr = line;

	Do_Tokenizer();

	currtime = time(0); /* get time for the thing */

	sprintf(buffah, "%-35sP--- %7s %s", filename, filesize, ctime(&currtime));
	fputs(buffah, dd_list);

	strcpy(buffah, "                                   ");
	strcat(buffah, pmcptr + 33);
	fputs(buffah, dd_list);

	return 0;
}

int Do_Tokenizer()
{
	char *p;
	char temp1[200];

	*filename = 0;
	*filesize = 0;
	*p = 0;

	strcpy(temp1, line);
	p = strtok(temp1, " ");
	strcpy(filename, p);

	p = strtok(NULL, " ");
	strcpy(filesize, p);

	return 0;
}

int main()
{
	printf("\nProcessing...\n");

	pcb_list = fopen("directory.pcb", "rt");
	if (!pcb_list)
	{
		printf("error! no directory.pcb file in this dir\n");
		exit(1);
	}

	dd_list = fopen("daydream.dir", "wt");
	if (!dd_list)
	{
		printf("error writing directory.new.daydream file!\n");
		exit(1);
	}

	fgets(line, 200, pcb_list);
	fgets(line, 200, pcb_list);                     /* header */

	while (!feof(pcb_list))
		Reader();

	printf("Thanks for using pcbfilelist to daydreamfilelist.\n");

	fclose(pcb_list);
	printf("closed pcb_list\n");
	fclose(dd_list);
	printf("closed dd_list\n");

	return 0;
}