# Sheet

## Preklad programu

Program se preklada prikazem "make" nebo s temito argumenty:

gcc -std=c99 -Wall -Wextra -Werror sheet.c -o sheet

## Spousteni programu
./sheet PRIKAZ [ARG]

- PRIKAZ je nazev prikazu z tabulky nize
- ARG je argument v podobe radku nebo sloupce (pripadne vice hodnot) pro danou funkci.

## Prikazy pro praci s programem, kde X a Y jsou argumenty programu:

- arow - vlozi prazdny radek na konec souboru  
- irow X - vlozi prazdny radek pred radek X  
- drow X - smaze radek X  
- drows X Y - smaze radky od X po Y  

- acol - vlozi prazdny sloupec za posledni sloupec  
- icol X - vlozi prazdny sloupec pred sloupec X  
- dcol X - smaze sloupec X  
- dcols X Y - smaze sloupce od X po Y  

- cset X - preformatuje sloupec X na format string  
- tolower X - preformatuje sloupec X na lowercase text  
- toupper X - preformatuje sloupec X na uppercase text  
- round X - zaokrouhli cisla ve sloupci X  
- int X - preformatuje sloupec X na format int  
- copy X Y - zkopiruje sloupec X na misto sloupce Y  
- swap X Y - prohodi hodnoty ze sloupce X do sloupce Y  
- move X Y - vlozi sloupec X na místo sloupce Y, pricemz sloupcum zustane jejich posloupnost  

### Priklad spusteni
