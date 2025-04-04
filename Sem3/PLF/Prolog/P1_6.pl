sterge([],_,[]).
sterge([H|T],E,R):-
    E=:=H,
    sterge(T,E,R).
sterge([H|T],E,[H|R]):-
    E=\=H,
    sterge(T,E,R).

apartine([H|_],E):-
    H=:=E.
apartine([H|T],E):-
    H=\=E,
    apartine(T,E).


elimina([],[]).
elimina([H|T],R):-
    apartine(T,H),
    sterge(T,H,R1),
    elimina(R1,R).
elimina([H|T],[H|R]):-
    \+apartine(T,H),
    elimina(T,R).

maxim([H],H).
maxim([H|T],A):-
    maxim(T,MT),
    H>MT,
    A is H.
maxim([H|T],A):-
    maxim(T,MT),
    H=<MT,
    A is MT.



eliminamax(L,R):-
    maxim(L,H),
    sterge(L,H,R).

