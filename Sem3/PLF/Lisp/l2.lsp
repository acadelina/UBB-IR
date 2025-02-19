;3. Se da un arbore de tipul (1). Sa se precizeze numarul de niveluri din
; arbore.

;parcurg_st(l1,l2...ln,nv,nm)={ [], l e vida
							;   [], nv=1+nm
							;   l1(+)l2(+)parcurg_st(l3..ln,nv+1,nm+l2)}
							
(defun parcurg_st(arb nv nm)
 (cond
 ((null arb) nil)
 ((= nv (+ 1 nm)) nil)
 (t (cons (car arb) (cons (cadr arb) (parcurg_st (cddr arb) (+ 1 nv) (+ (cadr arb) nm)))))
 )
)

;parcurg_dr(l1..ln,nv,nm)={[], l e vida
						;  l, nv=1+nm
						; parcurg_dr(l3..ln,nv+1,nm+l2)}

(defun parcurg_dr(arb nv nm)
	(cond
	((null arb) nil)
	((= nv (+ 1 nm)) arb)
	(t (parcurg_dr(cddr arb) (+ 1 nv) (+ (cadr arb) nm)))
	)
)

;stang(l1l2...ln) = 
; = parcurg_st(l3...ln, 0,0)

(defun stang(arb)
	(parcurg_st (cddr arb) 0 0))

;drept(l1l2...ln) =
; = parcurg_dr(l3...ln, 0, 0)
(defun drept(arb)
	(parcurg_dr (cddr arb) 0 0))
	
; myMax(a, b) = 
; = a , if a > b
; = b , otherwise

(defun myMax(a b)
  (cond
    ((> a b) a)
    (t b)
  )
)


; levels(l1l2...ln, counter) = 
; = counter, if n = 0
; = myMax(levels(stang(l1l2...ln), counter + 1), levels(drept(l1l2...ln), counter + 1)), otherwise


(defun levels(l counter)
  (cond
    ((null l) counter)
    (t (myMax (levels (stang l) (+ 1 counter)) (levels (drept l) (+ 1 counter))))
  )
)


(defun main(l)
  (levels l -1)
)