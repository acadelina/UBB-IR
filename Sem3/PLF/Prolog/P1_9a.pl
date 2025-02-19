%sterge(L:list,E:int,R:list)
%(i,i,o)

sterge([],_,[]).
sterge([H|T],E,[H|R]):-
    E=\=H,
    sterge(T,E,R).
sterge([H|T],E,R):-
    E=:=H,
    sterge(T,E,R).

%intersectie(L:list,P:list,R:list)
%(i,i,o)
intersectie([],[],[]).
intersectie([],_,[]).
intersectie(_,[],[]).
intersectie([H|T],L,[H|R]):-
    exista2(L,H),
    intersectie(T,L,R).
intersectie([H|T],L,R):-
    \+ exista2(L,H),
    intersectie(T,L,R).
