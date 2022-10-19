        /** <examples>
        ?- run.
        ?- belong(X),mc(X),notsk(X).
        */

        belong(a).
        belong(b).
        belong(c).
        belong(X):-notmc(X),notsk(X),!, fail. 
        belong(_).
        like(a,rain).
        like(a,snow).
        like(a,X) :- dislike(b,X).
        like(b,X) :- like(a,X),!,fail.
        like(b,_).
        mc(Y):-like(Y,rain),!,fail.
        mc(_).
        notsk(X):- dislike(X,snow). 
        notmc(X):- mc(X),!,fail.
        notmc(_).
        dislike(P,Q):- like(P,Q),!,fail.
        dislike(_,_).
        g(X):-belong(X),mc(X),notsk(X),!.
        