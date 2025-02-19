%Cazul de baza: cand m este mai mare decat n, lista e goala
range(M,N,[]) :- M>N.
%Cazul recursiv: adaug M la lista si apelam recursiv pt M+1
range(M,N,[M2|Rest]):-
    M=<N,
    M1 is M+1,
    M2 is M*2,
    range(M1, N, Rest).
