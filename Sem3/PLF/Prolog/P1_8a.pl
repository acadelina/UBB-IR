elimina([],_,_,[]).
elimina([H|T],E,C,[H|R]):-
    C>3,
    !,
    elimina(T,E,C,R).
elimina([H|T],E,C,[H|R]):-
    E=\=H,
    elimina(T,E,C,R).
elimina([H|T],E,C,R):-
    C=<3,
    E=:=H,
    C1 is C+1,
    elimina(T,E,C1,R).

exista2([H|_],A):-
    H=:=A.
exista2([H|T],A):-
    H=\=A,
    exista2(T,A).

multime([]).
multime([H|T]):-
    \+exista2(T,H).
multime([H|T]):-
    exista2%%(T,H),
    multime(T).

