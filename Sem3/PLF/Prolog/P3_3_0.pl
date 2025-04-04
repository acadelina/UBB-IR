%candidat(L:list,E:int)
%model de flux(i,o)
%L:lista din care vrem sa generam un element
%E:elementul generat din lista data
candidat([H|_],H).
candidat([_|T],E):-
    candidat(T,E).

%generare(L:list,C:list,R:list)
%model de flux(i,i,o)
%L-lista pentru care vrem sa generam un subsir crescator
%C-secventa curenta pe care o construim
%R-rezultatul subsirul strict crescator generat
generare(_,C,C).
generare(L,[H|T],R):-
    candidat(L,E),
    E<H,
    generare(L,[E,H|T],R).

% generareMain(L:list, R:list)
% L-lista de intrare
% R-un subsir crescator generat
generareMain(L,R):-
    candidat(L,E1),%pornim generarea subsirului de la un element E1 ca prim element in lista
    generare(L,[E1],R).

main2(L,R):-
    findall(R1,generareMain(L,R1),R).
