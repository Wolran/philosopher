# philosopher


### Règles :

• Des philosophes (un philosophe minimum) sont assis autour d’une table ronde au
centre de laquelle se trouve un grand plat de spaghetti.\
\
• Les philosophes sont soit en train de manger, de penser ou de dormir.\
    Lorsqu’ils mangent, ils ne peuvent pas penser ou dormir.\
    Lorsqu’ils dorment, ils ne peuvent pas manger ou penser.\
Enfin, lorsqu’ils pensent, ils ne peuvent pas manger ou dormir.\
\
• Il y a également des fourchettes sur la table. Il y a autant de fourchettes que
de philosophes.\
\
• Puisque servir et manger des spaghetti à l’aide d’une seule fourchette n’est pas
chose facile, un philosophe prend la fourchette sur sa gauche et celle sur sa droite,
soit une fourchette dans chaque main, afin de manger.\
\
• Quand un philosophe a fini de manger, il repose les fourchettes sur la table et se
met à dormir. Une fois réveillé, il se remet à penser. La simulation prend fin si un
philosophe meurt de faim.\
\
• Chaque philosophe a besoin de manger et ne doit pas mourir de faim.\
\
• Les philosophes ne communiquent pas entre eux.\
\
• Les philosophes ne peuvent pas savoir si l’un d’entre eux est sur le point de mourir.\
\
• Inutile de préciser que les philosophes ne doivent pas mourir !


### Instructions :
• Chaque philosophe doit être représenté par un thread.\
\
• Une fourchette est placée entre chaque paire de philosophes. Cela signifie que, s’il
y a plusieurs philosophes, chaque philosophe a une fourchette à sa gauche et une à
sa droite. S’il n’y a qu’un seul philosophe, il n’y aura donc qu’une seule fourchette
sur la table.\
\
• Afin d’empêcher les philosophes de dupliquer les fourchettes, vous devez protéger
leur état en mémoire avec un mutex pour chacune d’entre elle.
