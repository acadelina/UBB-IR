%substituie(L:list,e:int,P:list,R:list)
%(i,i,i,o)

substituie([],_,_,[]).
substituie([H|T],E,L,[H|R]):-
    H=\=E,
    substituie(T,E,L,R).
substituie([H|T],E,L,[L|R]):-
    H=:=E,
    substituie(T,E,L,R).
