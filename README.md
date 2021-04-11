# Gaveta inteligente
## Equipe 2 - Sistemas microprocessados:
Francisco Jefferson - 470239
Lucas Cordeiro do Vale Menezes - 472887
Vinicius Costa Secundino - 471357

## Links
Github: https://github.com/viniciussec/gaveta-inteligente
YouTube: Não disponível

## Proposta inicial
Uma gaveta organizadora: Ao digitarmos o nome de um item, o compartimento que contém o item com o mesmo nome irá ser iluminado, facilitando a sua busca. Se o item não estiver presente, o sistema irá indicar onde o item deveria estar, para caso o usuário deseje repô-lo, com uma cor diferente (vermelha, por exemplo) e o notificar por meio de um som característico. Já caso o item não esteja cadastrado, o sistema irá acender todas as luzes com uma terceira cor e aguardar o usuário digitar. Se ele digitar "S" no teclado, irá mostrar os espaços disponíveis e aguardar que o item seja posicionado. Já se ele digitar "N" no teclado, o sistema irá apagar todas as luzes.

## Alterações sofridas devido ao simulador
O teclado foi modificado para ser um teclado numérico (ou matricial), pois o simulador Proteus não integra a comunicação entre o teclado nativo do computador com o microprocessador. Já quanto às funcionalidades da gaveta, teremos: cadastro e procura de itens a partir do seu código, facilitando organização de gavetas residenciais, ou em grande escala, de estoques comerciais ou industriais.

![Imagem Gaveta](https://imgur.com/EhtJBza.png)
Imagem exemplificando quando um objeto é encontrado.

## Diagrama de blocos:
![Imagem fluxograma](https://imgur.com/pWg01a1.png)

## Esquemático:
![Imagem Esquemático](https://imgur.com/dhvWMEH.png)

## Resultados
 - Luzes corretamente implementadas
 - Sistema de armazenamento e consulta de objetos
 - 

## Conclusões:
Tivemos bastante dificuldades causadas pelo uso do simulador. Ao utilizarmos o teclado ou o sistema da gaveta, o sistema gastava bastante tempo e energia da CPU tentando realizar e animar todas as instruções, que ficavam em loop, causando um efeito inesperado e inviabilizando seu uso na demonstração via simulador. Após algumas pesquisas realizadas para descobrir o motivo de tal comportamento, descobrimos que isso é causado por conta das conexões dos circuitos. Porém, a realização do projeto, mesmo com tais agraventes, pôde ser muito proveitosa e nos agregou bastante experiência, principalmente em uma área não tão explorada em momentos iniciais do curso de engenharia de computação. 