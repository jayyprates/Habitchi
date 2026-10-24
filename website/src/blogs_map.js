export const files = import.meta.glob("./posts/*.md", { query: "?raw", import: "default" });

export const posts = {
  primeiro_post: { 
    date: new Date(2026,09, 09),
    author: "Grupo",
    title: "#1 Definição do Projeto", 
    file: files["./posts/artigo_1.md"] 
  }, 

  segundo_post: { 
    date: new Date(2026,09, 16),
    author: "Grupo",
    title: "#2 Arquitetura do Projeto", 
    file: files["./posts/artigo_2.md"] 
  },
  
  terceiro_post: { 
    date: new Date(2026,09, 23),
    author: "Grupo",
    title: "#3 Início do Desenvolvimento", 
    file: files["./posts/artigo_3.md"] 
  }

};

