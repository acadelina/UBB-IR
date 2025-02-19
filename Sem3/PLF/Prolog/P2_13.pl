%divizorii(N:int,D:int,R:list)
%(i,i,o)

divizorii(N,D,[]):-
    D>=N,
    !.
divizorii(N,D,R):-
    N mod D =\=0,
    D1 is D+1,
    divizorii(N,D1,R).
divizorii(N,D,[D|R]):-
    N mod D =:=0,
    D1 is D+1,
    divizorii(N,D1,R).

adauga2(H,[],H).
adauga2(W,[H|T],[H|R]):-
    adauga2(W,T,R).

functie([],[]).
functie([H|T],[H|R]):-
    divizorii(H,2,R1),
    functie(T,R2),
    adauga2(R2,R1,R).
