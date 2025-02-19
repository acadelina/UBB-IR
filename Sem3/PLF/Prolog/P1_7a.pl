%exista(L:list,a:int)
%(i,i)

exista([H|_],A):-
    H=:=A.
exista([H|T],A):-
    H=\=A,
    exista(T,A).

%reuniune(L:list,P:list,R:list)
%(i,i,o)

reuniune([],[],[]).
reuniune([H|T],P,R):-
    \+exista(T,H),
    \+exista(P,H),
    reuniune(T,P,R1),
    R=[H|R1].
reuniune([H|T],P,R):-
    exista(T,H),
    reuniune(T,P,R).
reuniune([H|T],P,R):-
    exista(P,H),
    reuniune(T,P,R).
reuniune([],[H|T],[H|R]):-
    \+exista(T,H),
    reuniune([],T,R).
reuniune([],[H|T],R):-
    exista(T,H),
    reuniune([],T,R).

