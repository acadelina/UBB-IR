%range(A:int,B:int,R:list)
%(i,i,o)

range(A,A,[A]).
range(A,B,[A|R]):-
    A<B,
    A1 is A+1,
    range(A1,B,R).
