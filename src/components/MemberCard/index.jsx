const MemberCard = ({ name, career, ra, avatar }) => (
  <div 
    className="flex flex-col space-y-2 roboto border-2 p-4 border-gray-200 hover:border-yellow-400 transition duration-200 min-w-[18%]"
  >
    <img 
      className="object-cover aspect-square"
      src={`https://api.dicebear.com/10.x/identicon/svg?seed=${ra}`} 
    />
    <hr className="my-2 bg-gray-200 text-gray-200" />
    <p className="font-bold capitalize text-sm">{name}</p>
    <small className="capitalize">{career}</small>
    <small>RA: {ra}</small>
  </div>
)

export default MemberCard;