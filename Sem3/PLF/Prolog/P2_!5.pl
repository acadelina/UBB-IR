%lungimemax(L:list,C:int,R:int)
%(i,i,o)

lungimemax([],0,0).
lungimemax([H],1,1):-
    H mod 2=:=0.
lungimemax([H],0,0):-
    H mod 2=\=0.
lungimemax([_,H2|T],C,C):-
    H2 mod 2 =\= 0,
    lungimemax(T,0,R),
    C>R.
lungimemax([_,H2|T],C,R):-
    H2 mod 2 =\= 0,
    lungimemax(T,0,R),
    C=<R.
lungimemax([H1,H2|T],C,R):-
    H1  mod 2 =:=0,
    H2 mod 2  =:=0,
    H2 =:= H1+2,
    C1 is C+1,
    lungimemax([H2|T],C1,R).
lungimemax([H1,H2|T],C,R):-
    H1  mod 2 =:=0,
    H2 =\= H1+2,
    lungimemax(T,0,R),
    C=<R.
lungimemax([H1,H2|T],C,C):-
    H1  mod 2 =:=0,
    H2 =\= H1+2,
    lungimemax([H2|T],0,R),
    C>R.


lungime(L,R):-
    lungimemax(L,0,R).



%secventa(L:list,LC:list,DC:int,DM:int,LM:list,R:list)

secventa([],LC,DC,DM,_,LC):-DC>DM.
secventa([],_,DC,DM,LM,LM):-DM>=DC.
secventa([H|T],LC,DC,DM,_,R):-
    H mod 2=\=0,
    DC>DM,
    secventa(T,[],0,DC,LC,R).
secventa([H|T],_,DC,DM,LM,R):-
    H mod 2=\=0,
    DM>=DC,
    secventa(T,[],0,DM,LM,R).
secventa([H|T],LC,DC,DM,LM,R):-
    H mod 2=:=0,
    C is DC+1,
    LC1=[H|LC],
    secventa(T,LC1,C,DM,LM,R).

secventamax([],_,LC,M,LM,M):-
    LM>LC.
secventamax([],C,LC,_,LM,C):-
    LC>=LM.
secventamax([H1,H2|T],_,LC,M,LM,R):-
    H2 mod 2=\=0,
    H1 mod 2=:=0,
    LC1 is LC+1,
    LM>LC1,
    secventamax(T,[],0,M,LM,R).
secventamax([H1,H2|T],C,LC,_,LM,R):-
    H2 mod 2 =\=0,
    H1 mod 2=:=0,
    LC1 is LC+1,
    LC1>=LM,
    secventamax(T,[],0,[H1|C],LC1,R).
secventamax([H1,H2|T],C,LC,M,LM,R):-
    H2=:=H1+2,
    H1 mod 2 =:=0,
    LC1 is LC+1,
    secventamax([H2|T],[H1|C],LC1,M,LM,R).
secventamax([H1,H2|T],C,LC,_,LM,R):-
    H2=\=H1+2,
    H1 mod 2=:=0,
    LC1 is LC+1,
    LC1>LM,
    secventamax(T,[],0,[H1|C],LC1,R).
secventamax([H1,H2|T],_,LC,M,LM,R):-
    H2=\=H1+2,
    H1 mod 2=:=0,
    LC1 is LC+1,
    LC1=<LM,
    secventamax(T,[],0,M,LM,R).





