# TM 1

## Exercice 1

### Question 1

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 26, %ecx
        rrmovl %eax, %edx
        addl %ecx, %edx
        halt

```

### Question 2

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 26, %ecx
        rrmovl %eax, %edx
        andl %ecx, %edx
        halt

```
=> Le résultat est 10  
43 = 101011  
26 = 011010  
101011 AND  
011010 =  
001010  
= 8 + 2 = 10

### Question 3

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 26, %ecx
        rrmovl %eax, %ebx
        xorl %ecx, %ebx
        halt

```
=> Le résultat est 49
101011 XOR  
011010 =  
110001  
= 32 + 16 + 1 = 49

## Exercice 2

### Question 1

ZF Flag (Zero Flag) :

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 43, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```

OF Flag (Overflow Flag) :

```y86
        .pos 0
init:   irmovl 0x8fffffff, %eax
        irmovl 0x8fffffff, %ecx
        rrmovl %eax, %ebx
        addl %ecx, %ebx
        halt

```

SF Flag (Sign Flag) :

```y86
        .pos 0
init:   irmovl 26, %eax
        irmovl 43, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```

### Question 2

SF = 1

```y86
        .pos 0
init:   irmovl 1, %eax
        irmovl 43, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```



```y86
        .pos 0
init:   irmovl 1, %eax
        irmovl 0x8fffffff, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```

# TD 2

## Exercice 1
```y86
        irmovl 0, %eax  # sum
        irmovl 1, %ecx  # i <- 1
bcl:    rrmovl %ecx, %edx  # copie de i dans %edx
        isubl 10, %edx
        jg suite  # jg -> ZF = SF = 0 | jl -> SF = 1 | je -> ZF 1 | jne -> ZF = 0
        addl %ecx, %eax
        iadd 1, %ecx
        jmp bcl
suite:
```

## Exercice 2

### Question 1
???

### Question 2
???

### Question 3
```y86
        mrmovl n, %edx
        irmovl 1, %eax  # bit balayage
        xorl %ecx, %ecx  # compteur de bits
bcl:    rrovl %edx, %ebx
        andl %eax, %ebx
        je pasun
        iaddl 1, %ecx
pasun:  addl %eax, %eax  # décalage bit vers la gauche (2x)
        jne bcl
        rmovl %ecx, c
```

## Exercice 3
```y86
        irmovl x, %esi  # p = &x
        mrmovl (%esi), %ebx  # a = *p
        rmmovl %ebx, a  # a = 
        mrmovl b, %ebx  # *p = b
        mrmovl %ebx, (%esi)  # *p = 
        irmovl b, %esi  # p = &b
        mrmovl (%esi), %ebx  # (*p)++
        iaddl 1, %ebx  # ++
        rmmovl %ebx, (%esi)  # 
```

## Exercice 4
```y86
        irmovl t, %esi
        mrmovl n, %ecx  # décompteur
bcl:    isubl 1, %ecx
        jl fin
        mrmovl (%esi), %ebx
        addl 1, %ebx
        rmmovl %ebx, (%esi)
        iaddl 4, %esi  # p++
        jmp bcl
fin:    halt
```

---

# TM 2

## Exercice 1

### Question 1
```y86
        .pos 0
init:   irmovl t, %esi
        mrmovl n, %ecx
        isubl 2, %ecx
bcl:    isubl 1, %ecx
        jl fin
        mrmovl (%esi), %eax
        iaddl 4, %esi
        mrmovl (%esi), %ebx
        addl %eax, %ebx
        iaddl 4, %esi
        rmmovl %ebx, (%esi)
        isubl 4, %esi
        jmp bcl
fin:    halt

        .pos 0x100
n :     .long 16
t:      .long 1
        .long 1


```

---

# TM 3

## Exercice 1

### Question 1
`(a - b) + ((b - c) & (c - d)) -> a b - b c - c d - & +`

### Question 2
`(5 - 19) + ((19 - 10) & (10 - 1)) = -5`

`(V1)`
```y86
        .pos 0
init:   irmovl stack, %esp
        mrmovl a, %eax
        mrmovl b, %ecx
        subl %ecx, %eax
        pushl %eax
        mrmovl b, %eax
        mrmovl c, %ecx
        subl %ecx, %eax
        pushl %eax
        mrmovl c, %eax
        mrmovl d, %ecx
        subl %ecx, %eax
        popl %ecx
        andl %ecx, %eax
        popl %ecx
        addl %ecx, %eax
        halt

        .pos 0x200
stack:  
a:      .long 5
b:      .long 19
c:      .long 10
d:      .long 1

```

## Exercice 2
```y86

```

---

# TM 4

`Impossible en dehors du CREMI (:`

## Exercice 1

