%vale(L:list,F:int)
%(i,i)

vale([_],1).
vale([L1,L2|T],F):-
    F=\=1,
    L1>L2,
    vale([L2|T],0).
vale([L1,L2|T],F):-
    F=\=(-1),
    L1<L2,
    vale([L2|T],1).

suma([],_,0).
suma([H|T],F,R):-
    F1 is F*(-1),
    suma(T,F1,R1),
    R is R1+(F*H).
