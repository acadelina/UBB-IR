exista([A],A).
exista([H|_],H).
exista([H|T],A):-
    H=\=A,
    exista(T,A).

difmult([],_,[]).
difmult([H|T],L,[H|R]):-
    \+exista(L,H),
    difmult(T,L,R).
difmult([H|T],L,R):-
    exista(L,H),
    difmult(T,L,R).

cmmdc(A,0,A).
cmmdc(A,B,R):-
    B=\=0,
    R1 is A mod B,
    cmmdc(B,R1,R).

cmmmc(A,B,R):-
    cmmdc(A,B,R1),
    R is (A*B)/R1.

sterge([],_,[]).
sterge([H|T],A,R):-
    H=:=A,
    sterge(T,A,R).
sterge([H|T],A,[H|R]):-
    H\=A,
    sterge(T,A,R).

multime([],[]).
multime([H|T],[H|R]):-
    sterge(T,H,T1),
    multime(T1,R).

elimina([H|T],P,N,[H|R]):-
    N=\=P,
    P1 is P+1,
    elimina(T,P1,N,R).
elimina([_|T],P,N,T):-
    P=:=N.

append([],L,L).
append([H|T],L,[H|R]):-
    append(T,L,R).

pereche([],_,[]).
pereche([H|T],A,[[A,H]|R]):-
    pereche(T,A,R).

perechi([],[]).
perechi([H|T],R):-
    pereche(T,H,R1),
    perechi(T,R2),
    append(R1,R2,R).

%vale(l1...ln,f)=
%       adevarat, l1<l2 si f\=-1
%       vale(l2...ln,0), l1>l2 si f\=1
%       vale(l2...ln,1), l1<l2 si f\=-1
%       fals, altfel

vale([H1,H2],F):-
    F=\=(-1),
    H1<H2.
vale([H1,H2|T],F):-
    F=\=1,
    H1>H2,
    vale([H2|T],0).
vale([H1,H2|T],F):-
    F=\=(-1),
    H1<H2,
    vale([H2|T],1).

select([H|_],N,N,H).
select([_|T],P,N,R):-
    P1 is P+1,
    P<N,
    select(T,P1,N,R).

elk([],_,_,_,[]).
elk([H|T],P,K,C,[H|R]):-
    P=\=K,
    P1 is P+1,
    elk(T,P1,K,C,R).
elk([_|T],P,K,C,R):-
    P=:=K,
    P1 is P+1,
    K1 is K+C,
    elk(T,P1,K1,C,R).

dublare([],_,_,[]).
dublare([H|T],P,K,[H,H|R]):-
    H mod 2=:=0,
    P<K,
    P1 is P+1,
    dublare(T,P1,K,R).
dublare([H|T],P,K,[H|R]):-
    H mod 2 =:=1,
    P<K,
    P1 is P+1,
    dublare(T,P1,K,R).
dublare([_|T],P,K,R):-
    P=:=K,
    K1 is K*2+1,
    P1 is P+1,
    dublare(T,P1,K1,R).

append(L,0,_,L):-!.
append(L,NR,X,[X|R]):-
    NR1 is NR-1,
    append(L,NR1,X,R).

adaugam([],_,_,_,_,_,[]).
adaugam([H|T],P,M,X,N,C,[H|R]):-
    P<M,
    P1 is P+1,
    adaugam(T,P1,M,X,N,C,R).
adaugam([H|T],P,M,X,N,C,R):-
    P=:=M,
    P1 is P+1,
    M1 is M+N,
    C1 is C+1,
    adaugam(T,P1,M1,X,N,C1,R1),
    append(R1,C,X,R2),
    R=[H|R2].

