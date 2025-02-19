%pare(L:list,R:list)
%(i,o)

pare([],[],0).
pare([H|T],[H|R],N):-
    H mod 2 =:=0,
    pare(T,R,N1),
    N is N1+1.
pare([H|T],R,N):-
    H mod 2 =:=1,
    pare(T,R,N).



impare([],[],0).
impare([H|T],[H|R],N):-
    H mod 2 =:=1,
    impare(T,R,N1),
    N is N1+1.
impare([H|T],R,N):-
    H mod 2 =:=0,
    impare(T,R,N).

descompunere(L,[R1,R2],N1,N2):-
    pare(L,R1,N1),
    impare(L,R2,N2).
