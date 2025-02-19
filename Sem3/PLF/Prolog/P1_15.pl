%nrpar(L:list)
%(i)

nrpar([]).
nrpar([_,_|T]):-
    nrpar(T).

minim([H],H).
minim([H|T],R):-
    minim(T,R1),
    R1<H,
    R is R1.
minim([H|T],R):-
    minim(T,R1),
    R1>=H,
    R is H.

eliminam([],_,[]).
eliminam([H|T],E,R):-
    H=:=E,
    eliminam(T,E,R).
eliminam([H|T],E,[H|R]):-
    H=\=E,
    eliminam(T,E,R).

eliminamin(L,Rez):-
    minim(L,R),
    eliminam(L,R,Rez).