### Question 1
```y86

```

---

# TM 5

# Exercice 1
https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wo3ClV/Cj8KaQBTDhcOfN8OZw69gw6YZNzAga0nDk8OEwqpNTMK6w5DDrMKawqZJw5MHwoVRSEfDhsOCTFfCs8OZw6/DnsOhwo8Bw6HCsMObN8O8wp17DnDDr3h5wrnCvRnCjcOIcxLDicKYeBY1TcKjBDFLw7bCsSTDnsO0AsOyWDzCr8KFw6BbcSLCnsOMFMKrwrDCvMKgwp/DhcOPw5HDqMKFw4jDs8KREcKPLMOmw6TDlcOowrDDoAnDgMKvw4tFH35TeRzDrHYDQsOaw6drwrHDn3PDlsOnfsKww67Dg8KZD27DqUMaPMKiTAB/QAhLwo9JwprClcOdRQpnOyB8VsO5CsK8wrXDhsKBAsOlw44nB8OAwo8IbhN5wp/Cs8K9TsOqwovCj0JuwrLDszINRcOEMlhBwqVwFsKsw5TDnxTCocO5QcKdIMKkwpAORWgODAt2QMOpJcKGSV8Uw6fCswjCvsKHLyTCtMOMw5LDqA1uwoHDg8KEw7vCsMO8wqM2HCdFw7gOwqs0woRcdxtyf2DDgE9qwotzABovw4EBGTo4JUfCjnkqw4c+w4TDusOZwqFyVMKDB0xrPjvDicOVEUrDhUNsw5LDn1gTwocHw4XCoTTDowrDsjkXIQ5Dw7MBw4NHf8OUw69JJsO1w7DDh8OIcMORSmPCocO9wqpWbsOEw74mIcOLw7srwrdYYAZJIn3CqWtMfcKtw7fCsm3CuwY5E8KPOsKmQcO4ZsOLw7jDkAIsFnFjwrcqwrszwp1WdsKbNnbCuMKyw7XDgm/DnMK0csOfw5PCvhl9GMOqw63DncO4w63Dik/CrcOqw6HCrUkrYGjDlcO3QsKcw6sQwpvCmsOvwodcN2FSJcK4w5QpEz7CuMOvw7TCoMO4w4A1bsK3bmHDkcO5wo7Cu8O8EsK2ZhrCijRlwqEUWXvCrMK7TBzDqlnDniVpMU8pw6rDtsOcCSXDjcOWw73Cr0vCrVbCqTNcanVSw43DoVLCu1NKwodLwp3Dvy/CnXRKw53CusK0bMOMw63DjcOrPw==

# Exercice 2
https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVVXcKPwppAFH3Dn2TDv8KDwplnw53DgMKACMKmaWLDlSYmXWx2TcOTwqTDqcKDw4rCqMKkw4hYHMK6wprDjcO+w7cOXxHChgPDqsKTeMOuOcKHO3cuw7fCvj8+dDrDpMONw7fDhMKODHXCqmnDnRTDmDF/wrsTZGgXw4Bxw4fDnxbCnAcrfiJDEcOFLMKDRQHDvUrDvnY6w69EwpwPwowMw4lkTD7Cugo2fwXDoMK3w6nCpA5+wo/Cj8K7w7lmw5MQCMOrw7jCgm/CtwHCq8Ojw658UQdHLnjCpQvDkcO5C8OyBMOgTwhCw6rDgQ/Co8K0wrooEsKwDQh8wonCjzNwagnDj2NANz/CmwDDvMKEw4DClS8GR8K2wpVOw7XDoAsXw4vDqDwNw5fDnGMRZFDDgcONCUvDo8KtQSh+wo5PEMKkEG3CssKQOBBMw5gewrnCpzB0w7oaB8OBw4jCg8OncMK5woDCklHDqMK1w6A6aCZcwofDqcOfeBlgJw/Cv2EWwq4hLsKrDXHCt8OhwoJfw6MVw7YBUG8KGsKkwqlxUhwpw4bCocOowrkQwpbCucODw4ghbmwwGXPDmUnDjA4wwpQkwrEMw7/DoBjDnz/DhwEMwo3CghjDosOjwoDCr8KxGcK6H3DDucOoQ8O9w6FHQl5+DwnCilgqTGLCv8KzwpHDq8Kxf8O+wpodw6HDiMOtEsOfwpNPwpLCosOJZznClh3Cq0vDjmRIbcK7S8KCw6XCigUNwqM5wpnDghfCscKewokHRsKmw5bCk8OfQg3Dp3VVTsKrcsKqw5l3w4kNRW7Dnyc3wqtyw4PCuibDj3fDh8OFwqHCnzlQwoNmCcOowqXDozctwprCmsKJVTUxTMOzwrpJwrLCgi4OwoPDjMOBwqJmw70gcFlVw6V2VV4pw6MNckfCkWvDt8OJdcKtwqrCr8O0EF7DgHJVwpfDtHkPwprDvcO8GsKpdsORw4PCrcKuw6jCqcKid8OoFX3CsXxLHnknwppWXgPCp3TChsOKN8K5w6Zhw4jDlsKCR8Olw49yE8OxfW7DtMOkwodJPQQvworDs8OEY8KhwpVywrhwwqnDgnXCmsKpwoZCwrXCm8KpwqZCHTRTw7sKwrUlV8OrdsOqQC3CgcOew47DlcOLXMOaw4zCtVVfwqPCncKrw5/CmMKDwqPDuMO2w5vCqcK3wqYrb8O+ZsOfwpRbNsK2WsK4asKLwrXDucKqLcOWw6bCq8O2WMOBTcKbw7/DscOhw6M/

