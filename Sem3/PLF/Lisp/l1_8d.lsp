(defun exista2 (lista a)
    (cond
        ((null lista) nil)
        ((equal a (car lista))t)
        (t (exista2 (cdr lista) a))))

(defun multime_test(l)
    (cond
     ((null l)t)
     ((exista2 (cdr l) (car l))nil)
     (t (multime_test(cdr l)))))