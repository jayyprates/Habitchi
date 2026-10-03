# Documentação para a tela e-paper com Arduino Nano

Recursos para aprender a escrever texto, desenhar formas e exibir imagens em uma tela Waveshare 2.66" usando **GxEPD2** e **Adafruit GFX**.

## Documentação recomendada

Como a tela funciona com a **GxEPD2**, que usa a **Adafruit GFX** para desenhar, são necessárias três fontes principais de documentação.

### 1. Adafruit GFX — texto, formas, fontes e bitmaps

É o guia principal para aprender a desenhar: linhas, retângulos, círculos, texto, fontes e bitmaps. Tudo o que você aprender ali pode ser usado diretamente na sua tela.

- **Guia:** https://learn.adafruit.com/adafruit-gfx-graphics-library
- **Repositório:** https://github.com/adafruit/Adafruit-GFX-Library

O repositório também inclui a ferramenta `fontconvert`, que permite criar fontes a partir de arquivos `.ttf`.

### 2. GxEPD2 — recursos específicos de e-paper

Aqui está a parte que muda em relação a outras telas: atualização parcial, páginas, `hibernate()`, etc.

- **Repositório:** https://github.com/ZinggJM/GxEPD2

A pasta `examples/` é o que há de mais útil para aprender. Veja principalmente:

- `GxEPD2_HelloWorld`
- `GxEPD2_Example`
- `GxEPD2_MinimumExample`

Esses exemplos mostram como trabalhar com texto, atualização parcial e imagens.

### 3. Documentação da Waveshare

Para o seu módulo específico, consulte a documentação da Waveshare para verificar pinos, tensões, variantes e outras características do hardware.

- **Wiki:** https://www.waveshare.com/wiki

Procure por **"2.66inch e-Paper Module"**.

---

## Imagens: como funciona

Uma imagem para e-paper é um array de bytes em um arquivo `.h`, que fica armazenado na memória Flash do Arduino Nano.

O processo é:

1. Prepare a imagem em preto e branco e no tamanho da tela (`296 × 152`) ou menor.
2. Converta a imagem para um array em C usando uma ferramenta como **Image2Code** ou um conversor online de **Image to C Array / XBM**.
3. Inclua o arquivo com `#include`.
4. Desenhe a imagem utilizando `display.drawBitmap(...)` ou `drawInvertedBitmap(...)`.

Nos exemplos do `GxEPD2_Example` existe uma pasta `bitmaps/` com exemplos do formato esperado.

### Limitação de memória

O Arduino Nano possui aproximadamente **30 KB de memória Flash disponível para o programa**.

Uma imagem completa de `296 × 152` pixels em preto e branco ocupa aproximadamente **5,6 KB**.

Ela cabe na memória, mas uma ou duas imagens grandes já consomem uma parte significativa do espaço disponível. Por isso, imagens menores, como ícones e logos, são mais confortáveis de utilizar.

---

## Ordem sugerida para aprender

Recomenda-se seguir esta ordem:

1. **Texto**
   - `setCursor`
   - `print`
   - `setFont`
   - `setTextSize`

2. **Formas**
   - `drawLine`
   - `drawRect`
   - `fillCircle`

3. **Rotação e posicionamento**
   - `setRotation`
   - `getTextBounds` para centralizar texto

4. **Bitmaps**
   - Exibir imagens e ícones

5. **Atualização parcial**
   - Atualizar apenas uma região da tela sem precisar atualizar a tela inteira.