# Exercice 3
https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVWw5tqw5tAEH0Pw6QfwozCnsKdwqBdXW1Kw4HCjV0INHJJQinClD7DmMOWw5oWVcK0wq7CvGoSQsO+wr3CusKsw5BeRivDpS05M8OneHbDpmh2w58uLyYTw6s5wonDmcORwpojbMObw5MaOMKSw6RwZMOWPGzCgcOzwpE+P1LCmm7DqcKLNWd5QRrCmMK1w5DCr8Oqw5/DicOkw41iwq8nYsONwq3DpcKNw7U+VcKww7UDAH5bLXXDsHtxPsKuw7fDu8KeQMKmw6PCj8O0cEjCicKOR8OrRx1cRMOAT0YgwrrCvsKHNAHDsCcIwoLCqcKnJMOLw6vDrkLCkcKUw6zCgcOAwpfDonwLwpzCusKEw5cFwpDDrn52AcOwEwRuExbCnMOJwqFUw5LCg8O3wpRtw7LDl1XCtsKjMcOJw4EMw4zCqMK7JHXDnBgEw4l3w4ULCGIQw63CkyhxwoDCsCRPwpB6DcKDSl/CizRdw4TDoDkiw4pAw4oiwosNOALDjATDt2HDtcK3w5jCpMKwUgzDv8OCbcK2A8OxwrLDmyAew7UMw7jCocOYw4I6AHTCtQIMw5JnwpwawocYNxnCu8KKQMK4wqwdwozCnMKKXsKDwpXCscKIwrzCsMObExjCqsKKw5hkf8OgGH3CuitSMMK0SAsQwr9Jw6kOFsKDw6YDDB/DulB/JDkrwod/BRHDmlhNwqxiwr/Cm8KVG8KTf8OJwo7CnMOBwpU7wrXCksK4w7zCq0zCscOLwr/Di8K1w6zDmlPDq8K1XMOswqE7wrXDksONwpbCpD3Cq8KZw6/Dj8KOwo8aPgrDvEYAw6FOwqBvw5lqIlgWw4FVNUMiw5Uaw64UwpxGw4HDs8ODRsOBF8OOAS5swpnDrsOKdMKpDSPDqMKeQsK3P0bDt2XCusKDB8OYw5Vlw5XCscKDdsKCw40IMcOyOzp4wq3DicO0UMKhwofDoQDCvcK9fDrCiVkrw4HCjz8TDgBfw6TCgn/CuAFnFcKpInsCGcK8w7PDpcOeIW7DgMOAacK8I1pnRMOrEcK3XsKAwrlxw6wPw7IdwoUfDsOxwqXCrw9xw6NVdsKtJx/Cmj/Cv8OqZSTCsD3CicOtYsOBdsOgG0rCnjxSfMOnDjpHHz3DosOuw7PDuMKnw6vCisOnHyUQw4oCwo7Dq8KaBMOKd8KSw4DDpcOGwpthW8O3DsO0wqLCksOYwpg7L3TCsMK+dcKGw5lIZsKHA2TDmTYYw4vCrkV4w4g2w7rDjsOkw47Dg8K8AE/DtMOOw7jDjcOrw4oqwr49QsKlesKQCRLDnMKFwrXDvcKqQnzDoSzDtcObTcK4wpR2NMOLw4jCjsORXMK8wpfDtjl9w6ITwr1OwrJqLMKMw7LDm8OpwpoWw4wWKsOoUsOxw7hUR0kNw4zCqUhIDcO7U11FdWZORcOjCsOwFFVkTh1Zwqs/XsOVV1Rxf2owXjVUUg3CqsKzw7HCqcOIViswDAHCqcOmw7IHcsOFLiBDc8KRakV3IFcSNngBwqnDhnUMwrnDmsKIPUPCsjY5U8KyOjtkOsKfNj3CgynDqmTDiWvCpsOvXcKbwrXDgRh1wrLDlGZDw6vCsGoMZMKoGcKrw47DgMKmMlRnGMOawow1Z8K0w77CrMOXw6fDpcOFw7t/

