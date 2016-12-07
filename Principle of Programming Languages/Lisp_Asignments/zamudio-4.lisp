;CS316 SPRING 16'
;Angelo Zamudio

(defun my-sum (L)
	(let ((X (sum (cdr L)))
		  (Y (car L))) (+ X Y)))

(defun my-neg-nums (L)
	(let ((X (neg-nums (cdr L))))
		  (if (minusp (car L)) 
		  	(cons (car L) X) X)))

(defun my-inc-list-2 (L N)
	(let ((X (inc-list-2 (cdr L) N)))
		  (cons (+ (car L) N) X)))

(defun my-insert (N L)
	(let ((X (insert N (cdr L))))
		  (if (> N (car L)) (list* (car L) N X)))
	(list* N L))

(defun my-isort (L)
	(let ((X (isort (cdr L))))
		(insert (car L) X)))

(defun my-split-list (L)
	(let ((X (split-list (cdr L))))
		(cons (car L) (car x))))

(defun my-partition (L P)
	(let ((X (partition (cdr L) P)))
		(if (< (car L) P) (cons (car L) (car X))
			(cons (car L) (cadr X)))))

;//////////////////////////////////////////////////

(defun sum (L)
	(if (endp L)
		0
		(+ (car L) (my-sum (cdr L)))))

;(print (sum '(2 4 6 8)))

(defun neg-nums (L)
	(if (endp L)
		NIL
		(if (< (car L) 0)
		 	(cons (car L) (my-neg-nums (cdr L)))
		 	(my-neg-nums(cdr L)))))

;(print (NEG-NUMS '(-1 0 –8 2 0 8 –1 –8 2 8 4 –3 0))) 
;there is a problem with negative numbers

(defun inc-list-2 (L N)
	(if (endp L)
		NIL
		(cons (+ (car L) N) (inc-list-2 (cdr L) N))))

;(print (inc-list-2 '(2 3 4 5) 2))

(defun insert (N L)
	(if (endp L)
		(list N)
		(if (< N (car L))
			(cons N L)
			(cons (car L) (insert N (cdr L))))))

;(print (insert 4 '(0 0 1 3 3 7 8 8)))

(defun isort (L)
	(if (endp L)
		NIL
		(let ((X (isort (cdr L))))
			(if (not (car X));(car x)==NIL->T, (car X)=# -> NIL/F
				(list (car L))
				(insert (car L) X)))))

;(print (isort '(25 7 1 6 3 5 9 8)))

(defun split-list (L)
	(if (endp L)
		(list NIL NIL)
		(let ((X (split-list (cdr L))))
			(append (list (cons (car L) (cadr X))) (list (car X))))))

;(print (split-list '(B C D 1 2 3 4 5)))

(defun partition (L P)
	(if (endp L)
		(list NIL NIL)
		(let ((X (partition (cdr L) P))) 
			(if (< (car L) P)
				(append (list (cons (car L) (car X))) (list (cadr X)))
				(append (list (car x)) (list (cons (car L) (cadr X))))))))

;(print (PARTITION'(4 0 5 3 1 2 4 1 4) 4))

(defun pos (E L)
	(cond ((endp L) 0)
		  ((equal E (car L)) 1)
		  (T (let ((X (pos E (cdr L))))
		  		(+ X 1)))))

;(print (POS 5'(1 2 5 3 5 5 1 5)))

(defun split-nums (N)
	(if (zerop N)
		(list '(0) NIL)
		(let ((X (split-nums(- N 1))))
			(if (evenp N)
				(append (list (cons N (car X))) (list (cadr X)))
				(append (list (car x)) (list (cons N (cadr X))))))))

;(print (SPLIT-NUMS 7))

(defun set-union (L K)
	(if (endp L)
		K
		(let ((X (set-union (cdr L) K)))
			(if (member (car L) X)
				X
				(cons (car L) X)))))

;(print (set-union '(a b c d) '(c e f)))

(defun set-remove (S N)
	(if (endp S)
		NIL
		(let ((X (set-remove (cdr S) N)))
			(if (equal (car S) N)
				X
				(cons (car S) X)))))

;(print (set-remove '(1 2 3 4) '4))

(defun set-excl-union (L K)
	(if (endp L)
		K
		(let ((X (set-excl-union (cdr L) K)))
			(if (member (car L) X)
				(set-remove X (car L))
				(cons (car L) X)))))

;(print (SET-EXCL-UNION '(A B C D) '(E C F G A))) 

(defun singletons (L)
	(if (endp L)
		NIL
		(let ((X (singletons (cdr L)) ))
			(if (member (car L) X)
				(set-remove X (car L))
				(cons (car L) X)))))

;(print (SINGLETONS '(A G A B C B)))














