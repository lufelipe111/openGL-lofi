### Aluno
- Nome: Luiz Felipe Leal Gomes Azzolini
- RA: 11048715 

### Sobre o projeto

O projeto feito para a disciplina de computação gráfica se inspirou nas famosas radios de musica do estilo Lo-Fi no Youtube para montar uma réplica em 3D do quarto da ilustração [studying girl](https://upload.wikimedia.org/wikipedia/en/3/3e/Lo-Fi_Girl.png) capa principal das rádios citadas, explorando a biblioteca abcg feita para facilitar o uso e estudo de openGL.

O projeto é composto de alguns modelos (atualmente mesa, estante, cama e chão), renderizados pelo openGL a partir de arquivos _*.obj_ , além de outros arquivos responsáveis por:
* objeto de inicialização ([main.cpp](examples/the-calm-room/main.cpp))
*  gerenciamento de janela e de carregamento de modelos ([openGLWindow.cpp](examples/the-calm-room/openGLWindow.cpp))
*   posicionamento de câmera ([camera.cpp](examples/the-calm-room/camera.cpp))
*   renderização de modelo a partir de arquivos _.obj_ ([model.cpp](examples/the-calm-room/model.cpp)).

---

### Bugs
Não foram encontrados bugs gráficos localmente nessa entrega.

Apesar disso ao compilar o arquivo para WebAssembly o browser retornava um erro sem carregar a aplicação.

---

### Próximas funcionalidades
- [ ] interação do usuário com o ambiente a partir da câmera
- [ ] tratamento de luminosidade
- [ ] criação de texturas

---

ABCg
======

Development framework accompanying the course MCTA008-17 Computer Graphics at [UFABC](https://www.ufabc.edu.br/).

----

### Credits

Developed by Harlen Batagelo.

### License

ABCg is licensed under the MIT License. See [LICENSE](https://github.com/hbatagelo/abcg/blob/main/LICENSE) for more information.
