%sublista(L:list,M:int,N:int,C:int,R:list)
%(i,i,i,i,o)

sublista([],_,_,_,[]).
sublista([_|T],M,N,C,R):-
    C<M,
    C1 is C+1,
    sublista(T,M,N,C1,R).
sublista([H|T],M,N,C,[H|R]):-
    C>=M,
    C=<N,
    C1 is C+1,
    sublista(T,M,N,C1,R).
sublista([_|T],M,N,C,R):-
    C>N,
    sublista(T,M,N,C,R).
