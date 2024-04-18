(* Listes triées, tri de listes, tri par insertion. *)
(* Modélisation et preuves: Philippe Duchon 2023, 
   d'après Pierre Castéran et Yves Bertot *)
Require Extraction.
Require Import List.
Set Implicit Arguments.

(* Par rapport à la version du cours: les listes sont les
   "vraies" listes Coq, avec des notations proches de celles
   de Ocaml pour la liste vide [] et :: pour le constructeur
   "cons" *)

Section SortedList.
(* Modélisation de la propriété "être une liste
   triée" *)

Variable T: Type.
Variable cmp: T->T->bool.

(* Une liste est triée pour une certaine définition
   de l'ordre croissant, qui est représenté par une
   fonction de type T->T->bool; cette fonction doit avoir
   une propriété de "complétude" (on veut un "ordre total") *)

Definition COMPLETE (f: T->T->bool):= forall x y, 
  (f x y = true) \/ (f y x = true).

(* Un "ordre" a en plus la propriété de transitivité;
  il se trouve que ce n'est pas nécessaire pour le
  tri par insertion (mais ça l'est pour d'autres tris) *)
Definition TRANSITIVE (f: T->T->bool):= forall x y z, 
  (f x y = true) -> (f y z = true) -> (f x z = true).

(* Normalement, la reflexivité est un prérequis pour
  définir un ordre; c'est une conséquence de la
  complétude *)
Lemma reflexive: forall (f: T->T->bool), 
  COMPLETE f -> forall x, f x x = true.
Proof.
unfold COMPLETE.
intros f Hcomp x.
destruct (Hcomp x x) as [H|H]; assumption.
Qed.

(* On définit ce qu'est une liste triée; il y a 
  trois cas selon que la liste est vide, ou ne
  contient qu'un seul élément, ou en contient au
  moins deux; le dernier cas est récursif. *)
Inductive SORTED (f: T->T->bool): list T -> Prop :=
| sorted0: SORTED f nil
| sorted1: forall x:T, SORTED f (x::nil)
| sorted2: forall (x y:T) (L: list T), 
  (f x y = true) -> SORTED f (y::L) 
  -> SORTED f (x::y::L).

(* On montre quelques "lemmes d'inversion" sur les 
  listes triées, i.e. des conséquences du fait 
  qu'une liste est triée *)
Lemma sorted_tail: forall x L, 
  SORTED cmp (x::L) -> SORTED cmp L.
Proof.
  intros x L H; inversion H.
  - apply sorted0.
  - assumption.
Qed.

Lemma sorted_head: forall x y L, 
  SORTED cmp (x::y::L) -> cmp x y = true.
Proof.
intros x y L H.
inversion H.
assumption.
Qed.

Lemma sorted_doubletail: forall x y L, 
  SORTED cmp (x::y::L) -> SORTED cmp L.
Proof.
intros x y L H. inversion H.
apply sorted_tail with (x:=y); assumption.
Qed.

End SortedList.

(* Pour prouver que le tri par insertion est correct,
  il ne suffit pas de prouver qu'il produit une liste
  triée (sinon la fonction qui retourne la liste vide
  serait une fonction de tri); il faut prouver que le
  résultat contient les mêmes valeurs que la liste de
  départ. On modélise donc le fait que deux listes
  soient des permutations l'une de l'autre *)

Section PermutationList.

Variable T: Type.

(* Deux listes sont "transposées" l'une de l'autre si
  elles diffèrent seulement par l'échange de deux
  éléments consécutifs *)
Inductive transpo: list T -> list T -> Prop :=
| transpo_head: forall x y L, 
    transpo (x::y::L) (y::x::L)
| transpo_tail: forall x L L', 
    transpo L L' -> transpo (x::L) (x::L')
.

(* C'est une relation symétrique (on ne s'en servira
  pas) *)
Lemma transpo_sym: forall L L', 
  transpo L L' -> transpo L' L.
Proof.
intros L L' H.
destruct H.
- apply transpo_head.
- apply transpo_tail. 
(* Échec: l'hypothèse H0 ne suffit pas, elle est dans
  le mauvais sens (alors qu'on est précisément en
  train de prouver que le sens ne compte pas). Au
  lieu d'une preuve par cas (destruct), on aurait dû
  faire une preuve par induction (induction). *)
Restart.
intros L L' H.
induction H.
- apply transpo_head.
- apply transpo_tail. assumption.
Qed.

(* On définit maintenant le propriété "être des
  listes permutées l'une de l'autre", à partir de
  la notion de transposition. Formellement, cela
  correspond à la notion de clôture transitive *)
Inductive perm: list T -> list T -> Prop :=
| perm_id: forall L, perm L L
| perm_transpo: forall L1 L2,
    transpo L1 L2 -> perm L1 L2
| perm_closure: forall L1 Lm L2, 
    transpo L1 Lm -> perm Lm L2 -> perm L1 L2
.

(* On a fait le choix, dans le constructeur 
  perm_closure, de mettre la condition
  "transpo L1 Lm", mais on aurait aussi pu mettre
  "perm L1 Lm". On justifie ici que cette version
  affaiblie est vraie aussi. *)
Lemma perm_tran: forall L1 Lm L2,
  perm L1 Lm -> perm Lm L2 -> perm L1 L2.
Proof.
intros L1 Lm L2 H; generalize L2; induction H.
- trivial.
- intros L3 H1. 
  apply perm_closure with (Lm:= L0); assumption.
- intros L3 H1; apply perm_closure with (Lm := Lm).
  * assumption.
  * apply IHperm; assumption.
Qed.

(* La relation "perm" est stable par ajout d'une même
  valeur en tête *)
Lemma perm_tail: forall x L L', 
  perm L L' -> perm (x::L) (x::L').
