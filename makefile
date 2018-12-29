CC=gcc -Wall -Werror -std=gnu99

all: courseFinale.o utilitaire.o voiture.o entrainement.o qualification.o course.o
	$(CC) -o courseFinale courseFinale.o utilitaire.o voiture.o entrainement.o qualification.o course.o

courseFinale.o: courseFinale.c
	$(CC) -c courseFinale.c

entrainement.o: entrainement.c
	$(CC) -c entrainement.c

qualification.o: qualification.c
	$(CC) -c qualification.c
course.o: course.c
	$(CC) -c course.c

utilitaire.o: utilitaire.c
	$(CC) -c utilitaire.c

voiture.o: voiture.c
	$(CC) -c voiture.c

tex: rapportOS.tex
	pdflatex rapportOS.tex

clean:
	rm -f *.o manageTime voiture utilitaire main *.gch rapportOS.out rapportOS.aux rapportOS.log rapportOS.toc *.txt courseFinale
