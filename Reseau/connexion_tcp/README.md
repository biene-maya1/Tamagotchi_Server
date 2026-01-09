MAYA CUGNIET G1

Pour ce projet j'ai fait :

-un serveur UDP (simple)
-un serveur TCP (avec connexion en flux)
-puis une implementation de Tamagotchi 

Le serveur UDP suivait une implemantation simple ou le serveur attends un message dun client puis la communication se termine immediatement. 
-> ce qui m'a permis de comprendre comment creer un serveur simple en C ( sokcets, envoie, reception, etc.)

Puis il fallait basculer sur TCP pour une connexion plus fiable et un echange bidirectionnel ainsi qu'une communication continue cette fois ci.
-> creation dun serveur avec socket, bind, listen et accept 
-> connexion du client doit etre accepter par le serveur 

Enfin j'ai implementé un tamagotchi pour rendre le projet plus creatif :) 
le serveur a donc un animal qui a un status de sleep, hunger et happiness. Le client peut envoyer des commandes pour nourir, faire dormir et joueur avec l'animal.
-> serveur lui renvoie un feedback 
Pour rendre le jeu un peu plus marrant j'ai implementer le fait que l'animal peut mourir si il est trop fatigué, sachant que les stats evoluent avec le temps et les commandes envoyé par le client.


Lancement:
make 
make serveur 
make client ARGS="127.0.0.1 9600"