Proof.
intros x L L' H. induction H.
- apply perm_id.
- apply perm_transpo; apply transpo_tail; assumption. 
- apply perm_closure with (Lm:= (x::Lm)).
  + apply transpo_tail; assumption.
  + assumption.
Qed. 

End PermutationList.
(* Les préliminaires sont terminés, on va pouvoir
  passer au tri par insertion. *)

(* On spécifie ce que c'est qu'une fonction de tri *)
Definition SORT_SPEC (T: Type) (cmp: T->T->bool) 
  (f: list T -> list T) := 
  forall L, perm L (f L) /\ SORTED cmp (f L).

(* La propriété
   SORT_SPECT T cmp f
   énonce que pour le type T, pour la fonction de
   comparaison cmp, la fonction f est une fonction de tri *)


(* On va définir le tri par insertion, de manière
  générique (le type des valeurs, et la fonction de
  comparaison, sont des paramètres) *)
Section TriInsertion.

Variable T: Type.
Variable cmp: T->T->bool.

(* Hypothesis cmp_t: TRANSITIVE cmp. *)
Hypothesis cmp_c: COMPLETE cmp.

(* On procède en deux temps: d'abord on définit la
  fonction d'insertion, et on prouve ses propriétés;
  puis on définit la fonction de tri par insertion,
  et on prouve ses propriétés. *)
