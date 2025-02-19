%adaugapare(L:list,R:list)
%model de flux (i,o)
%L-lista initiala de elemente
%R-rezultatul listei dupa adaugarea de 1 dupa elem pare

adaugapare([],[]).
adaugapare([H|T],R):-
    H mod 2 =\= 0,
    adaugapare(T,R1),
    R=[H|R1].
adaugapare([H|T],R):-
    H mod 2 =:= 0,
    adaugapare(T,R1),
    R=[H,1|R1].

