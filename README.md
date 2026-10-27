# cyber-monitor-daemon
# GCC
## Sommaire
1. [Objectifs et contexte](#1--mise-en-place-des-vm)
2. [Ecriture des scripts](#2-Preparation-des-fichiers-scriptiong)
3. [supply chain](#3-Industrialisation-et-supply-chain)


## 1.  Mise en place des vm
### 1.1 Déploiment d'une Vm serveur et d'une Vm cliente.
Contenant un serveur Web, un serveur ftp tout deux avec un certificat TLS. Ainsi que les serveurs DNS, DHCP qui auront pour domaine starfleet.lan, LDAP, MAriaDB, l'utilisation de PHP pour le serveur web avec ngnix

## 2. Preparation des fichiers scriptiong
### 2.1 Compilation pour le fichier .c

Creation de notre fichier cyber_daemon.c et son executable 
````
#include <stdio.h>
#include <unistd.h>


int main(void)
{
    while (1)
    {
        printf(" cyber_deamon : Surveillance active" );
        fflush(stdout);
        printf("\n");
        sleep(5);
    }
    return 0;
}

````


Commandes pour créer l'executable :

````
gcc -E cyber_daemon.c -o cyber_daemon.i
gcc -S cyber_daemon.i -o cyber_daemon.s
gcc -c cyber_daemon.s -o cyber_daemon.o
gcc cyber_daemon.o -o cyber_daemon

````



### 2.2 Création du systemd.service 



mon fichier unit
````
[Unit]
Description=Affichage toutes les 5 secondes d'une surveillance
After=network.target
[Service]
Type=oneshot
ExecStart=/usr/local/bin/cyber_daemon
RemainAfterExit=yes
StandardError=journal
StandardOutput=journal
StandardInput=null
[Install]
WantedBy=multi-user.target

````

##### Lancer son système service


````
sudo systemctl daemon-reload
sudo systemctl enable --now cyber_monitor
sudo systemctl status cyber_monitor
````

##### Surveiller en tant réel avec les logs de journalctl

>sudo journalctl -u cyber_monitor.service -f

## 3. Industrialisation et supply chain

fichier de mon dossier cyber-daemon-1.0-all 
````
cyber-daemon-1.0-all
├── DEBIAN
   ├── control
   ├── postinst
   ├── rules
└──usr
    └──local
       └──bin
           ├── cyber_daemon
└──lib
    └──systemd
       └── system
           ├──cyber_monitor.service
````


Construction de mon paquet à la RACINE de mon dossier  cyber-daemon-1.0-all
````
dpkg-deb -b . cyber-daemon-1.0-all.deb
````


## Ressources 

https://linuxize.com/post/how-to-create-a-systemd-service/
https://linuxhandbook.com/create-systemd-services/
https://www.linuxtricks.fr/wiki/systemd-creer-des-services-unite-de-type-service 
https://unix.stackexchange.com/questions/627689/how-to-create-a-debian-package-from-a-bash-script-and-a-systemd-service

pour les logs : 
https://serverfault.com/questions/1089887/systemd-process-stdout-stderr
