Section Negation.
  Variables P Q R S T: Prop.

  (* unfold not: expansion de la négation dans le but *)
  (* unfold not in X: expansion de la négation dans l'hypothèse X *)
  (* exfalso: transforme le but courant en False; c'est l'équivalent
     de la règle d'élimination de la contradiction *)

  (* Executez cette preuve en essayant de comprendre le sens de chacune des nouvelles tactiques utilisées. *)
  Lemma absurde_exemple: P -> ~P -> S.
  Proof.
    intros p np.
    unfold not in np.
    exfalso.
    apply np.
    assumption.
  Qed.
  
  Lemma triple_neg_e : ~~~P -> ~P.
  Proof.
     intro H. 
     intro H0.
     apply H.
     intro H1.
     apply H1; assumption.
   Restart.  (* Annule la preuve en cours, et en commence un autre *)
   unfold not.
   auto.
   (* auto est une tactique qui est capable de beaucoup, mais qu'on
      s'interdira d'utiliser dans nos preuves *)
   Qed.

  (* Début des exercices *)

  (* QUESTION: Remplacer les Admitted par des scripts de preuve *)
  Lemma absurde: (P -> Q) -> (P -> ~Q) -> (P -> S).
  Proof.
  Admitted.

  Lemma triple_abs: ~P -> ~~~P.
  Proof.
  Admitted.
  
  Lemma absurd' : (~P -> P) -> ~~P.
  Proof.
  Admitted.

  Definition Peirce  := ((P -> Q) -> P) -> P.

  (* On va prouver non-non-Peirce *)
  Lemma Peirce_2 : ~~ Peirce.
  Proof.
    (* Strategie: sous hypothese ~Peirce [par intro], montrer ~P, puis s'en 
       servir pour montrer Peirce, et on aura une contradiction
       entre Peirce et ~Peirce *)
    intro.
    assert (np: ~P).
  Admitted. (* À vous de finir *)

  (* Une série de séquents à prouver; à chaque fois, il faut
  l'énoncer, en introduisant les hypothèses au moyen d'une
  sous-section. *)

  (* P->Q, R->~Q, P->R |- P->S *)

  (* ~P->~Q |- ~~Q->~~P *)

  (* P->~P |- ~P *)

  (* ~~P |- ~P->~Q *)

  (* P->~Q, R->Q |- P->~R *)

  (* ~(P->Q) |- ~Q *)
  

  (* Séquents proposés en test par le passé *)

  Section Test01.
    
    Hypothesis H: P->Q.

    Lemma Ex01: ~(~Q->~P) -> R.
    Admitted.
  End Test01.

  Section Test02.
    Hypothesis H: ~(P->R).

    Lemma Ex02: Q->(P->Q->R)->P.
    Admitted.
  End Test02.

  Section Test03.
    Hypothesis H: ~(Q->R).

    Lemma Ex03: (P->Q->R)->(P->Q).
    Admitted.
  End Test03.

  Section Test04.
    Hypothesis H: ~~P.

    Lemma Ex04: Q->(P->Q->False)->P.
    Admitted.
  End Test04.
    
End Negation.


