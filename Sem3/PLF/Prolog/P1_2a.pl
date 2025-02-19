%cmmdc(A:int,B:int,R:int)
%(i,i,o)

cmmdc(A,0,A).
cmmdc(A,B,R):-
    B=\=0,
    Rest is A mod B,
    cmmdc(B,Rest,R1),
    R is R1.

%cmmmc(A:int,B:int,C:int)
%(i,i,o)

cmmmc(A,B,C):-
    cmmdc(A,B,C2),
    C is A*B/C2.

cm_lista([E],E).
cm_lista([H1,H2|T],R):-
    cmmmc(H1,H2,C),
    cm_lista([C|T],R1),
    R is R1.
