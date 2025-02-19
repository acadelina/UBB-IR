divizibil(N,D):-
    D*D>N,
    !.
divizibil(N,D):-
    N mod D =\= 0,
    D1 is D+1,
    divizibil(N,D1).

prim(2).
prim(3).
prim(N):-
    N>3,
    N mod 2 =\=0,
    divizibil(N,3).


dublareprim([],[]).
dublareprim([H|T],[H|R]):-
    \+prim(H),
    dublareprim(T,R).
dublareprim([H|T],[H,H|R]):-
    prim(H),
    dublareprim(T,R).
