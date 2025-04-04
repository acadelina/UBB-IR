%invers(L:list,Acm:list,R:list)
%(i,i,o)

invers([],A,A).
invers([H|T],A,R):-
    invers(T,[H|A],R).

%adauga(L:list,C:int,T:int,R:list)
%(i,i,i,o)
adauga([],0,[]).
adauga([],Tr,[Tr]):-
    Tr>0.
adauga([H|T],Tr,R):-
    N1 is (H+Tr) mod 10,
    N2 is (H+Tr) div 10,
    adauga(T,N2,R1),
    R=[N1|R1].

succesor(L,R):-
    invers(L,[],R1),
    adauga(R1,1,R2),
    invers(R2,[],R).
