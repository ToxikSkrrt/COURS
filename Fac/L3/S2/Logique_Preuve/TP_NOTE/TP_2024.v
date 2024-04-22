(* TP Logique et Preuve, 2024 *)
Require Import Setoid.

Ltac forall_e H t := generalize (H t); intro.

(* Rappel de tactiques
  assumption: règle d'hypothèse
  intro, intros:  introduction de l'implication; introduction du forall
  split: introduction de la conjonction
  left, classical_left: introduction (gauche) de la disjonction
  right, classical_right: introduction (droite) de la disjonction
  reflexivity: introduction de l'égalité
  unfold not: expansion de la macro "not" (~)
  apply: modus ponens (élimination de l'implication), application d'un théorème
  destruct: élimination de la conjonction, de la disjonction, du "exists"
  exfalso: élimination de la contradiction
  forall_e, specialize: élimination du "forall"
  assert: coupure
  rewrite: élimination de l'égalité (réécriture), ou réécriture d'une
    équivalence

  contradiction: prouve n'importe quel but si les hypothèses incluent une proposition
    et sa négation
*)
  

Section Test.
(* Le test consiste à prouver les cinq lemmes E1, E2, E3, E4
   et E5. Après chaque preuve, remplacer Admitted. par Qed.

   De nouvelles hypothèses, qui compliquent un peu le "monde"
   modélisé, sont ajoutées entre E4 et E5; elles ne s'appliquent
   qu'à E5.
*)

Variable plat: Type.

Variables entree principal dessert: plat -> Prop.
Variables sucre sale: plat -> Prop.

Hypothesis Htype: forall p, entree p \/ principal p \/ dessert p.
Hypothesis Hep: forall p, ~ (entree p /\ principal p).
Hypothesis Hpd: forall p, ~ (principal p /\ dessert p).
Hypothesis Hed: forall p, ~ entree p \/ ~ dessert p.

Hypothesis Hsucre_sale: forall p, sucre p \/ sale p.
Hypothesis Hsale: ~ (exists p, sale p /\ dessert p).

Lemma E0: forall p, ~ (entree p /\ dessert p).
Proof.
intros p Hp.
destruct Hp as [Hpp Hdp].
forall_e Hed p.
destruct H as [Hnp | Hnd].
- contradiction.
- contradiction.
Qed.

Lemma E1: forall p, dessert p ->  ~ principal p.
Proof.
intros p Hdp Hpp.
forall_e Hpd p.
apply H.
split ; assumption.
Qed.


Lemma E2: forall p, sale p -> entree p \/ principal p.
Proof.
intros p Hsp.
forall_e Htype p.
destruct H as [H1 | H2].
- left ; assumption.
- destruct H2 as [H1 | H2].
  * right ; assumption.
  * exfalso.
    apply Hsale.
    exists p.
    split ; assumption.
Qed.


Lemma E3: (exists p, sucre p /\ sale p) -> ~ (forall p, dessert p).
Proof.
intros Hsupandsap Hdp.
destruct Hsupandsap.
destruct H as [Hsux Hsax].
apply Hsale.
exists x.
split.
- assumption.
- forall_e Hdp x.
  assumption.
Qed.

Lemma E4: forall p, sale p -> ~ entree p -> principal p.
Proof.
intros p Hsp Hnep.
forall_e Htype p.
destruct H as [H1 | H2].
- contradiction.
- destruct H2 as [H0 | H1].
  + assumption.
  + exfalso.
    apply Hsale.
    exists p.
    split ; assumption.
Qed.

(* On ajoute un peu de complexité au monde *)

Variable personne: Type.
Variable mange: personne -> plat -> Prop.
Variable Gargantua: personne.
Variable Becsucre: personne.
Variable Tartare: plat.
Hypothesis Ht: principal Tartare.
Hypothesis Hgarg: forall p, mange Gargantua p.
Hypothesis Hbec: forall p, mange Becsucre p <-> dessert p. 


Lemma E5: ~ (Gargantua = Becsucre).
Proof.
intro HGeqB.
forall_e Hpd Tartare.
apply H.
split.
- assumption.
- forall_e Hbec Tartare.
  apply H0.
  forall_e Hgarg Tartare.
  rewrite <- HGeqB.
  assumption.
Qed.

End Test.



