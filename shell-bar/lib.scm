(library (shell-bar lib)
  (export take compose lin-space)
  (import (rnrs base (6))
          (rename (srfi :26 cut) (cut $)))

  (define (compose f . rest)
    (if (null? rest)
      f
      (let ((g (apply compose rest)))
        (lambda args
          (call-with-values ($ apply g args) f)))))

  (define take
    (lambda (lst n)
      (let loop ((l lst)
                 (result '())
                 (m n))
        (if (or (zero? m) (null? l))
          (reverse result)
          (loop (cdr l) (cons (car l) result) (- m 1))))))

  (define (lin-space a b n)
    (let loop ((r '())
               (i n))
      (if (zero? i)
        (cons a r)
        (loop (cons (* i (/ (- b a) n)) r) (- i 1)))))
)
