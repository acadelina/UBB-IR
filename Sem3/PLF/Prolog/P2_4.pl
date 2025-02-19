%interclasare(L:list,P:list,R:list)
%(i,i,o)

interclasare([],[],[]).
interclasare([],[H|T],[H|R]):-
    \+exista2(T,H),
    interclasare([],T,R).
interclasare([H|T],[],[H|R]):-
    \+exista2(T,H),
    interclasare(T,[],R).
interclasare([],[H|T],R):-
    exista2(T,H),
    interclasare([],T,R).
interclasare([H|T],[],R):-
    exista2(T,H),
    interclasare(T,[],R).

interclasare([H1|T1],[H2|T2],[H1|R]):-
    H1<H2,
    \+exista2(T1,H1),
    interclasare(T1,[H2|T2],R).

interclasare([H1|T1],[H2|T2],[H2|R]):-
    H2<H1,
    \+exista2(T2,H2),
    interclasare([H1|T1],T2,R).
interclasare([H1|T1],[H2|T2],R):-
    H1=H2,
    interclasare([H1|T1],T2,R).

