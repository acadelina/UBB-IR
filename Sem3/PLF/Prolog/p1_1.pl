%Cazul in care se afla la inceputul listei
apare(E,[E|_]).
apare(E,[_|T]):-
    apare(E,T).
%Cazul de baza: intersectia cu multimi goale
intersectie([],_,[]).
%Daca primul element al primei multimi apare in a doua
intersectie([H|T],L2,[H|R]):-
    apare(H,L2),
    !,
    intersectie(T,L2,R).
%Daca primul element nu apare in a doua multime
intersectie([_|T],L2,R):-
    intersectie(T,L2,R).

