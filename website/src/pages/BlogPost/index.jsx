// @ Packages 
import { Link, useParams } from "react-router";
import { useEffect, useState } from "react";
import ReactMarkdown from "react-markdown";

// @ Projects
import { posts } from "../../blogs_map";


function BlogPost() {
  const { id } = useParams();
  const [postObj, setPostObj] = useState();
  const [post, setPost] = useState();
  const [error, setError] = useState();
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    let cancelled = false;

    const loadPost = async () => {
      setLoading(true);
      setError(false);
      setPost(null);

      const foundPost = posts[id];

      if (!foundPost) {
        setError("404 - Post not found");
        setLoading(false);
        return;
      }

      try {
        const text = await foundPost.file();
        if (!cancelled) {
          setPost(text);
          setPostObj(foundPost);
        }
      } catch {
        if (!cancelled) setError(true);
      } finally {
        if (!cancelled) setLoading(false);
      }
    };

    loadPost();

    return () => {
      cancelled = true;
    };
  }, [id]);

  return (
    <div className="w-[75%] justify-self-center flex justify-center">
      <div className="w-[75%] flex flex-col mt-20">
        <Link to="/#blog" className="underline text-blue-600 mb-4">{"<"} Voltar</Link>

        {postObj && (
          <p className="mt-0 mb-0 w-[70%] mb-10">
            <strong>Data</strong>: {postObj.date.toLocaleDateString("pt-BR")}
            <br />
            <strong>Autor</strong>: {postObj.author}
          </p>
        )}
        <section className="flex flex-col justify-center prose lg:prose-lg w-full mb-4" id="post">
          
          {(post && !loading) && (
            <ReactMarkdown>
              {post}
            </ReactMarkdown>
          )}
        </section>

        <Link to="/#blog" className="underline text-blue-600 mb-20">{"<"} Voltar</Link>
      </div>
    </div>
  )
}

export default BlogPost;
