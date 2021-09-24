
SortedListDr: SortedListDr.o SortedList.o Student.o
	g++ -o driver SortedListDr.o SortedList.o Student.o

SortedListDr.o: SortedListDr.cpp
	g++ -c SortedListDr.cpp

SortedList.o: SortedList.cpp SortedList.h
	g++ -c SortedList.cpp

Student.o: Student.cpp Student.h
	g++ -c Student.cpp

run: SortedListDr
	./driver

clean:
	rm -f *.o
	rm -f *~
	rm -f driver
	rm outFile.txt
	rm soutFile.txt
