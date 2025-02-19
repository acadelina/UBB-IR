%pereche(L:list,E:elem,R:list)
%(i,i,o)

pereche([],_,[]).
pereche([H|T],A,[[A,H]|R]):-
    pereche(T,A,R).

adauga([],R,R).
adauga([H|T],R,[H|Rez]):-
    adauga(T,R,Rez).

perechi([],[]).
perechi([_],[]):-
    !.
perechi([H|T],R):-
    pereche(T,H,R1),
    perechi(T,R2),
    adauga(R1,R2,R).

