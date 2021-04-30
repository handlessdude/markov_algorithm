# markov_algorithm
[tip: it is highly recommended to not launch .exe file in folder the path of which contains cyrillic symbols.]

EXAMPLE OF PROGRAM WORKING LOOP OUTPUT:

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): y
Enable saving output in file? (y = yes, no = any other key): y
Enter filename: test1.txt

Please enter your rules in format "P->Q" or "P->.Q" if rule is final:
[input empty string to finish]
[if it's needed to enter empty word as a side of the rule just enter nothing there]

1)a->b

2)

Enter the string to process:
aaa

String process started.

1) Found applicable rule: 1)a->b
String after applying: baa

2) Found applicable rule: 1)a->b
String after applying: bba

3) Found applicable rule: 1)a->b
String after applying: bbb

4) No applicable rule found.


Processed string:
bbb

Another one? (y = yes, no = any other key): y

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): n
Enable saving output in file? (y = yes, no = any other key): y
Enter filename: test1.txt
File already exists in the current folder. Choose another name: test2.txt
Enter new rules? (y = yes, no = any other key): n

Enter the string to process:
aaa

Processed string:
bbb

Another one? (y = yes, no = any other key): n

 =========== PROCESS FINISHED ===========
