%egalitate(L:list,P:list)
%(i,i)
stergeE([],_,[]).
stergeE([H|T],E,[H|R]):-
    H=\=E,
    stergeE(T,E,R).
stergeE([H|T],E,R):-
    H=:=E,
    stergeE(T,E,R).

egalitate([],[]).
egalitate([H|T],L):-
    exista2(L,H),
    stergeE(L,H,R1),
    egalitate(T,R1).


%nelement(L:list,N:int,C:int,E:int)
nelement([_|T],N,C,E):-
    C<N,
    C1 is C+1,
    nelement(T,N,C1,E).
nelement([H|_],N,C,H):-
    N=:=C.
