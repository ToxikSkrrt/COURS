(* Logique du premier ordre, version 2024 *)

(** Tactiques :
  pour forall :  
    introduction : 
            intro, intros.
    elimination :
            apply, eapply, specialize.
            (H x ...)

  pour exists : 
     introduction: exists (fournir le terme)
     elimintation: destruct.

  pour = reflexivity (introduction),
         rewrite H   [in HØ] (elimination)
         rewrite <- H [in H0]
                  
 *)

(* tactique maison pour eliminer un forall *)
(* il faut fournir le terme temoin *)

Ltac forall_e H t := (generalize (H t); intro).

(* Compléments sur "specialize": permet de spécialiser
  une hypothèse H (quantifiée universellemnt) en
  fournissant une valeur (terme) pour une ou plusieurs
  variables. Syntaxe:
  specialize H with (x:=t) 
     va remplacer H par "H appliquée à t", la variable x
     est remplacée par t
  specialize H with (x:=t) as H0
     similaire mais laisse H inchangée, on obtient une
     nouvelle hypothèse H0
     
  Au final c'est plus souple que forall_e, en particulier
  quand H a plusieurs variables quantifiées
  universellemnet. 
  *)


(* Exemple *)

Example E0 : ~(forall x:nat, x <> x).
Proof.
  intro H.                                       
  forall_e H 42.
  unfold not in H0.
  apply H0.
  reflexivity.
Qed.

Section Syllogismes. (* Entrainements *)
Variable Etre: Type.
Variables humain mortel animal : Etre -> Prop.

Variable Socrate : Etre.
Variable Rhino : Etre.

Hypothesis HM : forall x,  humain x -> mortel x.
Hypothesis HSocrate : humain Socrate.
Hypothesis Etre_disj : forall x:Etre,  humain x \/ animal x.
Hypothesis Hrhino : ~ humain Rhino.

Lemma Syllogisme :  mortel Socrate.
Proof.
apply HM. (* elimination du forall et modus-ponens *)
assumption.
Qed.

Lemma contraposee : forall x, ~ mortel x -> ~ humain x.
Proof.  
intros x Hx H.
unfold not in Hx.
apply Hx.
apply HM; assumption.
Qed.    

