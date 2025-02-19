%inser(L:list,A:int,R:list)
%(i,i,o)

inser([],A,[A]).
inser([H|T],A,[A,H|T]):-
    A<H.
inser([H|T],A,[H|R]):-
    H<A,
    inser(T,A,R).
inser([H|T],A,[H|T]):-
    H=:=A.

sortare([],[]).
sortare([H|T],R):-
    sortare(T,R1),
    inser(R1,H,R).