Section Insertion.
(* La fonction d'insertion *)
Fixpoint insert (x:T) (L: list T) :=
  match L with
  | nil => x::nil
  | y::L' => if (cmp x y) then x::L
             else y::(insert x L')
  end.

(* Un petit lemme d'inversion sur la fonction de 
  comparaison *)
Lemma cmp_rev: forall x y, 
  cmp x y = false -> cmp y x = true.
Proof.
intros x y H; destruct (cmp_c x y) as [H0|H0].
- rewrite H in H0; discriminate.
- assumption.
Qed.

(* On commence par prouver que la fonction 
  d'insertion a une propriété de type permutation *)
Lemma insert_perm: forall x L, 
  perm (x::L) (insert x L).
Proof.
intros x L; induction L.
- apply perm_id.
- destruct (cmp x a) eqn:Hxa; simpl.
  + rewrite Hxa. apply perm_id. 
  + rewrite Hxa. 
    apply perm_closure with (Lm := a::x::L).
    * apply transpo_head. 
    * apply perm_tail. assumption.
Qed.

(* Un petit lemme sur insert: quand on insère une
  valeur dans une liste non vide, la tête de la
  liste résultat est soit la valeur insérée, soit
  la tête de la liste dans laquelle on insère *)
Lemma insert_head: forall x y L, exists L', 
  insert x (y::L) = x::L' \/ insert x (y::L) = y::L'.
Proof.
intros x y L.
destruct (cmp x y) eqn: Hxy.
- exists (y::L). left. simpl; now rewrite Hxy.
- exists (insert x L); right; simpl; now rewrite Hxy.
Qed.

(* Le lemme principal: quand on insère dans une liste
  triée, le résultat est trié. *)
Lemma insert_sorted: forall x L, 
      SORTED cmp L -> SORTED cmp (insert x L).
Proof.
intros x L; generalize x.
induction L.
- intros x0 H; apply sorted1.
- intros x0 Hal.
  case_eq (cmp x0 a).
  + intro Hxa. simpl. rewrite Hxa.
    apply sorted2.
    * assumption.
    * assumption.
  + intro Hxa. simpl. rewrite Hxa.
    assert (Hx0L: SORTED cmp (insert x0 L)).
    { apply IHL. 
    apply sorted_tail with (x:=a); assumption. } 
    destruct L as [ | y L'].
    * simpl. apply sorted2.
      -- unfold COMPLETE in cmp_c.
         destruct (cmp_c a x0).
         assumption. rewrite Hxa in H. discriminate H.
      -- apply sorted1.
    * destruct (insert_head x0 y L') as [L'' [Hl|Hl]].
      -- rewrite Hl; apply sorted2.
        ++ apply cmp_rev; assumption.
        ++ rewrite <- Hl. apply IHL.
           apply sorted_tail with (x:=a). assumption.
      -- rewrite Hl. apply sorted2.
        ++ apply sorted_head with (L:=L'). assumption.
        ++ rewrite <- Hl. 
           apply IHL. apply sorted_tail with (x:=a).
           assumption.
Qed.
(* C'est bien lourd! J'ai dû merder... mais ça marche *)

End Insertion.

(* On est maintenant prêt pour définir la fonction de
  tri par insertion, et prouver sa propriété 
  principale (c'est une fonction de tri) *)
Fixpoint insert_sort L := match L with 
  | nil => nil
  | x::L' => insert x (insert_sort L')
end.

Lemma perm_insert_sort: forall L, 
  perm L (insert_sort L).
Proof.
intros L; induction L.
- apply perm_id.
- unfold insert_sort; simpl; fold insert_sort.
  apply perm_tran with (Lm := a::insert_sort L).
  + apply perm_tail; assumption.
  + apply insert_perm.
Qed.

Lemma insert_sort_sorted: forall L, 
  SORTED cmp (insert_sort L).
Proof.
intros L; induction L.
- apply sorted0.
- unfold insert_sort; simpl; fold insert_sort.
  apply insert_sorted. assumption.
Qed.

(* Le théorème principal: on a une fonction de tri. *)
(* (à ce stade, c'est une formalité) *)
Theorem SORT_insert_sort: SORT_SPEC cmp insert_sort.
Proof.
unfold SORT_SPEC.
intro L; split.
- apply perm_insert_sort.
- apply insert_sort_sorted.
Qed.

End TriInsertion.

Check insert_sort.
Check SORT_insert_sort.
(* Aussi bien le programme insert_sort, et le théorème
   SORT_insert_sort, dépendent du type T et de la fonction
   cmp, qui étaient des paramètres dans la section *)


(* Extraction de programmes Ocaml, en utilisant
   les types de base "bool" et "list" *)
Extraction Language OCaml.
Extract Inductive list => "list" [ "[]" "(::)" ].
Extract Inductive bool => "bool" [ "true" "false" ].
Recursive Extraction insert_sort.
Extraction "sort" insert_sort.
