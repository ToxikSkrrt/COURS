(* Raccourcis clavier de coqide *)
(* CTRL-flèche bas: avancer d'une commande *)
(* CTRL-flèche haut: revenir en arrière d'une commande *)
(* CTRL-flèche droit: avancer ou revenir en arrière jusqu'au curseur *) 

(** premiers pas en Coq *)

(* Logique minimale "pure": pas de négation/contradiction *)

Section Exemples.

  (* Définition de variables propositionnelles *)
  Variables P Q R S T : Prop.

  (* Une Section peut contenir d'autres [sous-]Sections. C'est le bon endroit
     pour definir des hypotheses (et donc prouver des sequents avec hypotheses).
   *)
  
  Lemma imp_dist: (P -> Q -> R) -> (P -> Q) -> P -> R.
  Proof.
    intro Hpqr.
    intro Hpq.
    intro Hp.
    apply Hpqr.
    - assumption.
    - apply Hpq.
      assumption.
  Qed.

  (* Explication des tactiques utilisées: *)
  (* intro: utilisation de la regle d'introduction pour changer de but *)
  (* apply: utilisation d'une implication qui a la bonne conclusion
     (il va falloir prouver ses hypotheses) *)
  (* Note: on ne peut faire "apply" que sur une propriété déjà prouvée,
     contrairement au modus ponens des preuves en arbres *)
  (* C'est automatiquement un modus ponens: "apply Hpqr" pour prouver R
     demande à prouver P et Q *)
  (* assumption: utilisation de la regle d'hypothese *)

  (* Autre tactique utile: intros 
     permet de faire plusieurs introductions d'un coup (intro multiple) *)

  Check imp_dist.  (* On voit la formule prouvée *)
  Print imp_dist.  (* Pour voir le "terme de preuve" calculé *)
  (* la syntaxe est très proche de celle de Ocaml *)

  (* exemple de preuve d'un sequent avec hypothèses *)
  (* On crée une section spécifique, sinon les hypothèses
     ajoutées pour ce lemme resteront pour les suivants *)
  Section S1.
    Hypothesis H : P -> Q.
    Hypothesis H0 : P -> Q -> R.

    Lemma L2 : P -> R.
    (* le sequent est: P->Q, P->Q->R |- P->R *)
    Proof.
      intro p.
      apply H0.
      - assumption.
      - apply H.
        assumption.
    Qed.

    Check L2. (* Les hypothèses font partie de la section *)
  End S1.

  (* Quand on ferme la section, ses hypotheses sont "exportees" sous la
     forme d'hypotheses supplementaires pour L2                         *)
  Check L2.
End Exemples.

Check L2.
(* La section Exemples avait des variables P Q R; une
   fois fermée, ces variables sont exportées sous forme
   universelle: cela permet d'appliquer L2 à d'autres
   propositions (théorème de substitution) *)
   
Section Exemple_bis.
  Variables A B C: Prop.

  Lemma L2': (A->B)->(A->B->C)->A-> C.
  Proof.
    apply L2. (* Ici Coq "voit" tout seul qu'il suffit
                 de prendre A pour P, B pour Q et 
                 C pour R, et L2 a alors le bon énoncé *)
  Qed.
End Exemple_bis.

Section Exercices.
  Variables P Q R S T: Prop.

  Section About_cuts.
    Hypothesis H : P -> Q.
    Hypothesis H0 : P -> Q -> R.
    Hypothesis H1 : Q -> R -> S.
    Hypothesis H2 : Q -> R -> S -> T.

    (* preuve sans lemme (coupure) *)
    Lemma L3 : P -> T.
    (* QUESTION: Quel est le séquent qu'on s'apprête à prouver? *)
    (* P -> T *)

    (* QUESTION: Faites-en une preuve papier AVANT de continuer *)
    Proof.
      intro p.
      apply H2.
      apply H.
      assumption.
      apply H0.
      assumption.
      apply H.
      assumption.
      apply H1.
      apply H. 
      assumption.
      apply H0.
      assumption.
      apply H. 
      assumption.
    Restart. (* Restart.: recommence une preuve de zéro *)
    (* QUESTION: Réécrivez le script ci-dessus en introduisant des tirets 
       (-, *, +) à chaque fois qu'une tactique engendre plus d'un 
       sous-but *)
      intro Hp.
      apply H2.
        - apply H.
          assumption.
        - apply H0.
          assumption.
          apply H.
          assumption.
        - apply H1.
          * apply H.
            assumption.
          * apply H0.
            assumption.
            apply H.
            assumption.
          
    
    Qed. (* À remplacer par "Qed." une fois la preuve faite. *)

    (* preuve avec coupures: on prouve Q et R une seule fois chacun,
       puis on les utilise *)

     Lemma L'3 : P -> T.
     Proof.
       intro p.
       assert (q: Q). { 
         apply H. assumption.
         }
       (* On a fini de prouver Q; on a maintenant une hypothèse (q:Q) *)   
       assert (r: R). {
         apply H0.
         - assumption.
         - assumption.
          }
       (* Pareil: on a maintenant prouvé R, et on a gagné une hypothèse *)
       assert (s : S). {
        apply H1. assumption. assumption.
       }
       apply H2; assumption. (* sans le ; il faut trois "assumption" *)
     Qed.

     (* assert: permet d'ouvrir une nouvelle sous-preuve, *)
     (* dans laquelle on se définit un nouveau but; c'est *)
     (* une coupure. Les accolades sont optionnelles mais *)
     (* facilitent la lecture humaine                     *)
     
     Check L'3.

(* remarquez la différence entre les termes de preuves avec coupure et sans coupure. *)
     Print L'3.
     Print L3.
(* Les coupures deviennent des "let.. in.." similaires à ceux de Ocaml *)

  End About_cuts.


 (* Les exercices commencent ici, à part la preuve admise de L2.  

    Reprendre les exemples vus en TD, en utilisant les tactiques 
    assumption, apply, assert et intro/intros.

    Remplacer chaque commande Admitted par un script correct de preuve,
    suivi de la commande Qed.

  *)

  Lemma IdP : P -> P.  
  Proof.
    intro H0.
    assumption.
  Qed.

  Lemma IdPP : (P -> P) -> P -> P.
  Proof.
    intros H0  H1.
    assumption.
  Qed.

  (* sans regarder le fichier de demo, c'est de la triche *)
  Lemma imp_trans : (P -> Q) -> (Q -> R) -> P -> R.
  Proof.
    intros H0 H1 H2.
    apply H1.
    apply H0.
    assumption.
  Qed.

  Section proof_of_hyp_switch.
    Hypothesis H : P -> Q -> R.
    Lemma hyp_switch : Q -> P -> R.
    Proof.
      intros H0 H1.
      apply H; assumption.
    Qed. 

  End proof_of_hyp_switch.

  Check hyp_switch.

  Section proof_of_add_hypothesis.
    Hypothesis H : P -> R.

    Lemma add_hypothesis : P -> Q -> R.
    Proof.
      intros H0 H1.
      apply H.
      assumption.
    Qed.

  End proof_of_add_hypothesis.


  Section proof_of_remove_dup_hypothesis.
  (* prouver le sequent (P -> P -> Q) |- P -> Q  
     (il faut l'énoncer, et faire la preuve) *)
    Hypothesis H : P -> P -> Q.
    
    Lemma remove_dup_hypothesis : P -> Q.
    Proof.
      intro H0.
      apply H ; assumption.
    Qed.
  End proof_of_remove_dup_hypothesis.


  Section proof_of_dup_hypothesis.
  (* même exercice avec le séquent P->Q |- P->P->Q *)
    Hypothesis H : P -> Q.
    
    Lemma dup_hypothesis : P -> P -> Q.
    Proof.
      intros H0 H1.
      apply H.
      assumption.
    Qed.
  End proof_of_dup_hypothesis.

 
  Section proof_of_distrib_impl.
 (* meme exercice avec 
     P -> Q , P -> R , Q -> R -> T |- P -> T  
   *)
    Hypothesis H0 : P -> Q.
    Hypothesis H1 : P -> R.
    Hypothesis H2 : Q -> R -> T.
    
    Lemma distrib_impl : P -> T.
    Proof.
      intro H3.
      apply H2.
      {
        apply H0.
        assumption.
      }
      {
        apply H1.
        assumption.
      }
    Qed.
  End proof_of_distrib_impl.


  Section proof_of_ex9.
  (* même exercice, avec 
     P->Q, Q->R, (P->R)->T->Q, (P->R)->T |- Q   
     (ex. 9 de la feuille "Logique minimale")
   *)
   Hypothesis H0 : P -> Q.
   Hypothesis H1 : Q -> R.
   Hypothesis H2 : (P -> R) -> T -> Q.
   Hypothesis H3 : (P -> R) -> T.
   
   Lemma ex9 : Q.
   Proof.
    apply H2.
    - intro H4.
      apply H1.
      apply H0.
      assumption.
    - apply H3.
      intro H4.
      apply H1.
      apply H0.
      assumption.
      
   Qed.
  End proof_of_ex9.
  
  (* exercice 10 de la feuille "Logique minimale" *)
  Section Proof_of_weak_Peirce.

    Hypothesis H: (((P->Q)->P)->P)->Q.
    Lemma weak_Peirce : Q.
    Proof.
    Admitted.

  End Proof_of_weak_Peirce.
  Check weak_Peirce.
  Print weak_Peirce. (* Pas facile à déchiffrer *)
  (* QUESTION: si vous n'aviez pas déjà fait cet exercice sur papier, 
     écrivez une preuve papier du même séquent; votre script de preuve
     devrait vous aider à identifier quelle règle utiliser à chaque étape.
  *)

End Exercices.

Section Exercices_bis. (* Les séquents proposés en tests semaine 3 *)  
  Variables P Q R S.
  
  Section Test_mercredi_1.
    Hypothesis H: (P->P)->Q->R.

    Lemma Mercredi1: Q->R.
    Proof.
    Admitted.
  End Test_mercredi_1.

  Section Test_mercredi_2.
    Hypothesis H: P->Q.

    Lemma Mercredi2: (P->Q->R)->P->R.
    Proof.
    Admitted.
  End Test_mercredi_2.

  Section Jeudi_1.
    Hypothesis H:P.

    Lemma Jeudi1: (P->Q)->Q.
    Proof.
    Admitted.
  End Jeudi_1.

  Section Jeudi_2.
    Hypothesis H: Q->R.

    Lemma Jeudi2: ((P->R)->S)->(P->Q)->S.
    Proof.
    Admitted.
  End Jeudi_2.

  Section Vendredi_1.
    Hypothesis H: (P->Q)->R.

    Lemma Vendredi1: P->(Q->R).
    Proof.
    Admitted.
  End Vendredi_1.

  Section Vendredi_2.
    Hypothesis H: P->R.

    Lemma Vendredi2: (P->Q)->(P->R).
    Proof.
    Admitted.
  End Vendredi_2.
End Exercices_bis.