`Test du Mux :`  
https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVWXWvDmzAUfR/DtD8EP8Knw4XCulZsJ8KMQcOWZFBYwpPDkcKWURh7SGInMXPCrcOMwpHDl8KWw5LDvz5/w4hYwpLCr2XDt8KtPTrDp8Okw4rDt8OoSm8Xwp9GI8OrOQrDuMORwpoRwrDDrXEJHMODw6hww6TDlsOMwq/CgcOzwpE9PzAWb8OZwos1w6NpFlYwwq/CoV/DhcK/wqPDkcKbw4VfT8KhNcKzFsOXw5bDu1jDg8OWw7cIw7h9wrlowoM/wrLDs3HCvcOfdywkbcO8woEdDnHDmMOGV8Orwoc2OF8hP8K5QsORw7Udw6bCicKAwo8owohST1HCksKWXxdbwonDgz3CssOwNTvDnyDCu8OOw6F1wobDkMOpF8KKwoDCnzFwG3HDrxwecsKnw7bDoh3Do8Kbw7R1wpnDrFgQwqYoAzjCo8KLwrBcNy7CosOiw5vDrAUFAUXCuyxyHBEsw4Inw4zCvcKEUcKnb1kcw48DdB8rw4ZRw4k8CQw4QcOCwoR/wofDpcOfbBPDo04Bw74LN8OJDsOFw7PCr8KNw6LCq8KOBsOfZ1vDnAfCgS7Cl0hAwrrCglPDosKYw6I6w6HClysUw45rR1dOWWfDgMOywrVVw7jDgm9Ow6hSUcOEJsO5woPCr8KxwqfDmyxGwpfDpnHChsOiw5cxw5vDoWZYf8KQw6ZjB8O1Z8KUw7LCvMO5wpfCmMKgXivChcOFw5rDr2rDpAbDocK/aBfCnsORwpE7wrbCoiDDvyvCp8OYw7nDn8O5WMKmw7bDmHrDjQfCu0/Dh1bCvMOZwoZxw4doFsOzwrPDkcKTSk88wrcyIMOQGHQNw5vClgnCqCZQVMOTZ1LCjMOhw4bDgcKpHCbCrl85wrjDkj7DkMKBwq3DisKpKlc+w4MAw7lEwpPDmx/Ck8K7wqrDnMKBHnVxWTVqwq/DrmDDlUIgbiNHwq81VcOua3LDn8OvwpHDl8KXT2Mxwq0tw4TDtsKnw5IGw7rDtk5EAD3Cp8Oqwr3DnMO6AcKfwo7CiMO8eSAab39QD8Kaw57Dr8OTK8KnwofCiMOcFXErO8OnwpvCj0/DscKywpHDlFRRU8KQYsKDwr7CgcOUw44RLXbCtMK3w7PDrcOWwpE6e8Oiw6hRecO/woMMPMOVw4DCocOUZMKQwr9zJMKtw4jDnhTDhMO0wplIw4HDgV5Ewqpaw4TDji/DjsKLPjV6w5Vgwqtqwr9HwqzDhgbCiMKaWgJ9wrERTzDDiQLDlMKDw6fDisOHwr7Dq8OBVjzCgiULwpHCvnzDnsOYw63DvMKhD8OmR8O1I8KIAE7Dq8Omw4l6w7TCpVrCvMOFJMO9RD09wpRKw7rDssOZJsOdRzvCliTDocKOwrNUwr7CksO2KXsSw63CvMKKwpLCoifCnMKJwovDqcKKZcOcwpYqaMKoMMKcw6poVMOPTCUSw5XDr8KmUsONdWrCpsKSYQVMNFdiwqYOwqzDlR3DrsOqasKuw5BNw7XChsK7w7oaw5XDoDodTiXCtsOGdXvCuMOyw4bCiMKhC0QPIsOtw6Eqw4bCpirDtMOYOgZuKwvCpipaLTbCkVvCnTPClcORw6rCncOhwqjClWTDpWMYwo4Fw5FbTQwJKsOJworCsyEYwqAHwoPCmCbCicKeDDDClAF6MiY9XMKlZBNZT8KGwqkIGH5IQcKffmAIBsOoQ8KNGMKGCsOoYw1Mw5vDk8ODDMKmwprDtcORZsKIZ8OJwoVhR8K1w6Q6A8KbV3ApMlvDisObw6zDosOTw7t/