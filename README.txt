[AVANT PROPOS]

Avant toute chose, je tiens à vous remercier, Mr Belhomme, pour le délai supplémentaire que vous m'avez accordé. 
Je tiens aussi à m'excuser pour ce travail qui est encore incomplet : Tout fonctionne sauf l'ipv6. 
Impossible donc dans la version 2 d'envoyer un fichier en renseignant le nom du serveur distant associé à son adresse IPV6.
Veuillez m'excuser pour cette partie manquante. 

Lionel



[CONTENU DU TRAVAIL]

	- recevoir_f.c 
	- envoyer_f_v1.c
	- envoyer_f_v2.c 


[INSTRUCTIONS DE COMPILATION]

	Pour chacun des fichiers, utiliser la commande gcc pour le compiler 
		- recevoir_f : gcc recevoir_f.c -o recevoir_f
		- envoyer_f_v1 : gcc envoyer_f_v1.c -o envoyer_f_v1
		- envoyer_f_v2 : gcc envoyer_f_v2.c -o envoyer_f_v2


[INSTRUCTIONS D'UTILISATION] 

	Si un problème de connexion est rencontré, utiliser la commande "sudo iptables -F" a réglé le problème chez moi. 


	1) SERVEUR : programme recevoir_f 

	Lancer le programme avec en paramètres : le nom du fichier à recevoir avec son format, le port sur lequel écouter. 
	exemple : ./recevoir_f test_recevoir.png 3456

	2) CLIENT : programme envoyer_f_v1

	Lancer le programme avec en paramètres : le nom du fichier à envoyer, l'adresse ipv4 du serveur distant, le port du serveur 
	exemple : ./envoyer_f_v1 test_envoi.png 192.168.28.129 3456

	3) CLIENT : programme envoyer_f_v2

	Avant toute chose, s'assurer que l'adresse ipv4 du serveur est présent dans son routage dns. 
	Pour s'en assurer, essayer de ping le serveur avant de lancer le programme. 

	Lancer le programme avec en paramètres : le nom du fichier à envoyer, le nom du serveur distant associé à son adresse, le port du serveur
	exemple : ./envoyer_f_v2 test_envoi.png dev2 3456


