%interclasare(L:list,P:int,E:int,R:list)
%(i,i,i,o)

interclasare([],_,_,[]).
interclasare([H|L],P,E,[H|R]):-
    P=\=1,
    P1 is P-1,
    interclasare(L,P1,E,R).
interclasare([H|L],P,E,[H,E|R]):-
    P=:=1,
    P1 is P-1,
    interclasare(L,P1,E,R).

