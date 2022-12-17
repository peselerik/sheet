# Sheet
Projekt neni kompletne dokoncen, nektere funkce chybi.  
Program se snazi napodobit fungovani excelu.

## Preklad programu

Program se preklada prikazem "make" nebo s temito argumenty:

$ gcc -std=c99 -Wall -Wextra -Werror sheet.c -o sheet

## Spousteni programu
$ ./sheet -d : PRIKAZ [ARG] <[FILENAME]

- "-d :" je nastaveni delice sloupcu 
- PRIKAZ je nazev prikazu z tabulky nize
- ARG je argument v podobe radku nebo sloupce (pripadne vice hodnot) pro danou funkci.
- Filename je nazev souboru pro otevreni

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

## Priklady spusteni

$ ./sheet -d : move 2 5 <in.txt  
$ ./sheet -d : icol 3 <in.txt  
$ ./sheet -d : arow <in.txt  
$ ./sheet -d : drows 3 6 <in.txt

## Priklad spusteni a vystupu
$ cat in.txt  
1:2:3:4:5:6  
2:3:4:5:6:7  
a:B:C:D:e:f  
f:G:h:I:j:K  
auto:pes:kocka:123:4+2:ooo  
ccc:d2d:ari:l:****:XXXXX  
AAAA:BBBB:cccc:dddd:EEEE:ffff  

$ ./sheet -d : move 2 5 <in.txt  
1:3:4:5:2:6  
2:4:5:6:3:7  
a:C:D:e:B:f  
f:h:I:j:G:K  
auto:kocka:123:4+2:pes:ooo  
ccc:ari:l:****:d2d:XXXXX  
AAAA:cccc:dddd:EEEE:BBBB:ffff
