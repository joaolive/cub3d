# 📋 PLANO DE AÇÃO - ISSUE 1: Sistema de Parsing do Arquivo .cub

**Status:** ⏳ FASE 3 EM ANDAMENTO
**Data:** 17/01/2026

---

## ✅ FASES CONCLUÍDAS

### FASE 1: Estrutura e Leitura ✅
- ✅ Diretório criado
- ✅ Headers e arquivos base
- ✅ Funções utilitárias

### FASE 2: Extractors ✅
- ✅ `extract_textures()` completo
- ✅ `extract_colors()` com parse RGB→RGBA
- ✅ `extract_map()` com limpeza de quebras
- ✅ `color_parser.c` implementado
- ✅ Compilação OK

---

## 🎯 OBJETIVO DA ISSUE

Implementar um sistema robusto de leitura, parsing e validação de arquivos `.cub` que:

1. **Leia e extraia** todos os elementos do arquivo:
   - 4 texturas (NO, SO, WE, EA)
   - Cores RGB do chão (F) e teto (C)
   - Mapa 2D com jogador e paredes

2. **Valide todos os elementos** contra as regras do projeto:
   - Apenas caracteres válidos: `0`, `1`, `N`, `S`, `E`, `W` (e espaços)
   - Mapa fechado (cercado por paredes)
   - Exatamente um jogador no mapa
   - Cores RGB entre 0-255
   - Caminhos de textura válidos

3. **Trate erros adequadamente** com mensagens claras

4. **Popule as estruturas** (`t_game`, `t_map`, `t_tex`) corretamente

---

## 📐 FORMATO DO ARQUIVO .cub

```
NO ./path/to/north_texture
SO ./path/to/south_texture

### Regras de Formato:
- ✅ Elementos podem estar em **qualquer ordem** (exceto mapa)
- ✅ Mapa **sempre na última posição**
- ✅ Separados por **1+ linhas vazias**
- ✅ **Espaços são válidos** dentro do mapa
- ⚠️ Cada elemento (NO, SO, WE, EA, F, C) deve aparecer **exatamente uma vez**

---

## 🛠️ PLANO DE EXECUÇÃO

### FASE 1: Estrutura e Leitura (Dia 1)

#### 1.1 - Criar arquivo do parser
- **Arquivo:** `src/parsing/parser.c`
- **Responsabilidade:** Orquestração geral do parsing
- **Funções principais:**
  ```c
  int parse_map_file(const char *filename, t_game *game);
  ```

#### 1.2 - Criar utilitários de parsing
- **Arquivo:** `src/parsing/parse_utils.c`
- **Funções:**
  ```c
  char *trim_whitespace(char *str);
  int is_valid_line(const char *line);
  char **read_file_to_array(const char *filename);
  void free_split_result(char **split);
  ```

#### 1.3 - Criar validadores
- **Arquivo:** `src/parsing/validators.c`
- **Funções:**
  ```c
  int validate_texture_path(const char *path);
  int validate_color_format(const char *color_str);
  int validate_rgb_values(int r, int g, int b);
  int validate_map_characters(const t_map *map);
  int validate_map_surrounded(const t_map *map);
  int validate_single_player(const t_map *map);
  ```

#### 1.4 - Criar extractors (extratores)
- **Arquivo:** `src/parsing/extractors.c`
- **Funções:**
  ```c
  int extract_textures(char **lines, t_tex *tex);
  int extract_colors(char **lines, t_tex *tex);
  int extract_map(char **lines, int start_line, t_map *map);
  ```

---

### FASE 2: Implementação dos Extractors (Dia 1-2)

#### 2.1 - Extrair Texturas
```c
int extract_textures(char **lines, t_tex *tex)
{
  // Busca por "NO", "SO", "WE", "EA"
  // Valida caminhos
  // Armazena em tex->walls[N], tex->walls[S], etc
  // Retorna: 0 = sucesso, -1 = erro
}
```

**Checklist:**
- [ ] Identificar linhas que começam com NO/SO/WE/EA
- [ ] Extrair caminho após espaços
- [ ] Validar se arquivo existe
- [ ] Armazenar em estrutura correta
- [ ] Detectar duplicatas

#### 2.2 - Extrair Cores
```c
int extract_colors(char **lines, t_tex *tex)
{
  // Busca por "F" (floor) e "C" (ceiling)
  // Parse formato "R,G,B"
  // Converte para uint32_t RGBA
  // Armazena em tex->floor e tex->ceiling
}
```

**Checklist:**
- [ ] Identificar linhas F e C
- [ ] Fazer split por vírgula
- [ ] Validar valores 0-255
- [ ] Detectar duplicatas
- [ ] Converter para hex RGBA

#### 2.3 - Extrair Mapa
```c
int extract_map(char **lines, int start_line, t_map *map)
{
  // Copia linhas a partir de start_line
  // Calcula dimensões
  // Encontra posição do jogador (N/S/E/W)
  // Armazena em t_map
}
```

**Checklist:**
- [ ] Identificar início do mapa
- [ ] Copiar todas linhas restantes
- [ ] Calcular width (maior linha)
- [ ] Calcular height (número de linhas)
- [ ] Armazenar posição do jogador (px, py)
- [ ] Armazenar direção inicial (pdir)

---

### FASE 3: Validação (Dia 2)

#### 3.1 - Validar Caracteres do Mapa
```c
int validate_map_characters(const t_map *map)
{
  // Verifica se grid contém APENAS:
  // '0', '1', 'N', 'S', 'E', 'W', ' '
  // Retorna 0 = válido, -1 = inválido
}
```

#### 3.2 - Validar Mapa Fechado
```c
int validate_map_surrounded(const t_map *map)
{
  // Verifica se mapa está cercado por paredes ('1')
  // Bordas (0,0) até (height-1, width-1) devem ser '1'
  // Retorna 0 = válido, -1 = inválido
}
```

#### 3.3 - Validar Jogador Único
```c
int validate_single_player(const t_map *map)
{
  // Conta ocorrências de 'N', 'S', 'E', 'W'
  // Deve haver EXATAMENTE 1
  // Retorna 0 = válido, -1 = inválido
}
```

---

### FASE 4: Integração (Dia 2-3)

#### 4.1 - Modificar main.c
Alterar de:
```c
init_mock_map(&game);
```

Para:
```c
if (parse_map_file("maps/map.cub", &game) != 0) {
    ft_putstr_fd("Error\n", 2);
    return (1);
}
```

#### 4.2 - Atualizar cub3d.h
Adicionar declarações:
```c
int parse_map_file(const char *filename, t_game *game);
```

#### 4.3 - Criar Makefile para parsing
Adicionar ao Makefile:
```makefile
PARSING_SRCS = src/parsing/parser.c \
               src/parsing/parse_utils.c \
               src/parsing/validators.c \
               src/parsing/extractors.c
