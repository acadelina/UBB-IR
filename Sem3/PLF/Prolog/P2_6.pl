
adaugaX(L,[],L).
adaugaX(L,[H|T],[H|R]):-
    adaugaX(L,T,R).

%inlocuieste(L:list,E:int,X:list,R:list)
%(i,i,i,o)

inlocuieste([],_,_,[]).
inlocuieste([H|T],E,X,[H|R]):-
    H=\=E,
    inlocuieste(T,E,X,R).
inlocuieste([H|T],E,X,R):-
    H=:=E,
    inlocuieste(T,E,X,R1),
    adaugaX(R1,X,R).

