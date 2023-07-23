# Laboratorio 2 - Real Time Rendering

Este repositorio contiene el código fuente de mi laboratorio 2 del curso de Gráficas por Computadora, donde estoy practicando técnicas de "Real Time Rendering" utilizando SDL (Simple DirectMedia Layer).

## Descripción

El objetivo de este laboratorio es implementar el famoso juego "Conway's Game of Life". Se trata de un autómata celular que evoluciona en el tiempo a través de reglas muy simples. Cada célula en el tablero puede estar viva o muerta, y su estado depende de los estados de sus vecinos.

El tablero del juego se representa como una cuadrícula, y las células pueden formar patrones interesantes a medida que evolucionan. En este laboratorio, utilizamos una cuadrícula de `FRAMEBUFFER_WIDTH x FRAMEBUFFER_HEIGHT`, y cada célula puede estar en uno de los dos estados: viva o muerta.

Este es el resultado:

![Alt Text](Lab2SDL.gif)
