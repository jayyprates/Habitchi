const Section = ({id, title, body}) => (
  <div className="container-sm flex flex-col" id={id}>
    <h1 className="title text-4xl underline decoration-pink-400 decoration-wavy text-center mb-10 decoration-10 underline-offset-[-8px]">{title}</h1>
    {body}
  </div>
)

export default Section;