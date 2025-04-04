%apartine(E:int,L:list)
%(i,i)
apartine(E,[H|_]):-
    E=:=H.
apartine(E,[H|T]):-
    E=\=H,
    apartine(E,T).


%unice(L:list,R:list)
%(i,o)

unice([],[]).
unice([H|T],[H|R]):-
    \+apartine(H,T),
    unice(T,R).
unice([H|T],R):-
    apartine(H,T),
    unice(T,R).

elimina(_,[],[]).
elimina(E,[H|T],[H|R]):-
    E=\=H,
    elimina(E,T,R).
elimina(E,[H|T],R):-
    E=:=H,
    elimina(E,T,R).

%transforma(L:list,P:list,R:list)
%(i,i,o)

transforma([],_,[]).
transforma([H|T],L,[H|R]):-
    apartine(H,L),
    elimina(H,L,L1),
    transforma(T,L1,R).
transforma([H|T],L,R):-
    \+apartine(H,L),
    elimina(H,L,L1),
    transforma(T,L1,R).

tr_final(L,R):-
    unice(L,L1),
    transforma(L,L1,R1),
    R=R1.

