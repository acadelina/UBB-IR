inv([],A,A).
inv([H|T],A,R):-
    inv(T,[H|A],R).

diferenta([],_,[]).
diferenta([H|T],Tr,[N1|R]):-
    H<Tr,
    N1 is H+10-Tr,
    diferenta(T,1,R).
diferenta([H|T],Tr,[N1|R]):-
    H>=Tr,
    N1 is H-Tr,
    diferenta(T,0,R).

diff(P,R):-
    inv(P,[],R1),
    diferenta(R1,1,R2),
    inv(R2,[],R).
