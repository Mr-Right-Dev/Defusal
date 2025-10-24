# Guia de desarme de bomba
Olá, se você está lendo este manual, você achou uma bomba(?).
Este guia irá como a bomba mostra a sua senha, que será a chave para seu sucesso!

## Conhecendo o hardware
Ela consiste em um visor e um teclado 4x4.

![Visor e teclado](image.png)

* Visor:
    * Tempo restante.
    * Multiplicador do tempo.
    * Senha digitada (2° linha).
* Teclado 4x4:
    * Os numeros são utilizados para a senha.
    * "*" é para apagar o ultimo digito da senha insirida.
    * "#" é para confirmar a senha inserida.
    * As letras não fazem nada.

![LEDs e botão](image-1.png)

* Tem 3 LEDs que serão utilizadas para revelar a senha.
* O botão tambem é utilizado para revelar a senha.

## Obtendo a senha
Para obtela deverá prestar atenção nas instruções.

1° Digito.

* Caso você apertar o botão e a primeira linha não mudar para caracteres differentes, a LED vermelha ira piscar quando o ultimo digito dos segundos for o primeiro digito.
* Caso quando pressionar o botão e ir para caracteres differentes, utilize a tabela para transformalos em numeros.
    * Se o primeiro caracter for um coração a formula é `f(x) = x / (10*2)`
    * Caso for outro a formula é `f(x) = x /(10*0.5)`

2° Digito

* Segurando o botão e quando a led verde piscar ou um caracter diferente aparecer na segunda linha significa o ultimo caracter do segudo é uma parte da senha.
    * Se no multiplicador to timer for `0.00x` (lembrando que 0.00 é um exemplo) for `x`.

| N° do senha | N° da segundo |
|------|-------|
| 0 | 0 |
| 1 | 3 | 
| 2 | 6 | 
| 3 | 9 |
| 4 | 2 |
| 5 | 5 |
| 6 | 8 |
| 7 | 1 |
| 8 | 4 |
| 9 | 7 | 

* Se no multiplicador to timer for `0.00y` (lembrando que 0.00 é um exemplo) for `y`.

| N° do senha | N° da segundo |
|------|-------|
| 0 | 0 |
| 1 | 7 | 
| 2 | 4 | 
| 3 | 1 |
| 4 | 8 |
| 5 | 5 |
| 6 | 2 |
| 7 | 9 |
| 8 | 6 |
| 9 | 3 | 

4 e 3° Digito
* Para obter o valor o digito após `0.00x --` sendo -- dois digitos que é X.
    * Para obter o 3° fassa mod(X, 9) para obte-lo.
    * Para obter o 4° fassa X/9 para obte-lo.