Require Import Setoid.

(* forall_e Hypothese t: introduit une nouvelle hypothèse qui est ce 
   qu'on obtient quand on applique Hypothese de la forme
   forall x:T, ...
   au terme t:T   *)
Ltac forall_e H x:= generalize (H x); intro.

(* Alternativement:
   specialize Hypothese with t
   specialize Hypotheses with (x:=t)
   specialize Hypothese with t as Ht
   specialize Hypothese with (x:=t) as Ht
   les deux premières formes remplacent l'hypothèse;
   specifier la variable à lier avec (x:=t) permet de sélectionner
   la variable x s'il y a plusieurs quantificateurs consécutifs,
   forall z y x, ...  *)

Section Universite.

(* Prenez le temps de vous familiariser avec les hypothèses, et de les
   interpréter mentalement: cela vous aidera pour vos preuves *)

Variable cours: Type.
Variable individu: Type.

Variables etudiant professeur: individu -> Prop.

Variable connait: individu -> individu -> Prop.
Variables enseigne etudie: individu -> cours -> Prop.

Variables Alice Bob Charlie Diana: individu.
Variable Anglais: cours.

Hypothesis Huniv: forall x, professeur x \/ etudiant x.
Hypothesis Hetud_prof: forall c x y, enseigne x c -> etudie y c -> connait y x.
Hypothesis cours_pas_vide: forall c, exists y, etudie y c/\ ~professeur y.
Hypothesis cours_prof: forall c, exists x, enseigne x c.
Hypothesis enseignant: forall c x, enseigne x c -> professeur x.
Hypothesis All_english: forall x, etudiant x -> etudie x Anglais.
Hypothesis Etud_se_connaissent: forall x y c, etudie x c -> etudie y c -> connait x y.

Hypothesis Ha: etudiant Alice.
Hypothesis Hb: ~ professeur Bob.
Hypothesis Hc: forall x, connait x Charlie -> professeur x.
Hypothesis Hac: connait Alice Charlie.
Hypothesis Hd: enseigne Diana Anglais.

(* Un exemple *)

Lemma Exemple: etudiant Bob.
Proof.
  forall_e Huniv Bob.
  destruct H.
  - contradiction.
  - assumption.
Qed.

(* Les exercices commencent ici *)

(* Dans chaque Lemme, remplacer "Admitted" par votre propre script de preuve.
   N'oubliez pas de terminer chaque preuve par "Qed". *)

Lemma Exercice1: connait Alice Diana.
Proof.
specialize Hetud_prof with (c:=Anglais) (x:=Diana) (y:=Alice).
(* forall_e Hetud_prof Anglais.
forall_e H Diana.
forall_e H0 Alice. *)
apply Hetud_prof.
- forall_e All_english Diana.
  assumption.
- forall_e All_english Alice.
  apply H ; assumption.
Qed.

Lemma Exercice2: connait Alice Bob.
Proof.
(* specialize Etud_se_connaissent with (c:=Anglais) (x:=Alice) (y:=Bob). *)
specialize Etud_se_connaissent with Alice Bob Anglais.
apply Etud_se_connaissent.
- forall_e All_english Alice.
  apply H.
  assumption.
- forall_e Huniv Bob.
  destruct H.
  + contradiction.
  + forall_e All_english Bob.
    apply H0.
    assumption.
Qed.

Lemma Exercice3: exists x, professeur x /\ forall y, etudiant y -> connait y x.
Proof.
exists Diana.
split.
- specialize enseignant with (c:=Anglais) (x:=Diana).
  apply enseignant.
  assumption.
- intros.
  specialize Hetud_prof with (c:=Anglais) (x:=Diana) (y:=y).
  apply Hetud_prof.
  + assumption.
  + forall_e All_english y.
    apply H0.
    assumption.
Qed.

Lemma Exercice4: forall x y, professeur x \/ professeur y \/ connait x y.
Proof.
intros.
forall_e Huniv y.
forall_e Huniv x.
forall_e Etud_se_connaissent x.
forall_e H1 y.
forall_e H2 Anglais.
destruct H.
+ right.
left. assumption.
+ destruct H0.
left. assumption.
right. right.
apply H3.
-- apply All_english. assumption.
-- apply All_english. assumption.
Qed.

Lemma Exercice5: exists x, professeur x /\ etudiant x.
Proof.
exists Alice.
split.
- forall_e Hc Alice.
  apply H.
  assumption.
- assumption.
Qed.

Lemma Exercice6: forall c, ~enseigne Charlie c.
Proof.
intro.
intro.
forall_e cours_pas_vide c.
destruct H0.
destruct H0 as [e np].
apply np. 
forall_e Hc x.
apply H0.
forall_e Hetud_prof c.
specialize H1 with (y:=x)( x:=Charlie).
apply H1.
- assumption.
- assumption.
(* apply H1; assumption. *)
Restart.
intro.
intro.
forall_e cours_pas_vide c.
destruct H0.
destruct H0.
apply H1.
forall_e Hc x.
apply H2.
specialize Hetud_prof with c Charlie x.
apply Hetud_prof.
- assumption.
- assumption.
Qed.

End Universite.

(* Fin des exercices *)
