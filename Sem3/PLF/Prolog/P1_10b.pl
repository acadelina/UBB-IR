%cmmdc(A:int,B:int,R:rez)

cmmdc(A,0,A).
cmmdc(A,B,R):-
    B=\=0,
    Rest is A mod B,
    cmmdc(B,Rest,R).

cmmdcList([],0).
cmmdcList([A],A).
cmmdcList([H1,H2|T],R):-
    cmmdc(H1,H2,Rez),
    cmmdcList([Rez|T],R).
