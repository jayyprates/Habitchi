// @ Project
import Footer from "../../components/Footer";
import Navbar from "../../components/Navbar";
import MemberCard from "../../components/MemberCard"
import Tamagotchi from "../../assets/tamagotchi.png";
import Proposta from "../../assets/habitchi_proposta.pdf"

function App() {
  const MEMBERS = [
    {
      "name": "Fabrizio Liotta",
      "career": "Eng. Eletrica",
      "ra": "202651446"
    },
    {
      "name": "Joana Prates",
      "career": "Eng. Computaçao",
      "ra": "202616727",
      "external_url": "https://jayyprates.github.io/PortfolioCoder/index.html"
    },
    {
      "name": "Pedro Ciscotto",
      "career": "Eng. Computaçao",
      "ra": "202611111"
    },
    {
      "name": "Victor Hugo",
      "career": "Eng. Computaçao",
      "ra": "202622222"
    },
    {
      "name": "David Assis",
      "career": "Eng. Computaçao",
      "ra": "202633333"
    }
  ]

  return (
    <div className="pb-20">
      <Navbar />
  
      <section  className="w-full" id="header">
        <div className="pattern-bg"></div>
        <div className="flex justify-center items-start flex-col relative">
          <div className="w-full justify-center flex">
            <img src={Tamagotchi} className="hover:rotate-10 w-[75px]"/>
          </div>
          <h1 className="text-7xl md:text-8xl select-none title">Habitchi</h1>
          <div className="flex flex-col space-y-2">
            <p><span className="bg-pink-400 px-2 py-1 select-none">Criando hábitos</span></p>
            <div className="pulse_animation md:hidden">
              <a href={Proposta} target="_blank"><span className="bg-yellow-400 px-2 py-1 select-none ">Baixe a nossa proposta</span></a>
            </div>
          </div>
          <div className="absolute bg-yellow-400 right-[-100px] bottom-0 pulse_animation px-2 py-1 rotate-[-10deg] cursor-pointer hidden md:flex">
            <a href={Proposta} className="font-small" target="_blank">Baixe a nossa proposta</a>
          </div>
        </div>
      </section>

      <div className="space-y-10 flex flex-col items-center">
        <section className="w-[90%] sm:w-[60%] flex flex-col space-y-4" id="about">
          <h2 className="title text-4xl underline decoration-pink-400 decoration-wavy text-center mb-10 decoration-10 underline-offset-[4px] select-none">Sobre o projeto</h2>
          <p className="roboto">
            Formar um novo hábito não depende apenas de força de vontade. Você também precisa lembrar, todos os dias, de repetir a mesma ação até que ela se torne automática. 
            Nem sempre a rotina ajuda. 
            <a 
            href="https://www.sciencedaily.com/releases/2025/01/250124151347.htm" 
            target="_blank"
            className="underline text-blue-600 hover:text-blue-800 visited:text-purple-600 mx-1"
            >
              Um estudo da Universidade do Sul da Austrália (UniSA)
            </a> 
            mostrou que o tempo médio para consolidar um novo hábito saudável é de aproximadamente 66 dias.

            <br/><br/>
            Por isso, o <strong>Habitchi</strong> propõe transformar o processo de repetição diária em algo mais motivador e visível no dia a dia. 
            <br/><br/>

            O Habitchi é um chaveiro eletrônico com um bichinho virtual que cresce conforme o usuário cumpre um hábito que deseja incorporar à rotina. A cada dia em que o hábito é registrado como cumprido, o bichinho ganha felicidade e continua se desenvolvendo. Quando o hábito deixa de ser cumprido, o bichinho fica triste e para de crescer. Se o abandono persistir, ele morre. A ideia é usar o vínculo afetivo com o bichinho como reforço extra de motivação para incentivar a constância necessária para que o hábito se torne automático.
          </p>
        </section>

        <section className="w-[90%] sm:w-[75%] md:w-[60%] flex flex-col space-y-4" id="team">
          <h2 className="title text-4xl mb-4 underline decoration-yellow-400 decoration-wavy mt-10 mb-10 text-center decoration-10 underline-offset-[4px] select-none">A equipe</h2>
          {/* DESKTOP */}
          <div className="w-full justify-between xl:flex hidden space-x-4">
            {MEMBERS.map((member) => (
              <MemberCard 
                name={member.name}
                career={member.career}
                ra={member.ra}
                key={`desktop_member_card_{member.ra}`}
                externalUrl={member.external_url}
              />
            ))}
          </div>
          {/* MOBILE */}
          <div className="xl:hidden">
            <table className="table-auto w-full border-separate border-spacing-y-4">
              <thead>
                <tr className="text-left">
                  <th></th>
                  <th>Nome</th>
                  <th>Carreira</th>
                  <th>RA</th>
                </tr>
              </thead>
              <tbody>
                {MEMBERS.map(member => (
                  <tr key={`mobile_member_card_{member.ra}`}>
                    <td>
                      <img src={`https://api.dicebear.com/10.x/identicon/svg?seed=${member.ra}`} className="w-[20px] h-[20px] mr-2" />
                    </td>
                    <td className="text-sm">{member.name}</td>
                    <td className="text-sm">{member.career}</td>
                    <td className="text-sm">{member.ra}</td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </section>

        <section className="w-[90%] sm:w-[60%] flex flex-col space-y-4" id="blog">
          <h2 className="title text-4xl mb-4 underline decoration-pink-400 decoration-wavy mt-10 mb-10 text-center decoration-10 underline-offset-[4px] select-none">Blogs</h2>
          
          <div className="relative w-full space-y-4 flex flex-col justify-center items-center">
            <p className="text-xl md:text-2xl tracking-wider px-2 py-1 text-gray-400 select-none">[XX/XX/2026] - Nosso primeiro artigo! (Em breve)</p>
          </div>
        </section>
      </div>
    </div>
  )
}

export default App
