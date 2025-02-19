%multime(L:list,R:list)
%(i,o)

multime([],[]).
multime([H|T],[H|R]):-
    \+exista2(T,H),
    multime(T,R).
multime([H|T],R):-
    exista2(T,H),
    multime(T,R).