```

---

## 📂 ESTRUTURA DE ARQUIVOS A CRIAR

```
src/
├── parsing/                    ← NOVO DIRETÓRIO
│   ├── parser.c               ← Orquestrador principal
│   ├── parse_utils.c          ← Funções utilitárias
│   ├── validators.c           ← Funções de validação
│   ├── extractors.c           ← Funções de extração
│   └── parsing.h              ← Header interno
├── main.c                      ← MODIFICAR
└── ...
```

---

## ✅ CHECKLIST DE IMPLEMENTAÇÃO

### Preparação
- [ ] Criar diretório `src/parsing/`
- [ ] Criar 4 arquivos `.c` do parsing
- [ ] Criar header `parsing.h`

### Parser Principal
- [ ] Função `parse_map_file()` - orquestrador
- [ ] Ler arquivo linha por linha
- [ ] Separar elementos das linhas

### Parse Utils
- [ ] `trim_whitespace()` - remove espaços extras
- [ ] `is_valid_line()` - verifica se linha é válida
- [ ] `read_file_to_array()` - lê arquivo em array
- [ ] `free_split_result()` - libera memória

### Extractors
- [ ] `extract_textures()` - extrai NO, SO, WE, EA
- [ ] `extract_colors()` - extrai F e C
- [ ] `extract_map()` - extrai grid do mapa

### Validators
- [ ] `validate_texture_path()` - verifica se arquivo existe
- [ ] `validate_color_format()` - verifica "R,G,B"
- [ ] `validate_rgb_values()` - 0 ≤ valor ≤ 255
- [ ] `validate_map_characters()` - apenas 0,1,N,S,E,W, espaço
- [ ] `validate_map_surrounded()` - paredes ao redor
- [ ] `validate_single_player()` - exatamente 1 jogador

### Integração
- [ ] Modificar `main.c` para usar parser
- [ ] Atualizar `cub3d.h` com declarações
- [ ] Atualizar `Makefile`
- [ ] Testar com arquivo `.cub` real

### Tratamento de Erros
- [ ] [ ] Mensagens de erro claras
- [ ] [ ] Liberação de memória em caso de erro
- [ ] [ ] Validação de NULL pointers
- [ ] [ ] Arquivo não encontrado
- [ ] [ ] Arquivo corrompido/mal formatado
- [ ] [ ] Elementos duplicados/faltantes

---

## 🧪 TESTES RECOMENDADOS

### Criar arquivos de teste em `maps/`:

**1. map_valid.cub** - Mapa válido
```
NO ./assets/textures/north.png
SO ./assets/textures/south.png
WE ./assets/textures/west.png
EA ./assets/textures/east.png
F 220,100,0
C 225,30,0

