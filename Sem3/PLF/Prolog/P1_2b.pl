%adauga(L:list,v:int,p:int,c:int,R:list)
%(i,i,i,i,o)

adauga([],_,_,_,[]).
adauga([H|T],E,P,C,[H|R]):-
    P<C,
    P1 is P+1,
    adauga(T,E,P1,C,R).
adauga([H|T],E,P,C,[H,E|R]):-
    P=:=C,
    P1 is P+1,
    C1 is C*2,
    adauga(T,E,P1,C1,R).


adauga_final(L,V,R):-
    adauga(L,V,0,1,R1),
    R = R1.
