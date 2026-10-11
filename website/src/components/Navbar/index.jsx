const Navbar = () => (
  <nav id="navbar" className="z-[10] w-full h-[80px] fixed bg-white flex justify-center items-center roboto">
    <ul className="flex space-x-8">
      <li><a className="hover:bg-pink-400 px-2 py-1" href="/#about">O Projeto</a></li>
      <li><a className="hover:bg-yellow-400 px-2 py-1" href="/#team">Equipe</a></li>
      <li><a className="hover:bg-pink-400 px-2 py-1" href="/#blog">Blogs</a></li>
    </ul>
  </nav>
)

export default Navbar;