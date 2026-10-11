export const files = import.meta.glob("./posts/*.md", { query: "?raw", import: "default" });

export const posts = {
  nosso_primeiro_artigo: { 
    date: new Date(2026,10, 10),
    author: "Lorem Ipsum",
    title: "Nosso primeiro artigo!", 
    file: files["./posts/nosso_primeiro_artigo.md"] 
  }
};

