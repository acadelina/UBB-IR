%inversare(L:list,A:list,R:list)
%(i,i,o)

invers([],A,A).
invers([H|T],A,R):-
    invers(T,[H|A],R).

prod([],0,_,[]).
prod([H|T],Tr,C,[A|R]):-
    A is (H*C+Tr) mod 10,
    B is (H*C+Tr) div 10,
    prod(T,B,C,R).

produs(L,C,F):-
    invers(L,[],R),
    prod(R,0,C,R2),
    invers(R2,[],F).

