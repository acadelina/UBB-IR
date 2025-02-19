%elimina(L:list,p:int,curent:int,R:list)
%(i,i,i,o)


elimina([],_,_,[]).
elimina([H|T],P,C,[H|R]):-
    P=\=C,
    C1 is C+1,
    elimina(T,P,C1,R).
elimina([_|T],P,C,R):-
    P=:=C,
    C1 is C+1,
    elimina(T,P,C1,R).

eliminaf(L,P,R):-
    elimina(L,P,0,R).

