%adunare(N1:list,N2:list,T:int,R:list)
%(i,i,i,o)

%transforma(N1:list,Z:int,R:int)

transformalista([],R,R).
transformalista([H|T],Z,R):-
    Z1 is Z*10+H,
    transformalista(T,Z1,R).

inversare(0,Z,Z):-!.
inversare(N,Z,R):-
    N1 is N mod 10,
    N2 is N div 10,
    Z1 is Z*10+N1,
    inversare(N2,Z1,R).


transformanr(0,[]):-!.
transformanr(N,[N1|L]):-
    N1 is N mod 10,
    N2 is N div 10,
    transformanr(N2,L).

suma2(L1,L2,R):-
    transformalista(L1,0,R1),
    transformalista(L2,0,R2),
    S is R1+R2,
    inversare(S,0,S1),
    transformanr(S1,R).


invers([],A,A).
invers([H|T],A,R):-
    invers(T,[H|A],R).

adunare([],[],Tr,[Tr]):-
    Tr>0.
adunare([],[],Tr,[]):-
    Tr=:=0.
adunare([H1|T1],[H2|T2],Tr,R):-
    N is (H1+H2+Tr) mod 10,
    M is (H1+H2+Tr) div 10,
    adunare(T1,T2,M,R1),
    R=[N|R1].
adunare([H1|T1],[],Tr,R):-
    N is (H1+Tr) mod 10,
    M is (H1+Tr) div 10,
    adunare(T1,[],M,R1),
    R=[N|R1].
adunare([],[H2|T2],Tr,R):-
    N is (H2+Tr) mod 10,
    M is (H2+Tr) div 10,
    adunare([],T2,M,R1),
    R=[N|R1].

add(N1,N2,R):-
    invers(N1,[],M1),
    invers(N2,[],M2),
    adunare(M1,M2,0,R1),
    invers(R1,[],R).