Lemma Lmortel: exists x, mortel x.
Proof.  
exists Socrate.  (* introduction de l'existentiel *)
apply Syllogisme. (* On peut appliquer un théorème déjà prouvé *)  
Qed.

Lemma Lanimal: exists x, animal x.
Proof.  
exists Rhino.
destruct (Etre_disj Rhino).
(* elimination sur la disjonction "Etre_disj" appliquée à Rhino *)
- contradiction.
- assumption.
Restart. (* On utilise forall_e *)
exists Rhino.
forall_e Etre_disj Rhino.
destruct H as [hR|aR].
- contradiction. (* entre Hrhino et hR *)
- assumption. 
Qed.

Lemma L : ~(exists x:Etre,  ~ humain x /\ ~ animal x).
Proof.
intro H.
destruct H as [e He]. (* elimination de l'existentiel *)
destruct He.
forall_e Etre_disj e.
destruct H1.
- contradiction.
- contradiction.
Qed.

End Syllogismes.

Section Egalite. (* Entrainements, sur l'egalite *) 
Variable A : Type.
Variable f : A -> A.

Lemma Egal1 : forall x:A, exists y: A, x=y.
Proof.
intros x.
exists x.
reflexivity. 
Qed.

Lemma Egal2 : forall x y z: A, x = y -> y = z -> x = z.
Proof.
intros x y z H H0.
rewrite H.
assumption.
Qed. 

(* x <> y est une abréviation de ~ (x = y) *)
(* "unfold not" va faire apparaître l'implication vers False *)

Lemma diff_eq : forall x y z:A, x <> y -> y = z -> x <> z.
Proof.  
intros.
rewrite H0 in H.
assumption. 
Qed.
  
(* À vous ! *)
Lemma Egal3 : forall x y z: A , x = y -> x <> z -> z <> y.
Proof.
intros.
intro.
destruct H0.
rewrite H.
rewrite H1.
reflexivity.
Qed.

Lemma L4 : forall x y:A, f x <> f y -> x <> y.
Proof.
intros.
intro.
destruct H.
rewrite H0.
reflexivity.
Qed.

End Egalite.

(* Quelques preuves de logique du premier ordre *)

(* Supprimer les "Admitted" (on admet la preuve complète) et 
  les "admit" (on admet le but courant) dans toutes les preuves
  qui suivent, les compléter et le terminer par "Qed." *)

Section QuelquesPreuves.
Variable A B: Type.
Variables P Q : A -> Prop.
Variable R : A -> B -> Prop.
Variable X : Prop.

Lemma Question1 : (forall x:A, P x /\ Q x) <->
                  (forall x:A, P x) /\ (forall x:A, Q x).
Proof.
split ; intros.
- split ; intros.
  + apply H.
  + apply H.
- split.
  + apply H.
  + apply H.
Qed.

Lemma Question2 : (forall x, P x) \/ (forall x, Q x) ->
                  forall x, P x \/ Q x.
Proof.
intros.
destruct H.
- left.
  apply H.
- right.
  apply H.
Qed.
  
Lemma Question3 : (exists x:A, P x /\ Q x) ->
                  (exists x:A, P x) /\  (exists x:A, Q x).
Proof.
intros.
split ; intros.
- destruct H.
  exists x.
  apply H.
- destruct H.
  exists x.
  apply H.
Qed.

Lemma Question4 : (exists x:A, P x \/ Q x) <->
                  (exists x:A, P x) \/   (exists x:A, Q x).
Proof.
split ; intros.
- destruct H.
  destruct H.
  + left.
    exists x.
    assumption. 
  + right.
    exists x.
    assumption.    
- destruct H.
  + destruct H.
    exists x.
    left.
    assumption.
  + destruct H.
    exists x.
    right.
    assumption.
Qed.

Section Question5.
  Hypothesis H : forall x, P x -> Q x.
  Hypothesis H0 : exists x, P x.

  Lemma L5 : exists x, Q x.
  Proof.
  destruct H0.
  exists x.
  forall_e H x.
  apply H2.
  assumption.
  Qed.

End Question5.
 
(* Attention au parenthésage *)
Lemma Question6 : forall x,  P x -> exists y,  P y.
Proof.
intros.
exists x.
assumption.
Qed.
 
Lemma Question7 : ~(exists x, P x) <-> forall x, ~ P x.
Proof.
split ; intros.
- intro.
  apply H.
  exists x.
  assumption.
- intro.
  destruct H0.
  forall_e H x.
  apply H1.
  assumption.                       
Qed.

(* Ici, X joue le rôle de n'importe quelle proposition où x n'est
   pas libre *)
Lemma Question8 : ((exists x, P x) -> X) <->
                   forall x, P x -> X.
Proof.
Admitted.

Lemma Question9 :  (exists x:A, forall y:B, R x y)
                    -> (forall y:B, exists x:A, R x y).
Proof. 
Admitted.

(* Sur l egalite *)
Lemma eq_sym : forall x y:A, x = y -> y = x.
Proof.
intros x y H.
rewrite H.     
reflexivity.
Qed.

Lemma eq_trans : forall x y z:A, x = y -> y = z -> x = z.
Proof.
Admitted.

End QuelquesPreuves.

Section TypeVide.
(* Dans cette section, on envisage la possibilité que le type A
  soit vide *)
Variable A: Type.
Variable P: A->Prop.

Definition A_est_vide := forall x:A, x <> x.
(* Attention, on n'affirme pas que A est vide; on définit une
  formule qui dit que A est vide (mais on ne la prouve pas)  *)

(* "Si A est vide, alors les éléments de A ont toutes les
  propriétés" *)
Lemma TV1 : A_est_vide -> forall x:A, P x.
Proof.
unfold A_est_vide. (* A compléter *)
Admitted.

Lemma TV2 : (forall x y:A, x <> y) -> A_est_vide.
Proof.
Admitted.

End TypeVide.


(* On passe maintenant en logique classique *)
Require Import Classical.

(* Nouvelles tactiques:
  classical_left
  classical_right
    permettent de prouver un but "A\/B" en choisissant
    de prouver A (left) ou B (right), mais on récupère
    ~B (left) ou ~A (right) comme hypothèse *)

Section classic.
Variable A: Type.
Variables P Q: A->Prop.

(* "add_exm P" fait apparaître une hypothese P\/~P *)
Ltac add_exm  P :=
let hname := fresh "exm" in
assert(hname : P \/ ~P); [classical_right; assumption|].

(* absurdK: applique le raisonnement par l'absurde classique 
  Transforme un but  "Gamma |- P " en 
                     "Gamma, ~P |- False" *)
Ltac absurdK :=
  match goal with |- ?X =>
     let hname := fresh "exm" in
        assert(hname := classic X);
        destruct hname;[assumption| elimtype False]
  end.

Lemma Classical_Question1 : ~ (forall x, P x) <-> exists x, ~ P x.
Proof.   
split; intro H.
- absurdK.
  Admitted. (* finir la preuve; l'autre sens est intuitionniste *)

(* Dans le même esprit *)
Lemma Classical_Question2: 
  ~(forall x, P x /\ Q x) <-> exists x, ~ P x \/ ~ Q x.
Proof.
Admitted.

(* On complète la section "TypeVide", mais en classique *)
(* Pour des raisons techniques, le type s'appelle B *)

Section TypeVideClassique.
Variable B: Type.
Variable PP: B->Prop.

Definition B_est_vide := forall x:B, x <> x.

Hypothesis H : ~ B_est_vide.
Hypothesis H0 : forall x:B, PP x.
    
Lemma forall_to_exists : exists x:B, PP x. (* difficile *)
Proof.
unfold B_est_vide in H.
assert (exists x:B, x = x).
{  absurdK.
  admit.
}
Admitted. (* Compléter la preuve, y compris le "admit" *)

End TypeVideClassique.
    
Section DrinkersProblem. (* Problème du buveur *)
(* On se place en logique classique: on reprend donc le tiers exclus
  et l'absurde classique *)

(* On va prouver le théorème CLASSIQUE suivant: dans un bar qui contient
  au moins une personne (le patron), il existe une personne qui, si elle
  boît, tout le monde boit *)

(* Attention au semi-piège: ce n'est pas forcément le patron *)

Variable people : Type.
Variable patron : people.

Variable boit : people -> Prop.
Theorem buveurs :
  exists p:people, (boit p -> forall q, boit q).
Proof.
add_exm (forall q, boit q).
Admitted. (* Comme précédemment: compléter la preuve *)

End DrinkersProblem.
End classic.


 