1111111111
1000000001
1010001001
1001N00101
1111111111
```

**2. map_no_border.cub** - Sem bordas (DEVE FALHAR)
```
1111111111
1000000001
100N000001
1111111111
```

**3. map_two_players.cub** - Dois jogadores (DEVE FALHAR)
```
1111111111
1N0000000N
1000000001
1111111111
```

**4. map_invalid_char.cub** - Caractere inválido (DEVE FALHAR)
```
1111111111
1X00000001
1000000001
1111111111
```

**5. map_invalid_color.cub** - Cor RGB fora do range (DEVE FALHAR)
```
NO ./assets/textures/north.png
SO ./assets/textures/south.png
WE ./assets/textures/west.png
EA ./assets/textures/east.png
F 300,100,0
C 225,30,0

1111111111
1000000001
1001N00101
1111111111
```

---

## 🔄 DEPENDÊNCIAS

### O que já temos (reutilizar):
- ✅ `libft.h` com `ft_split()`, `ft_strlen()`, `ft_strchr()`
- ✅ Estruturas em `cub3d.h` (`t_map`, `t_tex`, `t_game`)
- ✅ Função `ft_atoi()` para converter strings em números

### O que precisamos implementar:
- ❌ Funções de parsing (listadas acima)

---

## ⚠️ PONTOS CRÍTICOS

1. **Espaços no Mapa** ← Válidos! Não remover
2. **Ordem dos Elementos** ← Pode ser qualquer ordem (exceto mapa)
3. **Posição do Jogador** ← Deve estar em espaço aberto ('0')
4. **Duplicatas** ← Cada elemento (NO, SO, WE, EA, F, C) APENAS UMA VEZ
5. **Liberação de Memória** ← Usar `free()` corretamente para evitar leaks
6. **Validação Ordem** ← Verificar:
   1. Formato correto (NO, SO, WE, EA, F, C)
   2. Caminhos das texturas existem
   3. Cores no range 0-255
   4. Mapa tem caracteres válidos
   5. Mapa está cercado
   6. Exatamente 1 jogador

---

## 📝 NOTAS DE IMPLEMENTAÇÃO

### Header interno (parsing.h)
```c
#ifndef PARSING_H
# define PARSING_H

# include "../include/cub3d.h"

// Estrutura auxiliar para rastrear o parsing
typedef struct s_parsing_state
{
	int	has_north;
	int	has_south;
	int	has_west;
	int	has_east;
	int	has_floor;
	int	has_ceiling;
	int	map_start;
}	t_parsing_state;

// Funções de extração
int extract_textures(char **lines, t_tex *tex);
int extract_colors(char **lines, t_tex *tex);
int extract_map(char **lines, int start_line, t_map *map);

// Funções de validação
int validate_texture_path(const char *path);
int validate_color_format(const char *color_str);
int validate_rgb_values(int r, int g, int b);
int validate_map_characters(const t_map *map);
int validate_map_surrounded(const t_map *map);
int validate_single_player(const t_map *map);

// Funções utilitárias
char *trim_whitespace(char *str);
char **read_file_to_array(const char *filename);
void free_file_array(char **arr);

#endif
```

### Inicializar t_parsing_state
Usar para rastrear qual elemento foi encontrado e detectar duplicatas.

### Tratamento de Erros Consistente
Retornar:
- `0` = sucesso
- `-1` = erro geral
- `-2` = elemento duplicado
- `-3` = elemento faltante
- `-4` = mapa inválido

---

## 🎯 PRÓXIMOS PASSOS APÓS ESTA ISSUE

1. ✅ Issue 1: Parser .cub (ESTE)
2. ⏳ Issue 2: Ray Casting DDA (blocado por Issue 1)
3. ⏳ Issue 3: Carregamento de texturas (blocado por Issue 1)
4. ⏳ Issue 4: Sistema de colisões (blocado por Issue 1)
5. ⏳ Issue 5: Renderização completa (blocado por Issues 2-3)

---

**Data de Início Recomendada:** 17/01/2026  
**Data Estimada de Conclusão:** 19/01/2026  
**Revisor:** Código deve ser validado contra especificação do projeto

