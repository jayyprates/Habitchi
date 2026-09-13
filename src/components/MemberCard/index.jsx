import { Link } from 'react-router';
import cn from 'classnames';

const MemberCard = ({ name, career, ra, avatar, externalUrl }) => {
  const handleOpenExternalUrl = () => {
    if (!externalUrl) return


    window.open(externalUrl, '_blank')
  }

  return (
    <div 
      className={cn(
        "flex flex-col space-y-2 roboto border-2 p-4 border-gray-200 hover:translate-y-[-5px] hover:border-yellow-400 transition duration-200 min-w-[18%]", {
          "cursor-pointer": externalUrl
        }
      )}
      onClick={handleOpenExternalUrl}
    >
      <img 
        className="object-cover aspect-square pointer-events-none"
        src={`https://api.dicebear.com/10.x/identicon/svg?seed=${ra}`} 
      />
      <hr className="my-2 bg-gray-200 text-gray-200 pointer-events-none" />
      <p className="font-bold capitalize text-sm pointer-events-none">{name}</p>
      <small className="capitalize pointer-events-none">{career}</small>
      <small className="pointer-events-none">RA: {ra}</small>
    </div>
  )
}

export default MemberCard;