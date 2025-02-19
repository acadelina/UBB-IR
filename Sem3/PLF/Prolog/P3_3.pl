%minim(L:list,R:int)
%model de flux(i,o),determinist
%L-lista elementelor in care cautam minimul
%R-elementul minim din lista

minim([A],A).
minim([H|T],A):-
    minim(T,A),
    A<H.
minim([H|T],H):-
    minim(T,A),
    H=<A.

%subsiruri(L:list,M:int,R:list)
%model de flux(i,i,o),nedeterminist
%L-lista initiala din care vrem sa extragem un subsir
%M-elementul minim din L
%R-subsirul strict crescator din L

subsiruri([],_,[]).
subsiruri([H|T],M,[H|R]):-
    M<H,
    subsiruri(T,H,R).
subsiruri([_|T],M,R):-
    subsiruri(T,M,R).


%subsiruriCresc(L:list,T:list)
%model de flux(i,o),nedeterminist
%L-lista initiala de elemnte
%T-un subsir crescator din L
subsiruriCresc(L,T):-
    minim(L,Min),
    Min1 is Min-1,
    subsiruri(L,Min1,T).

%main(L:list,R:list)
%model de flux(i,o)
%L-lista initiala din care vom extrage subsirurile
%R-lista subsirurilor strict crescatoare din L
main(L,R):-findall(R1,subsiruriCresc(L,R1),R).

%TESTE
%1)main([1,2,1,3,4,5,2],R).
%R = [[1, 2, 3, 4, 5], [1, 2, 3, 4], [1, 2, 3, 5], [1, 2, 3], [1, 2, 4,
% 5], [1, 2, 4], [1, 2|...], [1|...], [...|...]|...].

%2) main([1,0,2],R).
%R = [[1, 2], [1], [0, 2], [0], [2], []].

%3) main([4,2,3,6],R).
% R = [[4, 6], [4], [2, 3, 6], [2, 3], [2, 6], [2], [3, 6], [3],
% [...]|...].


%4)main([1,1,1],R).
%R = [[1], [1], [1], []].
