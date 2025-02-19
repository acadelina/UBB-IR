%sterge(L:list,a:int,R:list)
%(i,i,o)

sterge([],_,[]).
sterge([H|T],E,[H|R]):-
    H=\=E,
    sterge(T,E,R).
sterge([H|T],E,R):-
    H=:=E,
    sterge(T,E,R).

%NrAparitii(L:list,A:int,R:int)
%(i,i,o)

nrAparitii([],_,1).
nrAparitii([H|T],E,N):-
    H=:=E,
    nrAparitii(T,E,N1),
    N is N1+1.
nrAparitii([H|T],E,N):-
    H=\=E,
    nrAparitii(T,E,N).

perechi([],[]).
perechi([H|T],[R1|R]):-
    nrAparitii(T,H,A),
    sterge(T,H,T1),
    R1=[H,A],
    perechi(T1,R).
