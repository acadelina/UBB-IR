%cauta(L:list,e:element)
%model de flux(i,i)
%L-lista in care vom cauta elementul e
%e-elementul pe care il cautam in lista

cauta([H|_],E):-
    H=E.
cauta([H|T],E):-
    H\=E,
    cauta(T,E).



%diferenta(L:lis,P:list,R:list)
%model de flux(i,i,o)
%L-prima multime
%P-a doua multime
%R-diferenta dintre cele doua multimi

diferenta([],_,[]).
diferenta([H|T],P,R):-
    cauta(P,H),
    diferenta(T,P,R).
diferenta([H|T],P,[H|R]):-
    \+cauta(P,H),
    diferenta(T,P,R).


