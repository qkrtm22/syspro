#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[])
{
	int fd, id;
	struct student record;

	if (argc < 2) {
		fprintf(stderr, "How to use : %s File \n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	while(1) {
	id = 0;
	int flag;
	printf("0: list of all book, 1: list of available books ) ");
	scanf("%d", &flag);

	printf("%3s %10s %10s %6s %13s %7s \n", "id", "bookname", "author", "year", "numofborrow", "    borrow");

		while (id++ < 4) {
			lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
			if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
				if (flag == 0) {
				printf("%3d %10s %10s %6d %13d %7s \n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow)?"True":"False" );
				}else if (record.borrow == 1) {
				printf("%3d %10s %10s %6d %13d %7s \n", record.id, record.bookname, record.author, record.year, record.numofborrow, (record.borrow)?"True":"False" );
				}
			}
		}
	printf("\n");
	}
	close(fd);
	exit(0);
}
