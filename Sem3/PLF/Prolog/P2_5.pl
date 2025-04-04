%maxim(L:lista,R:int)
%(i,o)
maxim([A],A).
maxim([H|T],R):-
    maxim(T,R1),
    H>R1,
    R is H.
maxim([H|T],R):-
    maxim(T,R1),
    R1>=H,
    R is R1.

%pozitiimax(L:list,R:list)
%(i,o)

pozitiimax([],_,_,[]).
pozitiimax([H|T],P,M,[P|R]):-
    H=:=M,
    P1 is P+1,
    pozitiimax(T,P1,M,R).
pozitiimax([H|T],P,M,R):-
    H=\=M,
    P1 is P+1,
    pozitiimax(T,P1,M,R).

poz(L,R):-
    maxim(L,E),
    pozitiimax(L,0,E,R).

