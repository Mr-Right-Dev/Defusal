# Guia para Desarme de Bomba

Se você está lendo este manual, significa que encontrou uma bomba. Este guia irá ajudá-lo a entender como a bomba revela a sua senha, chave para seu sucesso.

---

## Conhecendo o Hardware

### Visor
- **1ª linha:** Tempo restante (segundos) e multiplicador do tempo (`0.00x` ou `0.00y`).
- **2ª linha:** Senha digitada.

### Teclado 4x4
- **Números:** Digite a senha.
- **`*`**: Apaga o último dígito.
- **`#`**: Confirma a senha.
- **Letras:** Não têm função.

### LEDs e Botão
- **3 LEDs** indicam o status do processo.
- O **botão** é utilizado para revelar partes da senha.

---

## Como Obter a Senha

A senha é composta por **4 dígitos**. Siga os passos abaixo:

---

### 1º Dígito

1. Pressione o **botão** uma vez.
2. Observe a **1ª linha** do visor:
   - **Se não mudar para caracteres diferentes**:
     - A **LED vermelha** piscará quando o **último dígito dos segundos** for igual ao 1º dígito da senha.
   - **Se mudar para caracteres diferentes**:
     - Use a tabela para transformar os caracteres em números:
       - **Coração (♥)**: `f(X) = X / 20`.
       - **Outro símbolo**: `f(X) = X / 5`.
     - O valor de `X` é o número representado pelos caracteres. Aplique a fórmula e use a **parte inteira** como o 1º dígito.

---

### 2º Dígito

1. **Segure o botão** e observe:
   - Se a **LED verde** piscar ou aparecer **um caractere diferente na 2ª linha**, o último dígito dos segundos será parte da senha.
2. Determine qual tabela usar dependendo do multiplicador do timer:
   - **Multiplicador `0.00x`**: Use a **Tabela A**.
   - **Multiplicador `0.00y`**: Use a **Tabela B**.

#### Tabela A (quando multiplicador é `0.00x`)

| Dígito da Senha | Último Dígito dos Segundos |
|-----------------|----------------------------|
| 0               | 0                          |
| 1               | 3                          |
| 2               | 6                          |
| 3               | 9                          |
| 4               | 2                          |
| 5               | 5                          |
| 6               | 8                          |
| 7               | 1                          |
| 8               | 4                          |
| 9               | 7                          |

#### Tabela B (quando multiplicador é `0.00y`)

| Dígito da Senha | Último Dígito dos Segundos |
|-----------------|----------------------------|
| 0               | 0                          |
| 1               | 7                          |
| 2               | 4                          |
| 3               | 1                          |
| 4               | 8                          |
| 5               | 5                          |
| 6               | 2                          |
| 7               | 9                          |
| 8               | 6                          |
| 9               | 3                          |

- **Como usar a tabela:** Leia o último dígito dos segundos e mapeie para o dígito da senha usando a tabela correspondente.

---

### 3º e 4º Dígitos

1. Quando aparecer a sequência `0.00x --` (onde `--` são dois dígitos juntos), esses dois dígitos formam **X** (um número entre 00 e 99).
2. **3º dígito** = **parte inteira** de `X / 9`.
3. **4º dígito** = `X mod 9` (resto da divisão de X por 9).

#### Exemplo:
Se `X = 47`:
- **3º dígito** = `47 / 9 = 5` (parte inteira).
- **4º dígito** = `47 mod 9 = 2` (resto).

Portanto, para `X = 47`, os 3º e 4º dígitos são:
- **3º dígito = 5**.
- **4º dígito = 2**.

---

## Confirmando a Senha

1. Digite os 4 dígitos da senha no teclado numérico.
2. Use **`*`** para apagar se cometer um erro.
3. Pressione **`#`** para confirmar a senha.

---

## Dicas Rápidas

- O **último dígito dos segundos** é sempre o dígito das unidades do contador (ex.: 123 s → último dígito = `3`).
- Para o cálculo de `X`, use os dois dígitos próximos ao multiplicador (ex.: `0.00x --`).
- Use **divisão inteira** para o 3º dígito e **resto** para o 4º.

---

Se precisar de mais exemplos ou ajuda, estou à disposição!
